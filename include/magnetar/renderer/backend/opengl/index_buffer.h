#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/index_buffer.h"
#include "magnetar/renderer/backend/opengl/glad.h"

namespace magnetar
{
    class GLIndexBuffer : public IndexBuffer
    {
    public:
        GLIndexBuffer(size_t count, const void *data);
        ~GLIndexBuffer();
        
        void bind() const override;
        void unbind() const override;

        void update(const void *data, size_t offset, size_t count) override;
        void copy(const void *destination, size_t offset, size_t count) const override;
        
        size_t size() const override { return m_count * sizeof(uint32_t); }
        size_t count() const override { return m_count; }
        bool exists() const override { return m_handle != 0; }

    private:
        GLuint m_handle;
        size_t m_count;
    };
}