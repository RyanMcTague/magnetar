#include "magnetar/renderer/backend/opengl/vertex_buffer.h"
#include "magnetar/renderer/backend/opengl/helpers.h"
magnetar::GLVertexBuffer::GLVertexBuffer(size_t size, const void *data)
    : m_handle(0), m_size(size)
{
    glGenBuffers(1, &m_handle);
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    if (data)
        glBufferData(GL_ARRAY_BUFFER, m_size, data, GL_STATIC_DRAW);
    else
        glBufferData(GL_ARRAY_BUFFER, m_size, nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

magnetar::GLVertexBuffer::~GLVertexBuffer()
{
    if (m_handle)
        glDeleteBuffers(1, &m_handle);
}

void magnetar::GLVertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}

void magnetar::GLVertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void magnetar::GLVertexBuffer::update(const void *data, size_t offset, size_t size)
{
    if (offset + size > m_size)
    {
        size_t overflow = (offset + size) - m_size;
        LOG_ERROR(logger::tags::renderer, "cannot update vertex buffer, data overflow of {} bytes", overflow);
        return;
    }
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    unbind();
}

void magnetar::GLVertexBuffer::copy(const void *destination, size_t offset, size_t size) const
{
    if (offset + size > m_size)
    {
        size_t overflow = (offset + size) - m_size;
        LOG_ERROR(logger::tags::renderer, "cannot copy vertex buffer, data overflow of {} bytes", overflow);
        return;
    }
    bind();
    glGetBufferSubData(GL_ARRAY_BUFFER, offset, m_size, &destination);
    unbind();
}
