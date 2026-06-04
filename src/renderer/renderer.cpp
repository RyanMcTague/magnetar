#include "magnetar/renderer/renderer.h"
#include "magnetar/renderer/backend/opengl/graphics_device.h"

magnetar::UniqueRef<magnetar::GraphicsDevice> magnetar::Renderer::s_device = nullptr;
std::vector<magnetar::RenderCommand> magnetar::Renderer::s_render_commands;
glm::mat4 magnetar::Renderer::s_view_projection = glm::mat4(1.0f);

void magnetar::Renderer::initialize()
{
    static bool first = true;
    if (!first)
        return;
    first = false;
    s_device = create_unique_reference<GLGraphicsDevice>();
}

void magnetar::Renderer::shutdown()
{
    s_render_commands.clear();
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

void magnetar::Renderer::draw_arrays(Ref<VertexArray> vao, int count, int offset)
{
    s_device->draw_arrays(vao, count, offset);
}

void magnetar::Renderer::draw_indexed(Ref<VertexArray> vao, Ref<IndexBuffer> ibo)
{
    s_device->draw_indexed(vao, ibo);
}

void magnetar::Renderer::set_viewport(int x, int y, int width, int height)
{
    s_device->set_viewport(x, y, width, height);
}

void magnetar::Renderer::set_clear_color(const glm::vec4 &color)
{
    s_device->set_clear_color(color);
}

void magnetar::Renderer::begin_scene(Ref<Camera> camera)
{
    s_view_projection = camera->matrix();
}

void magnetar::Renderer::submit(const Ref<Mesh> &mesh, const Ref<Material> &material, const glm::mat4 &transform)
{
    s_render_commands.emplace_back(mesh, material, transform);
}

void magnetar::Renderer::end_scene()
{
    for (const auto &command : s_render_commands)
    {
        command.material->bind();
        command.material->shader()->set_mat4("u_model", command.transform);
        command.material->shader()->set_mat4("u_view_projection", s_view_projection);
        command.mesh->draw();
    }
    s_render_commands.clear();
    s_view_projection = glm::mat4(1.0f);
}