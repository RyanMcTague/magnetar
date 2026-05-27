#pragma once
#include <glm/glm.hpp>
#include "magnetar/core/base.h"

namespace magnetar
{
    class MAGNETAR_API Shader
    {
    public:
        Shader() = default;
        virtual ~Shader() = default;

        Shader(const Shader &) = delete;
        Shader &operator=(const Shader &) = delete;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual bool exists() const = 0;

        virtual void set_int(const std::string& name, int value) const = 0;
        virtual void set_float(const std::string& name, float value) const = 0;
       
        virtual void set_vec2(const std::string& name, const glm::vec2& value) const = 0;
        virtual void set_vec3(const std::string& name, const glm::vec3& value) const = 0;
        virtual void set_vec4(const std::string& name, const glm::vec4& value) const = 0;
       
        virtual void set_mat2(const std::string& name, const glm::mat2& value) const = 0;
        virtual void set_mat3(const std::string& name, const glm::mat3& value) const = 0;
        virtual void set_mat4(const std::string& name, const glm::mat4& value) const = 0;

        virtual void set_mat2x3(const std::string& name, const glm::mat2x3& value) const = 0;
        virtual void set_mat2x4(const std::string& name, const glm::mat2x4& value) const = 0;
        virtual void set_mat3x2(const std::string& name, const glm::mat3x2& value) const = 0;
        virtual void set_mat3x4(const std::string& name, const glm::mat3x4& value) const = 0;
        virtual void set_mat4x2(const std::string& name, const glm::mat4x2& value) const = 0;
        virtual void set_mat4x3(const std::string& name, const glm::mat4x3& value) const = 0;

        virtual const std::string& name() const = 0;

        operator bool() const { return exists(); }
    };
}