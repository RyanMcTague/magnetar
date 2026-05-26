#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    class Window;

    class MAGNETAR_API Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
        void close();

        Window *get_window();

    protected:
        virtual void on_initialize();
        virtual void on_shutdown();
        virtual void on_update(float delta_time);

    private:
        bool m_is_running;
        Ref<Window> m_window;
        void initialize();
        void shutdown();
    };
}
