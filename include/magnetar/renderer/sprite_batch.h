#pragma once
#include <glm/glm.hpp>
#include "magnetar/core/base.h"
#include "magnetar/renderer/vertex_array.h"
#include "magnetar/renderer/vertex_buffer.h"
#include "magnetar/renderer/shader.h"
namespace magnetar
{
    class MAGNETAR_API SpriteBatch
    {
    public:
        struct Vertex
        {
            glm::vec4 position;
            glm::vec4 color;
        };

        static constexpr uint32_t VERTICES_PER_QUAD = 4;
        static constexpr uint32_t INDICES_PER_QUAD = 6;

        SpriteBatch(uint32_t max_quads);
        ~SpriteBatch();

        SpriteBatch(const SpriteBatch &) = delete;
        SpriteBatch &operator=(const SpriteBatch &) = delete;

        void start(const glm::mat4 &view_projection);
        void render();

        void draw_quad(const glm::mat4 &transform, const glm::vec4 &color);
        void draw_quad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);
        void draw_quad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color);

    private:
        uint32_t m_num_quads;
        uint32_t m_current_quad_count;
        size_t m_vertex_data_count;
        Vertex *m_vertex_data;
        size_t m_vertex_index;
        Ref<VertexArray> m_vertex_array;
        Ref<VertexBuffer> m_vertex_buffer;
        Ref<Shader> m_shader;
        glm::mat4 m_view_projection;
    };
}