#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/camera.h"
#include "magnetar/scene/ecs.h"
namespace magnetar
{   
    class MAGNETAR_API Scene
    {
    public:
        Scene();
        void set_camera(Ref<Camera> camera);
        const Ref<Camera> &camera() const { return m_camera; }

        Registry &registry() { return m_registry; }
        
    private:
        Ref<Camera> m_camera;
        Registry m_registry;
    };
}