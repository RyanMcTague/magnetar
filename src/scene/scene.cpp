#include "magnetar/scene/scene.h"
#include "magnetar/scene/systems/mesh_renderer_system.h"

magnetar::Scene::Scene()
    : m_camera(nullptr) 
{
    m_registry.register_system<MeshRendererSystem>();
}

void magnetar::Scene::set_camera(Ref<Camera> camera)
{
    m_camera = camera;
}