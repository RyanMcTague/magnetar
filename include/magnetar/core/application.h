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
        void initialize();

        Window *get_window();

    protected:
        virtual void on_initialize();
        virtual void on_shutdown();
        virtual void on_update(float delta_time);
        virtual const char* asset_config() = 0;

    private:
        bool m_is_running;
        bool m_is_initialized;
        Ref<Window> m_window;
        void shutdown();
    };
}
