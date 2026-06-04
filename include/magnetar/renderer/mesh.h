#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "magnetar/core/base.h"
#include "magnetar/renderer/index_buffer.h"
#include "magnetar/renderer/vertex_array.h"
#include "magnetar/renderer/vertex_buffer.h"

namespace magnetar
{
    class MAGNETAR_API IMesh
    {
    public:
        virtual ~IMesh() = default;
        virtual Ref<VertexArray> vertex_array() const  = 0;
        virtual Ref<IndexBuffer> index_buffer() const  = 0;

        virtual void draw() const = 0;
    };

    class MAGNETAR_API Mesh: public IMesh
    {
    public:
        struct Vertex
        {
            glm::vec3 position;
            glm::vec2 texcoord;
            glm::vec3 normal;
            glm::vec4 color;
        };

        Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);

        Ref<VertexArray> vertex_array() const override { return m_vao; }
        Ref<IndexBuffer> index_buffer() const override { return m_ibo; }

        void draw() const override;

    private:
        Ref<VertexArray> m_vao;
        Ref<VertexBuffer> m_vbo;
        Ref<IndexBuffer> m_ibo;
        uint32_t m_index_count;
    };
}