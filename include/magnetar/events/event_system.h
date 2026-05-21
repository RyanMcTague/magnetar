#pragma once
#include <stack>
#include <functional>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "magnetar/core/base.h"
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

        static void unsubscribe(EventHandle handle);

    private:
        struct Entry
        {
            EventTypeID event_type_id;
            EventCallbackID next_callback_id;
            std::stack<EventCallbackID> free_callback_ids;
            std::vector<Ref<IEventCallback>> callbacks;
        };

        static EventTypeID s_next_event_type_id;
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
        EventTypeID event_type_id = entry.event_type_id;
        EventCallbackID callback_id = 0;

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

        return ((EventHandle)(event_type_id) << 32) | (EventHandle)callback_id;
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
        auto it = s_entries.find(typeid(T));
        if (it == s_entries.end())
            return;

        for (Ref<IEventCallback> &callback : it->second.callbacks)
            callback->call(&event);
    }
}