#pragma once
#include <glm/glm.hpp>
#include "magnetar/core/base.h"
#include "magnetar/renderer/texture.h"

namespace magnetar
{
    class MAGNETAR_API Renderer2D
    {
    public:
        static void initialize();
        static void shutdown();

        static void start(const glm::mat4 &view_projection);
        static void submit();

        static void draw_quad(const glm::mat4 &transform, const glm::vec4 &color, const Ref<Texture2D> &texture = nullptr);
        static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);
        static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color);
        
        static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture);
        static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture);
    };
}