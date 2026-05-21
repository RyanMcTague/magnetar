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
}