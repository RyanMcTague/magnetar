#include <magnetar/magnetar.h>
#include <glm/gtc/matrix_transform.hpp>
#include "assets.h"
using namespace magnetar;

namespace actions
{
    static constexpr int quit = 0;
    static constexpr int left = 1;
    static constexpr int right = 2;
    static constexpr int up = 3;
    static constexpr int down = 4;
    static constexpr int fire = 5;
}

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
};

void SandboxApp::on_initialize()
{
    InputSystem::register_action("quit", actions::quit, KeyboardKey::ESCAPE);
    InputSystem::register_action("left", actions::left, KeyboardKey::A);
    InputSystem::register_action("right", actions::right, KeyboardKey::D);
    InputSystem::register_action("up", actions::up, KeyboardKey::W);
    InputSystem::register_action("down", actions::down, KeyboardKey::S);
    InputSystem::register_action("fire", actions::fire, KeyboardKey::SPACE);

    ScriptEngine::load_assembly("./sample/Magnetar-ScriptCore.dll");
    ScriptEngine::load_assembly("./sample/Sample.dll");

    auto aspect_ratio = get_window()->aspect_ratio();
    auto winwidth = get_window()->width();
    auto winheight = get_window()->height();
    float y = 160.0f / 2.0f;
    float x = y * aspect_ratio;
    // LOG_DEBUG(nullptr, "resolution {}x{}", x * 2.0f, y * 2.0f);
    m_camera = create_reference<Camera2D>(-x, x, y, -y, -1.0, 1.0);

    m_scene = create_reference<Scene>();
    m_layer = push_layer<GameLayer>();

    m_scene->set_camera(m_camera);
    m_layer->set_scene(m_scene);

    // Renderer::set_viewport(0, 0, winwidth, winheight);
    Entity game_controller = m_scene->create_entity();
    game_controller.get_component<TagComponent>().tag = "game-controller";
    game_controller.add_component(ScriptComponent("Sample.GameController"));

    // Rect a(glm::vec2(-5.0f, -5.0f), glm::vec2(5.0f, 5.0f));
    // Rect b(glm::vec2(-2.0f, -2.0f), glm::vec2(2.0f, 2.0f));
    // LOG_DEBUG(nullptr, b.is_inside(a));
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
