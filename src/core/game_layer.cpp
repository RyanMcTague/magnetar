#include "magnetar/core/game_layer.h"
#include "magnetar/renderer/renderer.h"

#include "magnetar/scene/systems/mesh_renderer_system.h"
#include "magnetar/scene/systems/sprite_renderer_system.h"

void magnetar::GameLayer::on_attach()
{
}

void magnetar::GameLayer::on_detach()
{
}

void magnetar::GameLayer::on_update(float)
{
    m_scene->registry().flush();
}

void magnetar::GameLayer::on_render()
{
    Renderer::begin_scene(m_scene->camera());
    m_scene->registry().get_system<MeshRendererSystem>()->render();
    m_scene->registry().get_system<SpriteRendererSystem>()->render();
    Renderer::end_scene();
}

void magnetar::GameLayer::set_scene(Ref<Scene> scene)
{
    m_scene = scene;
}