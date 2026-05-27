#include "magnetar/renderer/vertex_buffer.h"
#include "magnetar/platforms/opengl/vertex_buffer.h"

magnetar::Ref<magnetar::VertexBuffer> magnetar::VertexBuffer::create(size_t size, const void* data)
{
    auto vbo = create_reference<OpenGLVertexBuffer>(size, data);
    return std::static_pointer_cast<VertexBuffer>(vbo);
}