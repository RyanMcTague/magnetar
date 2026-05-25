#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    struct MAGNETAR_API WindowProps
    {
        std::string title;
        int width;
        int height;
    };

    class MAGNETAR_API Window
    {
    public:
        Window() = default;
        virtual ~Window() = default;
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        virtual int width() const = 0;
        virtual int height() const = 0;
        virtual const std::string& title() const = 0;

        virtual void poll_events() = 0;
        virtual void swap_buffers() const = 0;
        virtual bool should_close() const = 0;
        virtual void* handle() = 0;

        static Ref<Window> create(const WindowProps& props);
    };
}