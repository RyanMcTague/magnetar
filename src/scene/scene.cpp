#include "magnetar/scene/scene.h"
#include "magnetar/scene/systems/mesh_renderer_system.h"
#include "magnetar/scene/systems/sprite_renderer_system.h"

magnetar::Scene::Scene()
    : m_camera(nullptr) 
{
    m_registry.register_system<MeshRendererSystem>();
    m_registry.register_system<SpriteRendererSystem>();
}

void magnetar::Scene::set_camera(Ref<Camera> camera)
{
    m_camera = camera;
}