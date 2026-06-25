#include "magnetar/core/game_layer.h"
#include "magnetar/renderer/renderer.h"
#include "magnetar/renderer/renderer2d.h"
#include "magnetar/filesystem/native_file_system.h"
void magnetar::GameLayer::on_attach()
{
    auto fs = FileSystem::get<NativeFileSystem>();
    auto file = fs->open("./sample/assets/fonts/Roboto-Regular.ttf", FileMode::READ);
    m_font = create_reference<Font>(file.get());
}

void magnetar::GameLayer::on_detach()
{
}

void magnetar::GameLayer::on_update(float delta_time)
{
    m_scene->on_update(delta_time);
}

void magnetar::GameLayer::on_render()
{
    m_scene->begin_scene();
    m_scene->on_render();

    auto character = m_font->get('A');
    Renderer2D::draw_quad(glm::vec3(20.0f, 20.0f, 0.5f), glm::vec2(10.0f, 10.0f), m_font->texture(), Rect(character.uv0, character.uv1));
    m_scene->end_scene();
}

void magnetar::GameLayer::set_scene(Ref<Scene> scene)
{
    m_scene = scene;
}