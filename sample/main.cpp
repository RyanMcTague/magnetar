#include <magnetar/magnetar.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace magnetar;

namespace R
{
    namespace shaders
    {
        AssetHandle GL_texture = 1000;
        AssetHandle GL_color = 1005;
    }

    namespace textures
    {
        AssetHandle wall = 1001;
    }

    namespace materials
    {
        AssetHandle wall = 1002;
        AssetHandle blue = 1005;
    }

    namespace meshes
    {
        AssetHandle square = 1003;
        AssetHandle cube = 1004;
    }
}

namespace actions
{
    static constexpr int quit = 0;
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
    EntityHandle m_player_handle;
    EntityHandle m_enemy_handle;
};

void SandboxApp::on_initialize()
{
    InputSystem::register_action(actions::quit, KeyboardKey::ESCAPE);

    AssetManager::load<Texture2D>("./sample/assets/images/wall.jpg");
    AssetManager::load<Shader>("./sample/assets/shaders/GL_texture.glsl");
    AssetManager::load<Material>("./sample/assets/materials/wall.material");
    AssetManager::load<Mesh>("./sample/assets/models/square.obj");
    AssetManager::load<Mesh>("./sample/assets/models/cube.obj");
    AssetManager::load<Shader>("./sample/assets/shaders/GL_color.glsl");
    AssetManager::load<Material>("./sample/assets/materials/blue.material");

    auto aspect_ratio = get_window()->aspect_ratio();
    float y = 4.0f;
    float x = y * aspect_ratio;
    m_camera = create_reference<Camera2D>(-x, x, y, -y, -1.0, 1.0);

    m_scene = create_reference<Scene>();
    m_scene->set_camera(m_camera);

    m_layer = push_layer<GameLayer>();
    m_layer->set_scene(m_scene);

    auto player = m_scene->registry().create_entity();
    m_player_handle = player->handle();

    player->add_component<MeshRendererComponent>(R::meshes::square, R::materials::blue);
    player->get_component<TransformComponent>()->rotation = glm::vec3(glm::radians(90.0f), 0.0f, 0.0f);

    auto enemy = m_scene->registry().create_entity();
    m_enemy_handle = enemy->handle();

    enemy->add_component<MeshRendererComponent>(R::meshes::square, R::materials::wall);
    enemy->get_component<TransformComponent>()->rotation = glm::vec3(glm::radians(90.0f), 0.0f, 0.0f);
    enemy->get_component<TransformComponent>()->position = glm::vec3(2.0f, 2.0f, 1.0f);
}

void SandboxApp::on_update(float delta_time)
{
    if (InputSystem::action_pressed(actions::quit))
        close();
}

const char *SandboxApp::asset_config()
{
    if(m_asset_config.empty())
    {
        auto file = FileSystem::get<NativeFileSystem>()->open("./sample/assets/manifest.yml", FileMode::READ);
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