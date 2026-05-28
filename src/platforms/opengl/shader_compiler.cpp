#include <sstream>
#include <iostream>
#include <magic_enum/magic_enum.hpp>
#include "magnetar/platforms/opengl/shader_compiler.h"
#include "magnetar/utils/string_utils.h"

magnetar::OpenGLShaderCompiler::OpenGLShaderCompiler(const std::string &source)
    : m_text(source)
{
    std::stringstream ss(m_text);
    std::string line;
    ShaderType type;
    int current_line = 0;
    while (std::getline(ss, line, '\n'))
    {
        current_line++;
        auto trimmed = string_utils::trim(line);

        if (trimmed.starts_with('#'))
        {
            auto index = trimmed.find_first_of(" \n\t\r");
            auto str = trimmed.substr(1, index - 1);
            if (str == "stage")
            {
                auto stage = string_utils::trim(trimmed.substr(str.length() + 1));
                if (stage == "vertex")
                    type = ShaderType::VERTEX;
                else if (stage == "fragment")
                    type = ShaderType::FRAGMENT;

                m_sources[type] = SourceEntry{"", current_line};
                continue;
            }
        }
        

        m_sources[type].source += line + "\n";
    }
}

magnetar::OpenGLShaderCompiler::~OpenGLShaderCompiler()
{
    for (auto &shader : m_shaders)
        glDeleteShader(shader);
}

bool magnetar::OpenGLShaderCompiler::compile()
{
    bool result = true;
    for (auto &pair : m_sources)
    {
        auto &source = pair.second;
        GLenum shader_type = 0;

        switch (pair.first)
        {
        case ShaderType::VERTEX:
            shader_type = GL_VERTEX_SHADER;
            break;
        case ShaderType::FRAGMENT:
            shader_type = GL_FRAGMENT_SHADER;
            break;
        default:
            break;
        }

        int success;
        GLuint shader = glCreateShader(shader_type);
        const char* sources[] = {
            "#version 330 core\n#line 1 0\n",
            source.source.c_str()
        };
        glShaderSource(shader, 2, sources, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            result = false;
            add_compile_error(shader, source.line_offset);
        }

        m_shaders.push_back(shader);
    }

    return result;
}

bool magnetar::OpenGLShaderCompiler::link()
{
    int success;

    m_program = glCreateProgram();

    for (auto shader : m_shaders)
        glAttachShader(m_program, shader);
    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);

    if (!success)
        add_link_error(m_program);

    for (auto shader : m_shaders)
        glDeleteShader(shader);

    if (has_errors())
    {
        glDeleteProgram(m_program);
        m_program = 0;
        return false;
    }

    m_shaders.clear();
    return true;
}

void magnetar::OpenGLShaderCompiler::add_compile_error(GLuint shader, int line_offset)
{
    Error error;
    error.error_type = ShaderErrorType::COMPILE;
    int log_length;
    GLint shader_type;
    char *log = nullptr;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
    glGetShaderiv(shader, GL_SHADER_TYPE, &shader_type);

    if (log_length == 0)
        return;

    log = new char[log_length];
    glGetShaderInfoLog(shader, log_length, nullptr, log);

    std::stringstream ss(log);
    std::string segment;
    int segment_index = 0;

    switch (shader_type)
    {
    case GL_VERTEX_SHADER:
        error.type = ShaderType::VERTEX;
        break;
    case GL_FRAGMENT_SHADER:
        error.type = ShaderType::FRAGMENT;
        break;
    default:
        break;
    }

    while (std::getline(ss, segment, ':'))
    {
        switch (segment_index)
        {
        case 0:
        {
            std::string error_level = string_utils::trim(segment);
            if (error_level == "ERROR")
                error.level = ShaderErrorLevel::ERROR;
            else
                LOG_WARN(logger::tags::renderer, "unknown shader error level {}", error_level);
        }
        break;
        case 1:
            error.index = std::stoi(string_utils::trim(segment));
            break;
        case 2:
            error.line = std::stoi(string_utils::trim(segment)) + line_offset;
            break;
        case 3:
            error.snippet = string_utils::trim(segment);
            break;
        case 4:
            error.message = string_utils::trim(segment);
            break;
        default:
            break;
        }
        segment_index++;
    }

    delete[] log;
    m_errors.push_back(error);
}

void magnetar::OpenGLShaderCompiler::add_link_error(GLuint program)
{
    Error error;
    error.error_type = ShaderErrorType::LINK;
    int log_length;
    char *log = nullptr;

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length == 0)
        return;

    log = new char[log_length];
    glGetProgramInfoLog(program, log_length, nullptr, log);

    std::stringstream ss(log);
    std::string segment;
    int segment_index = 0;

    while (std::getline(ss, segment, ':'))
    {
        switch (segment_index)
        {
        case 0:
        {
            std::string error_level = string_utils::trim(segment);
            if (error_level == "ERROR")
                error.level = ShaderErrorLevel::ERROR;
            else
                LOG_WARN(logger::tags::renderer, "unknown shader error level {}", error_level);
        }
        break;
        case 1:
            error.message = string_utils::trim(segment);
        default:
            break;
        }
        segment_index++;
    }
    delete[] log;
    m_errors.push_back(error);
}