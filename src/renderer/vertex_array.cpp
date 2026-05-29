#include "magnetar/renderer/vertex_array.h"
#include "magnetar/platforms/opengl/vertex_array.h"
magnetar::Ref<magnetar::VertexArray> magnetar::VertexArray::create()
{
    auto vao = create_reference<OpenGLVertexArray>();
    return std::static_pointer_cast<VertexArray>(vao);
}