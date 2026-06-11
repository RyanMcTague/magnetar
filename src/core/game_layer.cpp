#include "magnetar/core/game_layer.h"
#include "magnetar/renderer/renderer.h"

void magnetar::GameLayer::on_attach()
{
}

void magnetar::GameLayer::on_detach()
{
}

void magnetar::GameLayer::on_update(float)
{
}

void magnetar::GameLayer::on_render()
{
    Renderer::begin_scene(m_scene->camera());
    
    Renderer::end_scene();
}

void magnetar::GameLayer::set_scene(Ref<Scene> scene)
{
    m_scene = scene;
}