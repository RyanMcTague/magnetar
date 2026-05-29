#include "magnetar/renderer/renderer.h"
#include "magnetar/renderer/backend/opengl/graphics_device.h"

magnetar::UniqueRef<magnetar::GraphicsDevice> magnetar::Renderer::s_device = nullptr;

void magnetar::Renderer::initialize()
{
    static bool first = true;
    if(!first)
        return;
    first = false;
    s_device = create_unique_reference<GLGraphicsDevice>();
}

void magnetar::Renderer::shutdown()
{
    s_device = nullptr;
}

magnetar::Ref<magnetar::Shader> magnetar::Renderer::create_shader(const std::string &name, const std::string &source)
{
    return s_device->create_shader(name, source);
}

magnetar::Ref<magnetar::VertexArray> magnetar::Renderer::create_vertex_array()
{
    return s_device->create_vertex_array();
}

magnetar::Ref<magnetar::VertexBuffer> magnetar::Renderer::create_vertex_buffer(size_t size, const void *data)
{
    return s_device->create_vertex_buffer(size, data);
}

magnetar::Ref<magnetar::IndexBuffer> magnetar::Renderer::create_index_buffer(size_t count, const void *data)
{
    return s_device->create_index_buffer(count, data);
}

magnetar::Ref<magnetar::Texture2D> magnetar::Renderer::create_texture2D(const TextureSpecification &spec)
{
    return s_device->create_texture2D(spec);
}

void magnetar::Renderer::clear(const BufferMask &mask)
{
    s_device->clear(mask);
}

void magnetar::Renderer::draw_arrays(Ref<VertexArray> vao, int count, int offset)
{
    s_device->draw_arrays(vao, count, offset);
}

void magnetar::Renderer::draw_indexed(Ref<VertexArray> vao, Ref<IndexBuffer> ibo)
{
    s_device->draw_indexed(vao, ibo);
}
