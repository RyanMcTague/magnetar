#include <magnetar/magnetar.h>
#include <glm/gtc/matrix_transform.hpp>
#include "assets.h"
using namespace magnetar;

glm::vec4 rgba(uint32_t color)
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
    static constexpr int left = 1;
    static constexpr int right = 2;
    static constexpr int up = 3;
    static constexpr int down = 4;
    static constexpr int fire = 5;
}

namespace colors
{
    const glm::vec4 blue = rgba(0x2596beff);
    const glm::vec4 red = rgba(0xbf2443ff);
    const glm::vec4 gray = rgba(0x666666ff);
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
    Entity m_player;
    Entity m_enemy;
    std::vector<Entity> m_bullets;
    Timer m_bullet_timer;
    glm::vec2 m_viewport;

    void create_bullet();
    void update_bullets();
};

void SandboxApp::on_initialize()
{
    InputSystem::register_action("quit", actions::quit, KeyboardKey::ESCAPE);
    InputSystem::register_action("left", actions::left, KeyboardKey::A);
    InputSystem::register_action("right", actions::right, KeyboardKey::D);
    InputSystem::register_action("up", actions::up, KeyboardKey::W);
    InputSystem::register_action("down", actions::down, KeyboardKey::S);
    InputSystem::register_action("fire", actions::fire, KeyboardKey::SPACE);

    ScriptEngine::load_assembly("./sample/Sample.dll");

    auto aspect_ratio = get_window()->aspect_ratio();
    auto winwidth = get_window()->width();
    auto winheight = get_window()->height();
    float y = 50.0f;
    float x = y * aspect_ratio;
    m_viewport.x = x;
    m_viewport.y = y;
    m_camera = create_reference<Camera2D>(-x, x, y, -y, -1.0, 1.0);

    m_scene = create_reference<Scene>();
    m_layer = push_layer<GameLayer>();

    m_scene->set_camera(m_camera);
    m_layer->set_scene(m_scene);

    // Renderer::set_viewport(0, 0, winwidth, winheight);

    m_player = m_scene->create_entity();
    m_player.add_component(SpriteRendererComponent(glm::vec2(10.0f, 10.0f), colors::blue));
    m_player.add_component(ScriptComponent("Magnetar.Core.Player"));

    m_enemy = m_scene->create_entity();
    m_enemy.get_component<TransformComponent>().position = glm::vec3(20.0f, 20.0f, 1.0f);
    m_enemy.add_component(SpriteRendererComponent(glm::vec2(10.0f, 10.0f), colors::red));
    m_enemy.add_component(RigidBody2DComponent(glm::vec2(0.0f, -13.0f), 0.0f));
    m_enemy.add_component(ScriptComponent("Magnetar.Core.Enemy"));
}

void SandboxApp::on_update(float delta_time)
{
    if (InputSystem::action_pressed(actions::quit))
        close();

    static float speed = 12.0f;
    if (InputSystem::action_down(actions::left))
        m_player.get_component<TransformComponent>().position.x -= speed * delta_time;
    if (InputSystem::action_down(actions::right))
        m_player.get_component<TransformComponent>().position.x += speed * delta_time;

    if (InputSystem::action_down(actions::up))
        m_player.get_component<TransformComponent>().position.y += speed * delta_time;
    if (InputSystem::action_down(actions::down))
        m_player.get_component<TransformComponent>().position.y -= speed * delta_time;

    if (InputSystem::action_pressed(actions::fire))
        create_bullet();

    update_bullets();
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

void SandboxApp::create_bullet()
{
    static float bullet_width = 1.0f;
    float elapsed = (float)((double)m_bullet_timer.elapsed() / 1000.0);
    if (elapsed <= 0.5f)
        return;

    m_bullet_timer.reset();
    auto player_pos = m_player.get_component<TransformComponent>().position;
    auto player_size = m_player.get_component<SpriteRendererComponent>().size;

    auto bullet = m_scene->create_entity();
    bullet.get_component<TransformComponent>().position = glm::vec3(
        player_pos.x + player_size.x * 0.5f - bullet_width * 0.5f,
        player_pos.y,
        0.0f);
    bullet.add_component(SpriteRendererComponent(glm::vec2(bullet_width, bullet_width), colors::gray));
    bullet.add_component(RigidBody2DComponent(glm::vec2(25.0f, 0.0f), 0.0f));
    m_bullets.push_back(bullet);
}

void SandboxApp::update_bullets()
{
    for (auto bullet : m_bullets)
    {
        auto &transform = bullet.get_component<TransformComponent>();
        auto &sr = bullet.get_component<SpriteRendererComponent>();
        if (transform.position.x >= m_viewport.x)
        {
            auto it = std::find_if(m_bullets.begin(), m_bullets.end(), [&bullet](const Entity &e)
                                   { return e.handle() == bullet.handle(); });
            it->mark_destroyed();
            m_bullets.erase(it);
        }
    }
}

int main(int argc, char **argv)
{
    SandboxApp app;
    app.initialize();
    app.run();
    return 0;
}
