
#include <magnetar/magnetar.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace magnetar;

std::vector<Mesh::Vertex> vertex_data = {
    {
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
    },
    {
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
    },
    {
        glm::vec3(0.5f, 0.5f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    },
    {
        glm::vec3(-0.5f, 0.5f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    },
};

std::vector<uint32_t> indx = {0, 1, 2, 2, 1, 3};

namespace actions
{
    static constexpr int quit = 0;
}

class SandboxApp final : public Application
{
protected:
    void on_initialize() override;
    void on_update(float delta_time) override;

private:
    Ref<Mesh> m_mesh;
    Ref<Material> m_material;
    Ref<Camera> m_camera;
    BufferMask m_mask;
    glm::mat4 m_model;
};

void SandboxApp::on_initialize()
{
    Logger::set_level(LogLevel::trace);
    InputSystem::register_action(actions::quit, KeyboardKey::ESCAPE);

    m_mask.set(BufferMask::COLOR_BUFFER);

    m_model = glm::mat4(1.0f);
    m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    auto aspect = get_window()->aspect_ratio();
    float y = 1.0f;
    float x = y * aspect;
    m_camera = create_reference<Camera2D>(-x, x, y, -y, -1.0, 1.0);

    auto texture_handle = AssetManager::load<Texture2D>("./sample/wall.jpg");
    auto shader_handle = AssetManager::load<Shader>("./sample/GL_Sample.glsl");

    auto shader = AssetManager::get<Shader>(shader_handle);
    auto texture = AssetManager::get<Texture2D>(texture_handle);

    m_mesh = create_reference<Mesh>(vertex_data, indx);
    m_material = create_reference<Material>(shader);
    m_material->set_texture("u_texture", texture);
}

void SandboxApp::on_update(float delta_time)
{
    if (InputSystem::action_pressed(actions::quit))
        close();

    m_model = glm::mat4(1.0f);
    m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    m_model = glm::rotate(m_model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Renderer::clear(m_mask);
    Renderer::begin_scene(m_camera);
    Renderer::submit(m_mesh, m_material, m_model);
    Renderer::end_scene();
}

int main(int argc, char **argv)
{
    SandboxApp app;
    app.initialize();
    app.run();
    return 0;
}