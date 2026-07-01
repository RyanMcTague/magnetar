#include "magnetar/renderer/renderer.h"
#include "magnetar/renderer/backend/opengl/graphics_device.h"

magnetar::UniqueRef<magnetar::GraphicsDevice> magnetar::Renderer::s_device = nullptr;
glm::mat4 magnetar::Renderer::s_view_projection = glm::mat4(1.0f);
magnetar::Ref<magnetar::ShaderLibrary> magnetar::Renderer::s_shader_library = nullptr;

void magnetar::Renderer::initialize()
{
    static bool first = true;
    if (!first)
        return;
    first = false;
    s_device = create_unique_reference<GLGraphicsDevice>();
    s_shader_library = create_reference<ShaderLibrary>();
}

void magnetar::Renderer::shutdown()
{
    s_shader_library = nullptr;
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

magnetar::Ref<magnetar::Texture2D> magnetar::Renderer::create_texture2D(const TextureSpecification &spec, const void *data)
{
    return s_device->create_texture2D(spec, data);
}

void magnetar::Renderer::clear(const BufferMask &mask)
{
    s_device->clear(mask);
}

void magnetar::Renderer::draw_arrays(DrawMode mode, Ref<VertexArray> vao, int count, int offset)
{
    s_device->draw_arrays(mode, vao, count, offset);
}

void magnetar::Renderer::draw_indexed(DrawMode mode, Ref<VertexArray> vao, Ref<IndexBuffer> ibo)
{
    s_device->draw_indexed(mode, vao, ibo);
}

void magnetar::Renderer::set_viewport(int x, int y, int width, int height)
{
    s_device->set_viewport(x, y, width, height);
}

void magnetar::Renderer::set_clear_color(const glm::vec4 &color)
{
    s_device->set_clear_color(color);
}

void magnetar::Renderer::set_pixel_alignment(PixelStoreMode mode, int count)
{
    s_device->set_pixel_alignment(mode, count);
}

void magnetar::Renderer::set_blend_enabled(bool enabled)
{
    s_device->set_blend_enabled(enabled);
}

void magnetar::Renderer::set_blend_func(BlendFactor src, BlendFactor dst)
{
    s_device->set_blend_func(src, dst);
}