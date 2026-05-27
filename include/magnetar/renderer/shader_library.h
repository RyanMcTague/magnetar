#pragma once
#include <unordered_map>
#include "magnetar/core/base.h"

namespace magnetar
{
    class Shader;

    class MAGNETAR_API ShaderLibrary
    {
    public:
        Ref<Shader> create(const std::string& name, const std::string& source);
        Ref<Shader> get(const std::string& name);
        void remove(const std::string& name);        

    private:
        std::unordered_map<std::string, Ref<Shader>> m_shaders;
    };
}