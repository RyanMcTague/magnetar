#include "magnetar/platforms/opengl/index_buffer.h"

magnetar::OpenGLIndexBuffer::OpenGLIndexBuffer(size_t count, uint32_t *data)
    : m_handle(0), m_count(count)
{
    glGenBuffers(1, &m_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
    if (data)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(uint32_t), data, GL_STATIC_DRAW);
    else
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

magnetar::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    if (m_handle)
        glDeleteBuffers(1, &m_handle);
}

void magnetar::OpenGLIndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}

void magnetar::OpenGLIndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void magnetar::OpenGLIndexBuffer::update(uint32_t *data, size_t offset, size_t count)
{
    if (offset + count > m_count)
    {
        size_t overflow = (offset + count) - m_count;
        LOG_ERROR(logger::tags::renderer, "cannot update index buffer, data overflow of {} indices", overflow);
        return;
    }
    bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, count * sizeof(uint32_t), data);
    unbind();
}

void magnetar::OpenGLIndexBuffer::copy(uint32_t *destination, size_t offset, size_t count) const
{
    if (offset + count > m_count)
    {
        size_t overflow = (offset + count) - m_count;
        LOG_ERROR(logger::tags::renderer, "cannot copy index buffer, data overflow of {} indices", overflow);
        return;
    }
    bind();
    glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, m_count * sizeof(uint32_t), &destination);
    unbind();
}
