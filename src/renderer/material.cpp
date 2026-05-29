#include "magnetar/renderer/material.h"

magnetar::Material::Material(Ref<Shader> shader)
    : m_shader(shader) {}

void magnetar::Material::bind() const
{
    m_shader->bind();
    uint32_t slot = 0;
    for (auto &[name, texture] : m_textures)
    {
        texture->bind(slot);
        m_shader->set_int(name, slot);
        slot++;
    }

    for (auto &[name, value] : m_floats)
        m_shader->set_float(name, value);
}

void magnetar::Material::unbind() const
{
    m_shader->unbind();
}

void magnetar::Material::set_texture(const std::string &name, Ref<Texture> texture)
{
    m_textures.emplace(name, texture);
}

void magnetar::Material::set_float(const std::string &name, float value)
{
    m_floats.emplace(name, value);
}