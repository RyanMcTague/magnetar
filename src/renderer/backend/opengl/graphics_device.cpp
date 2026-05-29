#include <GLFW/glfw3.h>
#include "magnetar/renderer/backend/opengl/graphics_device.h"
#include "magnetar/renderer/backend/opengl/glad.h"
#include "magnetar/renderer/backend/opengl/vertex_array.h"
#include "magnetar/renderer/backend/opengl/vertex_buffer.h"
#include "magnetar/renderer/backend/opengl/index_buffer.h"
#include "magnetar/renderer/backend/opengl/helpers.h"

magnetar::GLGraphicsDevice::GLGraphicsDevice()
{
    LOG_INFO(logger::tags::renderer, "using graphics api: {}", m_name);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

magnetar::Ref<magnetar::Shader> magnetar::GLGraphicsDevice::create_shader(const std::string &name, const std::string &source)
{
    return shader_library()->create(name, source);
}

magnetar::Ref<magnetar::Shader> magnetar::GLGraphicsDevice::get_shader(const std::string &name)
{
    return shader_library()->get(name);
}

void magnetar::GLGraphicsDevice::remove_shader(const std::string &name)
{
    shader_library()->remove(name);
}

magnetar::Ref<magnetar::VertexArray> magnetar::GLGraphicsDevice::create_vertex_array()
{
    auto vao = create_reference<GLVertexArray>();
    return std::static_pointer_cast<VertexArray>(vao);
}

magnetar::Ref<magnetar::VertexBuffer> magnetar::GLGraphicsDevice::create_vertex_buffer(size_t size, const void *data)
{
    auto vbo = create_reference<GLVertexBuffer>(size, data);
    return std::static_pointer_cast<VertexBuffer>(vbo);
}

magnetar::Ref<magnetar::IndexBuffer> magnetar::GLGraphicsDevice::create_index_buffer(size_t count, uint32_t *data)
{
    auto ibo = create_reference<GLIndexBuffer>(count, data);
    return std::static_pointer_cast<IndexBuffer>(ibo);
}

void magnetar::GLGraphicsDevice::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void magnetar::GLGraphicsDevice::draw_arrays(Ref<VertexArray> vao, int count, int offset) const
{
    vao->bind();
    glDrawArrays(GL_TRIANGLES, offset, count);
    vao->unbind();
}