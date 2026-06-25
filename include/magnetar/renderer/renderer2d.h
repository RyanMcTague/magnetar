#pragma once
#include <glm/glm.hpp>
#include "magnetar/math/rect.h"
#include "magnetar/core/base.h"
#include "magnetar/renderer/texture.h"
#include "magnetar/renderer/font.h"

namespace magnetar
{
    class MAGNETAR_API Renderer2D
    {
    public:
        static void initialize();
        static void shutdown();

        static void start(const glm::mat4 &view_projection);
        static void submit();

        static void draw_quad(const glm::mat4 &transform, const glm::vec4 &color, const Ref<Texture2D> &texture = nullptr, const Rect& rect = Rect(1.0f));
        static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);
        static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color);
        
        static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, const Rect& rect = Rect(1.0f));
        static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, const Rect& rect = Rect(1.0f));

        static void draw_text(const std::string& text, Ref<Font> font, const glm::vec3 &position, const glm::vec4& color);
    };
}