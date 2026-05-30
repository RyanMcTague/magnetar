#include <GLFW/glfw3.h>
#include "magnetar/renderer/backend/opengl/graphics_device.h"
#include "magnetar/renderer/backend/opengl/glad.h"
#include "magnetar/renderer/backend/opengl/helpers.h"
#include "magnetar/renderer/backend/opengl/vertex_array.h"
#include "magnetar/renderer/backend/opengl/vertex_buffer.h"
#include "magnetar/renderer/backend/opengl/shader.h"
#include "magnetar/renderer/backend/opengl/index_buffer.h"
#include "magnetar/renderer/backend/opengl/texture.h"

magnetar::GLGraphicsDevice::GLGraphicsDevice()
{
    LOG_INFO(logger::tags::renderer, "using graphics api: {}", m_name);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

magnetar::Ref<magnetar::Shader> magnetar::GLGraphicsDevice::create_shader(const std::string &name, const std::string &source)
{
    auto shader = GLShader::factory(name, source);
    if (!shader)
        return nullptr;

    return std::static_pointer_cast<Shader>(shader);
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

magnetar::Ref<magnetar::IndexBuffer> magnetar::GLGraphicsDevice::create_index_buffer(size_t size, const void *data)
{
    auto ibo = create_reference<GLIndexBuffer>(size, (const uint32_t *)data);
    return std::static_pointer_cast<IndexBuffer>(ibo);
}
magnetar::Ref<magnetar::Texture2D> magnetar::GLGraphicsDevice::create_texture2D(const TextureSpecification &spec)
{
    auto texture = create_reference<GLTexture2D>(spec);
    return std::static_pointer_cast<Texture2D>(texture);
}

void magnetar::GLGraphicsDevice::clear(const BufferMask& mask) const
{
    GLbitfield bitfield = 0;
    if(mask.test(BufferMask::COLOR_BUFFER))
        bitfield |= GL_COLOR_BUFFER_BIT;
    if(mask.test(BufferMask::DEPTH_BUFFER))
        bitfield |= GL_COLOR_BUFFER_BIT;
    glClear(bitfield);
}

void magnetar::GLGraphicsDevice::draw_arrays(Ref<VertexArray> vao, int count, int offset) const
{
    vao->bind();
    glDrawArrays(GL_TRIANGLES, offset, count);
    vao->unbind();
}

void magnetar::GLGraphicsDevice::draw_indexed(Ref<VertexArray> vao, Ref<IndexBuffer> ibo) const
{
    vao->bind();
    ibo->bind();
    glDrawElements(GL_TRIANGLES, ibo->count(), GL_UNSIGNED_INT, nullptr);
    ibo->unbind();
    vao->unbind();
}

void magnetar::GLGraphicsDevice::set_viewport(int x, int y, int width, int height) const
{
    glViewport(x, y, width, height);
}

void magnetar::GLGraphicsDevice::set_clear_color(const glm::vec4& color) const
{
    glClearColor(color.x, color.y, color.z, color.w);
}