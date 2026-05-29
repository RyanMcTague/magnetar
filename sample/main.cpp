#include <magnetar/magnetar.h>
#include <magnetar/platforms/opengl/graphics_device.h>
#include <iostream>
using namespace magnetar;

const char* source = R"""(
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


namespace actions
{
    static constexpr int quit = 0;
}

class SandboxApp final : public Application
{
protected:
    void on_initialize() override;
    void on_update(float delta_time) override;
};

void SandboxApp::on_initialize()
{
}
void SandboxApp::on_update(float delta_time)
{
    if (InputSystem::action_pressed(actions::quit))
        close();
}

int main(int argc, char **argv)
{

    float data[] = {
         1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    SandboxApp app;
    Logger::set_level(LogLevel::trace);
    InputSystem::register_action(actions::quit, KeyboardKey::ESCAPE);

    Ref<OpenGLGraphicsDevice> device = create_reference<OpenGLGraphicsDevice>();
    auto shader = device->create_shader("GL_test.glsl", source);

    auto vbo = device->create_vertex_buffer(sizeof(data), data);
    auto vao = device->create_vertex_array();
    vbo->push_layout_element("a_position", RendererDataType::VEC3);
    vao->add_vertex_buffer(vbo);

    app.run();
    return 0;
}