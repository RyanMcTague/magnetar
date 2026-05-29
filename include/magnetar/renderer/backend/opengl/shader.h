#pragma once
#include <vector>
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/renderer/enums.h"
#include "magnetar/renderer/shader.h"
#include "magnetar/renderer/backend/opengl/glad.h"

namespace magnetar
{
    class MAGNETAR_API GLShader : public Shader
    {
    public:
        struct Variable
        {
            GLint location;
            std::string name;
            GLsizei length;
            GLint size;
            RendererDataType type;
        };

    public:
        GLShader(const std::string& name, GLuint handle);
        ~GLShader();

        static Ref<GLShader> factory(const std::string& name, const std::string& source);

        void bind() const override;
        void unbind() const override;

        void set_int(const std::string& name, int value) const override;
        void set_float(const std::string& name, float value) const override;

        void set_vec2(const std::string& name, const glm::vec2& value) const override;
        void set_vec3(const std::string& name, const glm::vec3& value) const override;
        void set_vec4(const std::string& name, const glm::vec4& value) const override;

        void set_mat2(const std::string& name, const glm::mat2& value) const override;
        void set_mat3(const std::string& name, const glm::mat3& value) const override;
        void set_mat4(const std::string& name, const glm::mat4& value) const override;

        void set_mat2x3(const std::string& name, const glm::mat2x3& value) const override;
        void set_mat2x4(const std::string& name, const glm::mat2x4& value) const override;
        void set_mat3x2(const std::string& name, const glm::mat3x2& value) const override;
        void set_mat3x4(const std::string& name, const glm::mat3x4& value) const override;
        void set_mat4x2(const std::string& name, const glm::mat4x2& value) const override;
        void set_mat4x3(const std::string& name, const glm::mat4x3& value) const override;

        bool exists() const override;
        const std::string& name() const override { return m_name; }
        
    private:
        GLuint m_handle;
        std::string m_name;
        std::unordered_map<std::string, Variable> m_attributes;
        std::unordered_map<std::string, Variable> m_uniforms;
        
        GLint uniform_location(const std::string& name, RendererDataType target_type) const;
    };
}
