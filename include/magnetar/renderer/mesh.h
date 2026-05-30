#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "magnetar/core/base.h"
#include "magnetar/renderer/index_buffer.h"
#include "magnetar/renderer/vertex_array.h"
#include "magnetar/renderer/vertex_buffer.h"

namespace magnetar
{    
    class MAGNETAR_API Mesh
    {
    public:
        struct Vertex
        {
            glm::vec3 position;
        };

        Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);

        Ref<VertexArray> vertex_array() const { return m_vao; }
        Ref<IndexBuffer> index_buffer() const { return m_ibo; }

        void draw() const;
    private:
        Ref<VertexArray> m_vao;
        Ref<VertexBuffer> m_vbo;
        Ref<IndexBuffer> m_ibo;
        uint32_t m_index_count;
    };
}