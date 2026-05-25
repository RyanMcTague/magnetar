#pragma once
#include <stack>
#include <functional>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include "magnetar/core/base.h"
#include "magnetar/core/uuid.h"
#include "magnetar/events/event_handle.h"
#include "magnetar/events/event_callback.h"

namespace magnetar
{
    class MAGNETAR_API EventSystem
    {
    public:
        template <typename T>
        static EventHandle subscribe(EventCallbackFunction<T> function);

        template <typename T, typename U>
        static EventHandle subscribe(U *instance, void (U::*function)(const T &));

        template <typename T>
        static void emit(const T &event);

        template <typename T>
        static void enqueue(const T &event);

        static void unsubscribe(EventHandle handle);

        static void process();

    private:
        struct Entry
        {
            uint32_t event_type_id;
            uint32_t next_callback_id;
            std::stack<uint32_t> free_callback_ids;
            std::vector<Ref<IEventCallback>> callbacks;
        };

        struct IQueuedEvent
        {
            virtual ~IQueuedEvent() = default;
            virtual void dispatch() = 0;
        };

        template <typename T>
        struct QueuedEvent : public IQueuedEvent
        {
            T event;
            UUID id;

            QueuedEvent()
            {
                LOG_DEBUG(logger::tags::events, "enqueued event {}#{}", MT_STATIC_CLASS_NAME(T), id.to_hex());
            }

            void dispatch() override
            {
                LOG_TRACE(logger::tags::events, "dispatching event {}#{}", MT_STATIC_CLASS_NAME(T), id.to_hex());
                EventSystem::emit(event);
            }
        };

        static uint32_t s_next_event_type_id;
        static std::queue<Ref<IQueuedEvent>> s_queued_events;
        static std::unordered_map<std::type_index, Entry> s_entries;
    };

    template <typename T>
    EventHandle EventSystem::subscribe(EventCallbackFunction<T> function)
    {
        auto it = s_entries.find(typeid(T));
        if (it == s_entries.end())
        {
            Entry entry;
            entry.next_callback_id = 0;
            entry.event_type_id = s_next_event_type_id++;
            it = s_entries.emplace(typeid(T), entry).first;
        }

        Entry &entry = it->second;
        uint32_t event_type_id = entry.event_type_id;
        uint32_t callback_id = 0;

        if (entry.free_callback_ids.empty())
        {
            callback_id = entry.next_callback_id++;
        }
        else
        {
            callback_id = entry.free_callback_ids.top();
            entry.free_callback_ids.pop();
        }

        auto callback = create_reference<EventCallback<T>>(callback_id, function);
        entry.callbacks.push_back(std::static_pointer_cast<IEventCallback>(callback));


        EventHandle handle(event_type_id, callback_id);
        return handle;
    }

    template <typename T, typename U>
    EventHandle EventSystem::subscribe(U *instance, void (U::*function)(const T &))
    {
        auto func = [instance, function](const T &event)
        {
            (instance->*function)(event);
        };
        return subscribe<T>(func);
    }

    template <typename T>
    void EventSystem::emit(const T &event)
    {
        LOG_TRACE(logger::tags::events, "emitting event {}", T::static_class_name());
        auto it = s_entries.find(typeid(T));
        if (it == s_entries.end())
            return;

        for (Ref<IEventCallback> &callback : it->second.callbacks)
            callback->call(&event);
    }

    template <typename T>
    void EventSystem::enqueue(const T &event)
    {
        auto ref = create_reference<QueuedEvent<T>>();
        ref->event = event;
        s_queued_events.push(std::static_pointer_cast<IQueuedEvent>(ref));
    }
}