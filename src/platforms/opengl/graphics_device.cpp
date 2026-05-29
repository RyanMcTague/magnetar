#include <GLFW/glfw3.h>
#include "magnetar/platforms/opengl/graphics_device.h"
#include "magnetar/platforms/opengl/glad.h"
#include "magnetar/platforms/opengl/vertex_array.h"
#include "magnetar/platforms/opengl/vertex_buffer.h"
#include "magnetar/platforms/opengl/index_buffer.h"
#include "magnetar/platforms/opengl/helpers.h"

magnetar::OpenGLGraphicsDevice::OpenGLGraphicsDevice()
{
    LOG_INFO(logger::tags::renderer, "using graphics api: {}", m_name);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

magnetar::Ref<magnetar::Shader> magnetar::OpenGLGraphicsDevice::create_shader(const std::string &name, const std::string &source)
{
    return shader_library()->create(name, source);
}

magnetar::Ref<magnetar::Shader> magnetar::OpenGLGraphicsDevice::get_shader(const std::string &name)
{
    return shader_library()->get(name);
}

void magnetar::OpenGLGraphicsDevice::remove_shader(const std::string &name)
{
    shader_library()->remove(name);
}

magnetar::Ref<magnetar::VertexArray> magnetar::OpenGLGraphicsDevice::create_vertex_array()
{
    auto vao = create_reference<OpenGLVertexArray>();
    return std::static_pointer_cast<VertexArray>(vao);
}

magnetar::Ref<magnetar::VertexBuffer> magnetar::OpenGLGraphicsDevice::create_vertex_buffer(size_t size, const void *data)
{
    auto vbo = create_reference<OpenGLVertexBuffer>(size, data);
    return std::static_pointer_cast<VertexBuffer>(vbo);
}

magnetar::Ref<magnetar::IndexBuffer> magnetar::OpenGLGraphicsDevice::create_index_buffer(size_t count, uint32_t *data)
{
    auto ibo = create_reference<OpenGLIndexBuffer>(count, data);
    return std::static_pointer_cast<IndexBuffer>(ibo);
}

void magnetar::OpenGLGraphicsDevice::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void magnetar::OpenGLGraphicsDevice::draw_arrays(Ref<VertexArray> vao, int count, int offset) const
{
    vao->bind();
    glDrawArrays(GL_TRIANGLES, offset, count);
    vao->unbind();
}