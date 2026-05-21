#include "magnetar/events/event_system.h"

magnetar::EventTypeID magnetar::EventSystem::s_next_event_type_id = 1;
std::unordered_map<std::type_index, magnetar::EventSystem::Entry> magnetar::EventSystem::s_entries;

void magnetar::EventSystem::unsubscribe(EventHandle handle)
{
    EventTypeID event_type_id = (EventTypeID)(handle >> 32);
    EventCallbackID callback_id = (EventCallbackID)(handle & 0xffffffff);
    for (auto &pair : s_entries)
    {
        Entry &entry = pair.second;
        if (entry.event_type_id == event_type_id)
        {
            auto it = std::find_if(entry.callbacks.begin(), entry.callbacks.end(),
                                   [callback_id](Ref<IEventCallback> cb)
                                   { return cb->id() == callback_id; });

            if (it != entry.callbacks.end())
            {
                entry.free_callback_ids.push(callback_id);
                entry.callbacks.erase(it);
            }
            break;
        }
    }
}