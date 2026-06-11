
#include <magnetar/magnetar.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace magnetar;

const char *raw_asset_config = R"""(
- guid: 1000
  type: shader
  path: ./sample/assets/shaders/GL_Sample.glsl

- guid: 1001
  type: texture2D
  path: ./sample/assets/images/wall.jpg

- guid: 1002
  type: material
  path: ./sample/assets/materials/wall.material

- guid: 1003
  type: mesh
  path: ./sample/assets/models/square.obj
)""";

namespace R
{
    namespace shaders
    {
        AssetHandle GL_sample = 1000;
    }

    namespace textures
    {
        AssetHandle wall = 1001;
    }

    namespace materials
    {
        AssetHandle wall = 1002;
    }

    namespace meshes
    {
        AssetHandle square = 1003;
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
    void on_render() override;
    const char *asset_config() override { return raw_asset_config; }

private:
    Ref<Camera> m_camera;
    glm::mat4 m_model;
};

void SandboxApp::on_initialize()
{
    // Logger::set_level(LogLevel::trace);
    InputSystem::register_action(actions::quit, KeyboardKey::ESCAPE);

    AssetManager::load<Texture2D>("./sample/assets/images/wall.jpg");
    AssetManager::load<Shader>("./sample/assets/shaders/GL_Sample.glsl");
    AssetManager::load<Material>("./sample/assets/materials/wall.material");
    AssetManager::load<Mesh>("./sample/assets/models/square.obj");

    m_model = glm::mat4(1.0f);
    m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    auto aspect = get_window()->aspect_ratio();
    float y = 1.0f;
    float x = y * aspect;
    m_camera = create_reference<Camera2D>(-x, x, y, -y, -1.0, 1.0);

    m_model = glm::mat4(1.0f);
    m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    m_model = glm::rotate(m_model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void SandboxApp::on_update(float delta_time)
{
    if (InputSystem::action_pressed(actions::quit))
        close();
}

void SandboxApp::on_render()
{
    Renderer::begin_scene(m_camera);
    Renderer::submit(
        AssetManager::get<Mesh>(R::meshes::square),
        AssetManager::get<Material>(R::materials::wall),
        m_model);
    Renderer::end_scene();
}

int main(int argc, char **argv)
{
    SandboxApp app;
    app.initialize();
    app.run();
    return 0;
}