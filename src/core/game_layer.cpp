#include "magnetar/core/game_layer.h"
#include "magnetar/renderer/renderer.h"

void magnetar::GameLayer::on_attach()
{
}

void magnetar::GameLayer::on_detach()
{
}

void magnetar::GameLayer::on_update(float delta_time)
{
    m_scene->flush_entities();
    m_scene->on_update(delta_time);
}

void magnetar::GameLayer::on_render()
{
    m_scene->begin_scene();
    m_scene->on_render();
    m_scene->end_scene();
}

void magnetar::GameLayer::set_scene(Ref<Scene> scene)
{
    m_scene = scene;
}