#pragma once
#include <stack>
#include <functional>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "magnetar/core/base.h"

namespace magnetar
{
    template <typename T>
    using EventCallbackFunction = std::function<void(const T &)>;

    using EventHandle = uint64_t;
    using EventTypeID = uint32_t;
    using EventCallbackID = uint32_t;

    class MAGNETAR_API IEventCallback
    {
    public:
        IEventCallback(EventCallbackID id) : m_id(id) {}
        virtual ~IEventCallback() = default;

        virtual void call(const void *event) = 0;

        EventCallbackID id() const { return m_id; }

    private:
        EventCallbackID m_id;
    };

    template <typename T>
    class MAGNETAR_API EventCallback : public IEventCallback
    {
    public:
        EventCallback(EventCallbackID id, EventCallbackFunction<T> function)
            : IEventCallback(id), m_function(function) {}

        void call(const void *event) override
        {
            m_function(*static_cast<const T *>(event));
        }

    private:
        EventCallbackFunction<T> m_function;
    };

    struct MAGNETAR_API EventSystemEntry
    {
        EventTypeID event_type_id;
        std::stack<EventCallbackID> free_callback_ids;
        EventCallbackID next_callback_id;
        std::vector<Ref<IEventCallback>> callbacks;

        EventSystemEntry(EventTypeID id)
            : event_type_id(id), next_callback_id(0) {}

        EventCallbackID generate_id()
        {
            EventCallbackID id = 0;
            if (free_callback_ids.empty())
            {
                id = next_callback_id++;
            }
            else
            {
                id = free_callback_ids.top();
                free_callback_ids.pop();
            }
            return id;
        }

        void free_id(EventCallbackID id)
        {
            free_callback_ids.push(id);
        }
    };

    class MAGNETAR_API EventSystem
    {
    public:

        static EventSystem* get()
        {
            if(!s_instance)
                s_instance = new EventSystem();
            return s_instance;
        }
        static void shutdown()
        {
            if(s_instance)
                delete s_instance;
        }

        template <typename T>
        EventHandle subscribe(EventCallbackFunction<T> function)
        {
            auto it = m_entries.find(typeid(T));
            if (it == m_entries.end())
            {
                it = m_entries.emplace(typeid(T), EventSystemEntry(m_next_event_type_id++)).first;
            }

            EventSystemEntry &entry = it->second;
            EventCallbackID callback_id = entry.generate_id();
            EventTypeID event_type_id = entry.event_type_id;

            auto callback = create_reference<EventCallback<T>>(callback_id, function);
            entry.callbacks.push_back(std::static_pointer_cast<IEventCallback>(callback));

            return ((EventHandle)(event_type_id) << 32) | (EventHandle)callback_id;
        }

        void unsubscribe(EventHandle handle)
        {
            EventTypeID event_type_id = (EventTypeID)(handle >> 32);
            EventCallbackID callback_id = (EventCallbackID)(handle & 0xffffffff);
            for (auto &pair : m_entries)
            {
                EventSystemEntry &entry = pair.second;
                if (entry.event_type_id == event_type_id)
                {
                    auto it = std::find_if(entry.callbacks.begin(), entry.callbacks.end(),
                                           [callback_id](Ref<IEventCallback> cb)
                                           { return cb->id() == callback_id; });

                    if (it != entry.callbacks.end())
                    {
                        entry.free_id(callback_id);
                        entry.callbacks.erase(it);
                    }
                    break;
                }
            }
        }

        template <typename T, typename U>
        EventHandle subscribe(U *instance, void (U::*function)(const T &))
        {
            auto func = [instance, function](const T &event)
            {
                (instance->*function)(event);
            };
            return subscribe<T>(func);
        }

        template <typename T>
        void emit(const T &event)
        {
            auto it = m_entries.find(typeid(T));
            if (it == m_entries.end())
                return;

            for (Ref<IEventCallback> &callback : it->second.callbacks)
                callback->call(&event);
        }

    private:
        static EventSystem *s_instance;
        EventTypeID m_next_event_type_id;
        std::unordered_map<std::type_index, EventSystemEntry> m_entries;

        EventSystem()
            : m_next_event_type_id(1) {}
    };
}