#include "magnetar/renderer/shader.h"
#include "magnetar/platforms/opengl/shader.h"

magnetar::Ref<magnetar::Shader> magnetar::Shader::create(const std::string &name, const std::string &source)
{
    auto shader = OpenGLShader::factory(name, source);
    if (!shader)
        return nullptr;

    return std::static_pointer_cast<Shader>(shader);
}