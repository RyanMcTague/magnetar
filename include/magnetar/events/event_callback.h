#pragma once
#include "magnetar/events/event_handle.h"
#include "magnetar/core/base.h"

namespace magnetar
{
    template <typename T>
    using EventCallbackFunction = std::function<void(const T &)>;
    
    class MAGNETAR_API IEventCallback
    {
    public:
        IEventCallback(uint32_t id) : m_id(id) {}
        virtual ~IEventCallback() = default;

        virtual void call(const void *event) = 0;

        uint32_t id() const { return m_id; }

    private:
        uint32_t m_id;
    };

    template <typename T>
    class MAGNETAR_API EventCallback : public IEventCallback
    {
    public:
        EventCallback(uint32_t id, EventCallbackFunction<T> function)
            : IEventCallback(id), m_function(function) 
        {
            LOG_TRACE(logger::tags::events, "Event subscription {:x} created for event {}", this->id(), MT_STATIC_CLASS_NAME(T));
        }

        ~EventCallback()
        {
            LOG_TRACE(logger::tags::events, "Event subscription {:x} removed for event", this->id(), MT_STATIC_CLASS_NAME(T));
        }

        void call(const void *event) override
        {
            m_function(*static_cast<const T *>(event));
        }

    private:
        EventCallbackFunction<T> m_function;
    };
}