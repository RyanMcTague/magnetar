#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    // using EventHandle = uint64_t;
    // using EventTypeID = uint32_t;
    // using EventCallbackID = uint32_t;

    class EventHandle
    {
    public:
        EventHandle()
            : m_event_type_id(0), m_event_callback_id(0) {}

        EventHandle(uint64_t value)
            : m_event_type_id(value >> 32), m_event_callback_id(value & 0xffffffff) {}

        EventHandle(uint32_t event_type_id, uint32_t event_callback_id)
            : m_event_type_id(event_type_id), m_event_callback_id(event_callback_id) {}

        uint32_t event_type_id() const { return m_event_type_id; }
        uint32_t event_callback_id() const { return m_event_callback_id; }
        uint64_t value() const { return ((uint64_t)m_event_type_id << 32) & (uint64_t)m_event_callback_id; }

        bool operator==(const EventHandle &rhs) const { return value() == rhs.value(); }
        bool operator!=(const EventHandle &rhs) const { return !(*this == rhs); }

        bool operator==(uint64_t rhs) const { return value() == rhs; }
        bool operator!=(uint64_t rhs) const { return !(*this == rhs); }

    private:
        uint32_t m_event_type_id;
        uint32_t m_event_callback_id;
    };
}