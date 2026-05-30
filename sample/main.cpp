#include <magnetar/magnetar.h>

using namespace magnetar;

const char *source = R"""(
#stage vertex

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec2 a_normal;
layout (location = 3) in vec4 a_color;

uniform mat4 u_model;
uniform vec4 u_mesh_color;

out vec4 o_color;

void main()
{
    o_color = u_mesh_color;
    gl_Position = u_model * vec4(a_position, 1.0);
}

#stage fragment

in vec4 o_color;
out vec4 FragColor;

void main()
{
    FragColor = o_color;
}
)""";

std::vector<Mesh::Vertex> vertex_data = {
    {
        glm::vec3(1.0f, -1.0f, 0.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
    },
    {
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
    },
    {
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    },
};

std::vector<uint32_t> indx = {0, 1, 2};

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
    BufferMask m_mask;
    glm::mat4 m_model;
};

void SandboxApp::on_initialize()
{
    Logger::set_level(LogLevel::trace);
    InputSystem::register_action(actions::quit, KeyboardKey::ESCAPE);

    m_mask.set(BufferMask::COLOR_BUFFER);

    auto shader = Renderer::create_shader("GL_test.glsl", source);
    m_mesh = create_reference<Mesh>(vertex_data, indx);
    m_material = create_reference<Material>(shader);
    m_material->set_color("u_mesh_color", glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

    m_model = glm::mat4(1.0f);
    m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

void SandboxApp::on_update(float delta_time)
{
    if (InputSystem::action_pressed(actions::quit))
        close();

    Renderer::clear(m_mask);
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