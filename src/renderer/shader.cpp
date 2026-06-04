#include "magnetar/renderer/shader.h"
#include "magnetar/renderer/backend/opengl/shader.h"

magnetar::Ref<magnetar::Shader> magnetar::Shader::create(const std::string &name, const std::string &source)
{
    auto shader = GLShader::factory(name, source);
    if (!shader)
        return nullptr;

    return std::static_pointer_cast<Shader>(shader);
}