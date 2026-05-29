#pragma once
#include <vector>
#include <unordered_map>
#include <magic_enum/magic_enum.hpp>
#include "magnetar/core/base.h"
#include "magnetar/renderer/enums.h"
#include "magnetar/renderer/backend/opengl/glad.h"
#include "magnetar/utils/string_utils.h"

namespace magnetar
{
    class MAGNETAR_API GLShaderCompiler
    {
    public:
        struct Error
        {
            ShaderErrorType error_type;
            ShaderType type;
            ShaderErrorLevel level;
            std::string message, snippet;
            int line, index;

            std::string to_string() const
            {
                if(error_type == ShaderErrorType::COMPILE)
                {
                    auto type_str = string_utils::lowercase(std::string(magic_enum::enum_name(type)));
                    return fmt::format("{} {} in {} shader line {}", message, snippet, type_str, line);
                }
                return message;
            }
        };

    public:
        GLShaderCompiler(const std::string &text);
        ~GLShaderCompiler();
        bool compile();
        bool link();

        GLuint program() const { return m_program; }
        bool has_errors() const { return m_errors.size() > 0; }
        const std::vector<Error> &errors() const { return m_errors; }

    private:
        struct SourceEntry
        {
            std::string source;
            int line_offset;
        };
        std::string m_text;
        std::unordered_map<ShaderType, SourceEntry> m_sources;
        std::vector<Error> m_errors;
        std::vector<GLuint> m_shaders;
        GLuint m_program;

        void add_compile_error(GLuint shader, int line_offset);
        void add_link_error(GLuint program);
    };
}