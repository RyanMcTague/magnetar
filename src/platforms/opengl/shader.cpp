#include <glm/gtc/type_ptr.hpp>
#include "magnetar/platforms/opengl/shader.h"
#include "magnetar/utils/enum_utils.h"
#include "magnetar/platforms/opengl/helpers.h"
#include "magnetar/platforms/opengl/shader_compiler.h"
magnetar::OpenGLShader::OpenGLShader(const std::string &name, GLuint handle)
    : m_handle(handle), m_name(name)
{
    GLint attribute_count, uniform_count;
    glGetProgramiv(m_handle, GL_ACTIVE_ATTRIBUTES, &attribute_count);
    glGetProgramiv(m_handle, GL_ACTIVE_UNIFORMS, &uniform_count);
    for (GLint i = 0; i < attribute_count; i++)
    {
        Variable var;
        const int buffer_size = 256;
        GLchar name[buffer_size];
        GLenum type;
        GLsizei length;
        GLint size;
        glGetActiveAttrib(m_handle, i, buffer_size, &length, &size, &type, name);

        var.length = length;
        var.location = glGetAttribLocation(m_handle, name);
        var.name = name;
        var.size = size;
        var.type = OpenGLHelpers::convert_renderer_type(type);
        m_attributes.emplace(var.name, var);
    }

    for (GLint i = 0; i < uniform_count; i++)
    {
        Variable var;
        const int buffer_size = 256;
        GLchar name[buffer_size];
        GLenum type;
        GLsizei length;
        GLint size;
        glGetActiveUniform(m_handle, i, buffer_size, &length, &size, &type, name);

        var.length = length;
        var.location = glGetUniformLocation(m_handle, name);
        var.name = name;
        var.size = size;
        var.type = OpenGLHelpers::convert_renderer_type(type);
        m_uniforms.emplace(var.name, var);
    }
}

magnetar::Ref<magnetar::OpenGLShader> magnetar::OpenGLShader::factory(const std::string &name, const std::string &source)
{
    OpenGLShaderCompiler compiler(source);
    compiler.compile();
    compiler.link();

    if (compiler.has_errors())
    {
        for (auto &error : compiler.errors())
            LOG_ERROR(logger::tags::renderer, "{}: {}", name, error.to_string());
        return nullptr;
    }
    return create_reference<OpenGLShader>(name, compiler.program());
}

magnetar::OpenGLShader::~OpenGLShader()
{
    if (m_handle)
        glDeleteProgram(m_handle);
}

void magnetar::OpenGLShader::bind() const
{
    glUseProgram(m_handle);
}

void magnetar::OpenGLShader::unbind() const
{
    glUseProgram(0);
}
bool magnetar::OpenGLShader::exists() const
{
    return m_handle != 0;
}

void magnetar::OpenGLShader::set_int(const std::string &name, int value) const
{
    GLint location = uniform_location(name, RendererDataType::INT);
    if (location < 0)
        return;
    glUniform1i(location, value);
}

void magnetar::OpenGLShader::set_float(const std::string &name, float value) const
{
    GLint location = uniform_location(name, RendererDataType::FLOAT);
    if (location < 0)
        return;
    glUniform1f(location, value);
}

void magnetar::OpenGLShader::set_vec2(const std::string &name, const glm::vec2 &value) const
{
    GLint location = uniform_location(name, RendererDataType::VEC2);
    if (location < 0)
        return;
    glUniform2f(location, value.x, value.y);
}
void magnetar::OpenGLShader::set_vec3(const std::string &name, const glm::vec3 &value) const
{
    GLint location = uniform_location(name, RendererDataType::VEC3);
    if (location < 0)
        return;
    glUniform3f(location, value.x, value.y, value.z);
}

void magnetar::OpenGLShader::set_vec4(const std::string &name, const glm::vec4 &value) const
{
    GLint location = uniform_location(name, RendererDataType::VEC4);
    if (location < 0)
        return;
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void magnetar::OpenGLShader::set_mat2(const std::string &name, const glm::mat2 &value) const
{
    GLint location = uniform_location(name, RendererDataType::MAT2);
    if (location < 0)
        return;
    glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void magnetar::OpenGLShader::set_mat3(const std::string &name, const glm::mat3 &value) const
{
    GLint location = uniform_location(name, RendererDataType::MAT3);
    if (location < 0)
        return;
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void magnetar::OpenGLShader::set_mat4(const std::string &name, const glm::mat4 &value) const
{
    GLint location = uniform_location(name, RendererDataType::MAT4);
    if (location < 0)
        return;
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void magnetar::OpenGLShader::set_mat2x3(const std::string &name, const glm::mat2x3 &value) const
{
    GLint location = uniform_location(name, RendererDataType::MAT2X3);
    if (location < 0)
        return;
    glUniformMatrix2x3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void magnetar::OpenGLShader::set_mat2x4(const std::string &name, const glm::mat2x4 &value) const
{
    GLint location = uniform_location(name, RendererDataType::MAT2X4);
    if (location < 0)
        return;
    glUniformMatrix2x4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void magnetar::OpenGLShader::set_mat3x2(const std::string &name, const glm::mat3x2 &value) const
{
    GLint location = uniform_location(name, RendererDataType::MAT3X2);
    if (location < 0)
        return;
    glUniformMatrix3x2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void magnetar::OpenGLShader::set_mat3x4(const std::string &name, const glm::mat3x4 &value) const
{
    GLint location = uniform_location(name, RendererDataType::MAT3X4);
    if (location < 0)
        return;
    glUniformMatrix3x4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void magnetar::OpenGLShader::set_mat4x2(const std::string &name, const glm::mat4x2 &value) const
{
    GLint location = uniform_location(name, RendererDataType::MAT4X2);
    if (location < 0)
        return;
    glUniformMatrix4x2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void magnetar::OpenGLShader::set_mat4x3(const std::string &name, const glm::mat4x3 &value) const
{
    GLint location = uniform_location(name, RendererDataType::MAT4X3);
    if (location < 0)
        return;
    glUniformMatrix4x3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

GLint magnetar::OpenGLShader::uniform_location(const std::string &name, RendererDataType target_type) const
{
    auto it = m_uniforms.find(name);
    if (it == m_uniforms.end())
    {
        LOG_ERROR(logger::tags::renderer, "uniform '{}' does not exist in shader {}", name, m_name);
        return -1;
    }

    if (it->second.type != target_type)
    {
        LOG_ERROR(logger::tags::renderer, "expected uniform {} to be a {} but is a {} in shader {}",
                  it->second.name, enum_utils::lowercase_name(target_type), enum_utils::lowercase_name(it->second.type), m_name);
        return -1;
    }

    return it->second.location;
}