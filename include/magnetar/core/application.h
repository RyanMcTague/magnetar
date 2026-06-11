#pragma once
#include <vector>
#include "magnetar/core/base.h"
#include "magnetar/core/layer_stack.h"
#include "magnetar/renderer/buffer_mask.h"

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
        virtual void on_render();
        virtual const char* asset_config() = 0;

        template<typename T, typename ...TArgs>
        Ref<T> push_layer(TArgs&& ...args);

    private:
        bool m_is_running;
        bool m_is_initialized;
        Ref<Window> m_window;
        LayerStack m_layer_stack;
        BufferMask m_mask;
        std::vector<Ref<Layer>> m_layers;
        
        void update(float delta_time);
        void render();
        void shutdown();
    };

    template<typename T, typename ...TArgs>
    Ref<T> Application::push_layer(TArgs&& ...args)
    {
        auto ref = create_reference<T>(std::forward<TArgs>(args)...);
        Ref<Layer> layer = std::static_pointer_cast<Layer>(ref);
        layer->on_attach();
        m_layer_stack.push_layer(layer);
        return layer;
    }
}
