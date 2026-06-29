#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/assets/asset.h"
#include "magnetar/renderer/texture.h"
namespace magnetar
{
    class MAGNETAR_API Font: public Asset
    {
    public:
        struct Glyph
        {
            glm::vec2 uv0;
            glm::vec2 uv1;

            glm::ivec2 size;
            glm::ivec2 bearing;

            glm::vec2 advance;
        };

        Font(const void* data, size_t size);

        const Glyph &get(char ch) const
        {
            auto it = m_glyphs.find(ch);
            MT_ASSERT(it != m_glyphs.end(), "could not find glyph {}", ch);
            return it->second;
        }

        Ref<Texture2D> texture() const { return m_texture; }
        int size() const { return m_size;}

    private:
        std::unordered_map<char, Glyph> m_glyphs;
        Ref<Texture2D> m_texture;
        int m_size;
    };
}