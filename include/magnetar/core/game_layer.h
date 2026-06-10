#pragma once
#include "magnetar/core/base.h"
#include "magnetar/core/layer.h"
#include "magnetar/scene/scene.h"
namespace magnetar
{
    class MAGNETAR_API GameLayer: public Layer
    {
    public:
        GameLayer(Scene* scene = nullptr) 
            : m_scene(scene) {}
        void on_attach();
        void on_detach();
        void on_update(float delta_time);
        void on_render();

    private:
        Scene* m_scene;
    };
}