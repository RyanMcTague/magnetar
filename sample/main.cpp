#include <magnetar/magnetar.h>

using namespace magnetar;

const char *source = R"""(
#stage vertex
layout (location = 0) in vec3 a_position;
uniform mat4 u_mvp;
void main()
{
    gl_Position = u_mvp * vec4(a_position, 1.0);
}

#stage fragment
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
)""";

// clang-format off
float data[] = {
     1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
};

uint32_t indices[] = {
    0,1,2
};
// clang-format on

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
    Ref<Shader> m_shader;
    Ref<VertexArray> m_vao;
    Ref<IndexBuffer> m_ibo;
    Ref<VertexBuffer> m_vbo;
    BufferMask m_mask;
    glm::mat4 m_mvp;
};

void SandboxApp::on_initialize()
{
    Logger::set_level(LogLevel::trace);
    InputSystem::register_action(actions::quit, KeyboardKey::ESCAPE);

    m_shader = Renderer::create_shader("GL_test.glsl", source);

    m_vbo = Renderer::create_vertex_buffer(sizeof(data), data);
    m_ibo = Renderer::create_index_buffer(sizeof(indices), indices);
    m_vao = Renderer::create_vertex_array();
    
    m_vbo->push_layout_element("a_position", RendererDataType::VEC3);
    m_vao->add_vertex_buffer(m_vbo);
    m_vao->set_index_buffer(m_ibo);
    m_mask.set(BufferMask::COLOR_BUFFER);

    m_mvp = glm::mat4(1.0f);
    m_mvp = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void SandboxApp::on_update(float delta_time)
{
    if (InputSystem::action_pressed(actions::quit))
        close();

    Renderer::clear(m_mask);
    m_shader->bind();
    m_shader->set_mat4("u_mvp", m_mvp);
    Renderer::draw_indexed(m_vao, m_ibo);
}

int main(int argc, char **argv)
{
    SandboxApp app;
    app.initialize();
    app.run();
    return 0;
}