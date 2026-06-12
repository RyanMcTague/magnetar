#include <magnetar/magnetar.h>
#include <glm/gtc/matrix_transform.hpp>
#include "assets.h"
using namespace magnetar;

glm::vec4 rgba_color(uint32_t color)
{
    uint8_t red = (color & 0xff000000) >> 24;
    uint8_t green = (color & 0x00ff0000) >> 16;
    uint8_t blue = (color & 0x0000ff00) >> 8;
    uint8_t alpha = (color & 0x000000ff);

    glm::vec4 c;
    c.x = (float)red / 255.0f;
    c.y = (float)green / 255.0f;
    c.z = (float)blue / 255.0f;
    c.w = (float)alpha / 255.0f;
    return c;
}

namespace actions
{
    static constexpr int quit = 0;
}

namespace colors
{
    const glm::vec4 blue = rgba_color(0x2596beff);
    const glm::vec4 red = rgba_color(0xbf2443ff);
};

class SandboxApp final : public Application
{
protected:
    void on_initialize() override;
    void on_update(float delta_time) override;
    const char *asset_config() override;

private:
    Ref<Camera> m_camera;
    Ref<GameLayer> m_layer;
    Ref<Scene> m_scene;
    std::string m_asset_config;
    EntityHandle m_player_handle;
    EntityHandle m_enemy_handle;
};

void SandboxApp::on_initialize()
{
    InputSystem::register_action(actions::quit, KeyboardKey::ESCAPE);

    auto aspect_ratio = get_window()->aspect_ratio();
    auto windwidth = get_window()->width();
    auto winheight = get_window()->height();
    float y = 4.0f;
    float x = y * aspect_ratio;
    m_camera = create_reference<Camera2D>(-x, x, y, -y, -1.0, 1.0);

    m_scene = create_reference<Scene>();
    m_layer = push_layer<GameLayer>();

    m_scene->set_camera(m_camera);
    m_layer->set_scene(m_scene);

    auto player = m_scene->registry().create_entity();
    auto enemy = m_scene->registry().create_entity();
    m_player_handle = player->handle();
    m_enemy_handle = enemy->handle();

    // Renderer::set_viewport(0, 0, windwidth, winheight);

    player->add_component<MeshRendererComponent>(R::meshes::square, R::materials::blue);
    player->get_component<TransformComponent>()->rotation = glm::vec3(glm::radians(90.0f), 0.0f, 0.0f);
    player->add_component<SpriteRendererComponent>(glm::vec2(10.0f, 10.0f), colors::blue);

    enemy->add_component<MeshRendererComponent>(R::meshes::square, R::materials::wall);
    enemy->get_component<TransformComponent>()->rotation = glm::vec3(glm::radians(90.0f), 0.0f, 0.0f);
    enemy->get_component<TransformComponent>()->position = glm::vec3(2.0f, 2.0f, 1.0f);
    enemy->add_component<SpriteRendererComponent>(glm::vec2(10.0f, 10.0f), colors::red);
}

void SandboxApp::on_update(float delta_time)
{
    if (InputSystem::action_pressed(actions::quit))
        close();
}

const char *SandboxApp::asset_config()
{
    if (m_asset_config.empty())
    {
        auto fs = FileSystem::get<NativeFileSystem>();
        auto file = fs->open("./sample/assets/manifest.yml", FileMode::READ);
        m_asset_config = file->to_string();
    }
    return m_asset_config.c_str();
}

int main(int argc, char **argv)
{
    SandboxApp app;
    app.initialize();
    app.run();
    return 0;
}