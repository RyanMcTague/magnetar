#pragma once
#include <vector>
#include "magnetar/core/base.h"

namespace magnetar
{
    class VertexBuffer;
    class IndexBuffer;
    
    class MAGNETAR_API VertexArray
    {
    public:
        VertexArray() = default;
        virtual ~VertexArray() = default;

        VertexArray(const VertexArray &) = delete;
        VertexArray &operator=(const VertexArray &) = delete;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void add_vertex_buffer(Ref<VertexBuffer> vertex_buffer) { m_vertex_buffers.push_back(vertex_buffer); }
        virtual void set_index_buffer(Ref<IndexBuffer> index_buffer) { m_index_buffer = index_buffer; }

        Ref<IndexBuffer> index_buffer() const { return m_index_buffer; }
        const std::vector<Ref<VertexBuffer>>& vertex_buffers() const { return m_vertex_buffers; }

    private:
        std::vector<Ref<VertexBuffer>> m_vertex_buffers;
        Ref<IndexBuffer> m_index_buffer;
    };
}