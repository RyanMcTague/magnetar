#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/buffer_layout.h"
namespace magnetar
{
    class MAGNETAR_API VertexBuffer
    {
    public:
        VertexBuffer() = default;
        virtual ~VertexBuffer() = default;

        VertexBuffer(const VertexBuffer &) = delete;
        VertexBuffer &operator=(const VertexBuffer &) = delete;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void update(const void *data, size_t offset, size_t size) = 0;
        virtual void copy(const void *destination, size_t offset, size_t size) const = 0;

        virtual size_t size() const = 0;
        virtual bool exists() const = 0;

        operator bool() const { return exists(); }

        const BufferLayout& layout() const { return m_layout; }

        void push_layout_element(const std::string& name, RendererDataType type, bool normalized = false)
        {
            m_layout.push(name, type, normalized);
        }

    private:
        BufferLayout m_layout;
    };
}