#include "magnetar/events/event_system.h"

uint32_t magnetar::EventSystem::s_next_event_type_id = 1;
std::unordered_map<std::type_index, magnetar::EventSystem::Entry> magnetar::EventSystem::s_entries;
std::queue<magnetar::Ref<magnetar::EventSystem::IQueuedEvent>> magnetar::EventSystem::s_queued_events;

void magnetar::EventSystem::unsubscribe(EventHandle handle)
{
    uint32_t event_type_id = handle.event_type_id();
    uint32_t callback_id = handle.event_callback_id();
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

void magnetar::EventSystem::process()
{
    while (!s_queued_events.empty())
    {
        auto& event = s_queued_events.back();
        event->dispatch();
        s_queued_events.pop();
    }
}