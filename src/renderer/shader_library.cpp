#include "magnetar/renderer/shader_library.h"
#include "magnetar/renderer/shader.h"

magnetar::Ref<magnetar::Shader> magnetar::ShaderLibrary::create(const std::string &name, const std::string &source)
{
    auto it = m_shaders.find(name);
    if (it != m_shaders.end())
    {
        LOG_DEBUG(logger::tags::renderer, "found cached shader {}, skipping creation", name);
        return it->second;
    }

    auto shader = Shader::create(name, source);
    if (!shader)
    {
        LOG_ERROR(logger::tags::renderer, "could not create shader {}", name);
        return nullptr;
    }

    LOG_INFO(logger::tags::renderer, "shader {} successfully loaded into library", name);
    m_shaders.emplace(name, shader);
    return shader;
}

magnetar::Ref<magnetar::Shader> magnetar::ShaderLibrary::get(const std::string &name)
{
    auto it = m_shaders.find(name);
    if (it == m_shaders.end())
    {
        LOG_DEBUG(logger::tags::renderer, "shader {} not found in cache", name);
        return nullptr;
    }
    LOG_TRACE(logger::tags::renderer, "shader {} found in cache", name);
    return it->second;
}

void magnetar::ShaderLibrary::remove(const std::string &name)
{
    auto it = m_shaders.find(name);
    if (it == m_shaders.end())
    {
        LOG_DEBUG(logger::tags::renderer, "shader {} not found in cache, skipping deletion", name);
        return;
    }

    m_shaders.erase(it);
    LOG_DEBUG(logger::tags::renderer, "removed shader {} from cache", name);
}