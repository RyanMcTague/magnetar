#include "magnetar/platforms/opengl/vertex_array.h"
#include "magnetar/renderer/vertex_buffer.h"
#include "magnetar/utils/enum_utils.h"
#include "magnetar/platforms/opengl/helpers.h"

magnetar::OpenGLVertexArray::OpenGLVertexArray()
    : m_handle(0)
{
    glGenVertexArrays(1, &m_handle);
}

magnetar::OpenGLVertexArray::~OpenGLVertexArray()
{
    if (m_handle)
        glDeleteVertexArrays(1, &m_handle);
}

void magnetar::OpenGLVertexArray::bind() const
{
    glBindVertexArray(m_handle);
}

void magnetar::OpenGLVertexArray::unbind() const
{
    glBindVertexArray(0);
}

void magnetar::OpenGLVertexArray::add_vertex_buffer(Ref<VertexBuffer> vertex_buffer)
{
    bind();
    vertex_buffer->bind();
    auto stride = (GLsizei)vertex_buffer->layout().stride();
    for (auto &element : vertex_buffer->layout())
    {
        GLenum normalized = element.normalized ? GL_TRUE : GL_FALSE;
        switch (element.type)
        {
        case RendererDataType::INT:
            glEnableVertexAttribArray(element.location);
            glVertexAttribPointer(element.location, 1, GL_INT, normalized, stride, (const void *)element.offset);
            break;
        case RendererDataType::FLOAT:
            glEnableVertexAttribArray(element.location);
            glVertexAttribPointer(element.location, 1, GL_FLOAT, normalized, stride, (const void *)element.offset);
            break;
        case RendererDataType::VEC2:
            glEnableVertexAttribArray(element.location);
            glVertexAttribPointer(element.location, 2, GL_FLOAT, normalized, stride, (const void *)element.offset);
            break;
        case RendererDataType::VEC3:
            glEnableVertexAttribArray(element.location);
            glVertexAttribPointer(element.location, 3, GL_FLOAT, normalized, stride, (const void *)element.offset);
            break;
        case RendererDataType::VEC4:
            glEnableVertexAttribArray(element.location);
            glVertexAttribPointer(element.location, 4, GL_FLOAT, normalized, stride, (const void *)element.offset);
            break;
        default:
            LOG_ERROR(logger::tags::renderer, "unsupported opengl attribute {}", enum_utils::lowercase_name(element.type));
            break;
        }
    }
    unbind();
    VertexArray::add_vertex_buffer(vertex_buffer);
}
