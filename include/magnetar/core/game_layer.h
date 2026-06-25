#pragma once
#include "magnetar/core/base.h"
#include "magnetar/core/layer.h"
#include "magnetar/scene/scene.h"
#include "magnetar/renderer/font.h"
namespace magnetar
{
    class MAGNETAR_API GameLayer: public Layer
    {
    public:
        MT_DECLARE_CLASS_NAME(GameLayer)
        void on_attach();
        void on_detach();
        void on_update(float delta_time);
        void on_render();

        void set_scene(Ref<Scene> scene);
    private:
        Ref<Scene> m_scene;
        Ref<Font> m_font;

    };
}