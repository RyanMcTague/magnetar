#include <magnetar/magnetar.h>
#include <iostream>

using namespace magnetar;

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

const char* source = R"""(
#pragma stage(vertex)
#version 330 core
#line 1 0
layout (location = 0) in vec3 a_position;

void main()
{
    gl_Position = vec4(a_position, 1.0);
}

#pragma stage(fragment)
#version 330 core
#line 1 0
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
)""";

#include "magnetar/platforms/opengl/shader_compiler.h"

int main(int argc, char **argv)
{
    SandboxApp app;
    Logger::set_level(LogLevel::trace);
    InputSystem::register_action(actions::quit, KeyboardKey::ESCAPE);

    opengl::ShaderCompiler compiler(source);
    compiler.compile();
    compiler.link();

    if(compiler.has_errors())
    {
        for(auto& error : compiler.errors())
        {
            LOG_ERROR(logger::tags::renderer, error.to_string());
        }
    }
    app.run();
    return 0;
}