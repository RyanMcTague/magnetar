#pragma once
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/renderer/shader.h"
#include "magnetar/renderer/texture.h"

namespace magnetar
{
    class MAGNETAR_API Material
    {
    public:
        Material(Ref<Shader> shader);

        void bind() const;
        void unbind() const;

        void set_texture(const std::string& name, Ref<Texture> texture);
        void set_float(const std::string& name, float value);

    private:
        Ref<Shader> m_shader;
        std::unordered_map<std::string, Ref<Texture>> m_textures;
        std::unordered_map<std::string, float> m_floats;
    };
}