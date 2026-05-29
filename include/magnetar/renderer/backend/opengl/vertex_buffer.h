#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/vertex_buffer.h"
#include "magnetar/renderer/backend/opengl/glad.h"

namespace magnetar
{
    class GLVertexBuffer : public VertexBuffer
    {
    public:
        GLVertexBuffer(size_t size, const void *data);
        ~GLVertexBuffer();
        
        void bind() const override;
        void unbind() const override;

        void update(const void *data, size_t offset, size_t size) override;
        void copy(const void *destination, size_t offset, size_t size) const override;
        
        size_t size() const override { return m_size; }
        bool exists() const override { return m_handle != 0; }

    private:
        GLuint m_handle;
        size_t m_size;
    };
}