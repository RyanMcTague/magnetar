#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/index_buffer.h"
#include "magnetar/platforms/opengl/glad.h"

namespace magnetar
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(size_t count, uint32_t *data);
        ~OpenGLIndexBuffer();
        
        void bind() const override;
        void unbind() const override;

        void update(uint32_t *data, size_t offset, size_t count) override;
        void copy(uint32_t *destination, size_t offset, size_t count) const override;
        
        size_t size() const override { return m_count * sizeof(uint32_t); }
        size_t count() const override { return m_count; }
        bool exists() const override { return m_handle != 0; }

    private:
        GLuint m_handle;
        size_t m_count;
    };
}