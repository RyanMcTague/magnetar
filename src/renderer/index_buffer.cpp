#include "magnetar/renderer/index_buffer.h"
#include "magnetar/platforms/opengl/index_buffer.h"
magnetar::Ref<magnetar::IndexBuffer> magnetar::IndexBuffer::create(size_t count, uint32_t *data)
{
    auto vbo = create_reference<OpenGLIndexBuffer>(count, data);
    return std::static_pointer_cast<IndexBuffer>(vbo);
}