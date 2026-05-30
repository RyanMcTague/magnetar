#pragma once
#include <vector>
#include "magnetar/core/base.h"
#include "magnetar/renderer/vertex_array.h"
#include "magnetar/renderer/vertex_buffer.h"
#include "magnetar/renderer/index_buffer.h"
#include "magnetar/renderer/shader.h"
#include "magnetar/renderer/texture.h"
#include "magnetar/renderer/graphics_device.h"
#include "magnetar/renderer/render_command.h"

namespace magnetar
{
    class MAGNETAR_API Renderer
    {
    public:
        static void initialize();
        static void shutdown();

        static Ref<Shader> create_shader(const std::string &name, const std::string &source);
        static Ref<VertexArray> create_vertex_array();
        static Ref<VertexBuffer> create_vertex_buffer(size_t size, const void *data = nullptr);
        static Ref<IndexBuffer> create_index_buffer(size_t count, const void *data = nullptr);
        static Ref<Texture2D> create_texture2D(const TextureSpecification &spec);

        static void clear(const BufferMask &mask);
        static void draw_arrays(Ref<VertexArray> vao, int count, int offset = 0);
        static void draw_indexed(Ref<VertexArray> vao, Ref<IndexBuffer> ibo);
        static void set_viewport(int x, int y, int width, int height);

        // static void begin_scene(Ref<Camera> camera);
        static void submit(const Ref<Mesh>& mesh, const Ref<Material>& material, const glm::mat4& transform);
        static void end_scene();

    private:
        Renderer() = default;
        static UniqueRef<GraphicsDevice> s_device;
        static std::vector<RenderCommand> s_render_commands;
    };
}
