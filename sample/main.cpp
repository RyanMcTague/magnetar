#include <magnetar/magnetar.h>
#include <magnetar/renderer/backend/opengl/graphics_device.h>
#include <iostream>
using namespace magnetar;

const char *source = R"""(
#stage vertex
layout (location = 0) in vec3 a_position;
void main()
{
    gl_Position = vec4(a_position, 1.0);
}

#stage fragment
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
)""";

const char *newsource = R"""(
#stage vertex
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;
layout (location = 3) in vec4 a_color;

out vec4 Color;

void main()
{
    Color = a_color;
    gl_Position = vec4(a_position, 1.0);
}

#stage fragment
in vec4 Color;
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
    Ref<GLGraphicsDevice> m_device;
    Ref<Shader> m_shader;
    Ref<VertexArray> m_vao;
    Ref<VertexBuffer> m_vbo;
};

void SandboxApp::on_initialize()
{
    Logger::set_level(LogLevel::trace);
    InputSystem::register_action(actions::quit, KeyboardKey::ESCAPE);

    m_device = create_reference<GLGraphicsDevice>();
    m_shader = m_device->create_shader("GL_test.glsl", source);

    m_vbo = m_device->create_vertex_buffer(sizeof(data), data);
    m_vao = m_device->create_vertex_array();
    m_vbo->push_layout_element("a_position", RendererDataType::VEC3);
    m_vao->add_vertex_buffer(m_vbo);
}

void SandboxApp::on_update(float delta_time)
{
    if (InputSystem::action_pressed(actions::quit))
        close();

    m_device->clear();
    m_shader->bind();
    m_device->draw_arrays(m_vao, 3);
}

int main(int argc, char **argv)
{
    SandboxApp app;
    app.initialize();
    app.run();
    return 0;
}