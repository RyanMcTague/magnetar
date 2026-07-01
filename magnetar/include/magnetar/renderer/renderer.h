#pragma once
#include <vector>
#include "magnetar/core/base.h"
#include "magnetar/renderer/vertex_array.h"
#include "magnetar/renderer/vertex_buffer.h"
#include "magnetar/renderer/index_buffer.h"
#include "magnetar/renderer/shader.h"
#include "magnetar/renderer/texture.h"
#include "magnetar/renderer/graphics_device.h"
#include "magnetar/renderer/camera.h"

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
        static Ref<Texture2D> create_texture2D(const TextureSpecification &spec, const void *data = nullptr);

        static void clear(const BufferMask &mask);
        static void draw_arrays(DrawMode mode, Ref<VertexArray> vao, int count, int offset = 0);
        static void draw_indexed(DrawMode mode, Ref<VertexArray> vao, Ref<IndexBuffer> ibo);
        static void set_viewport(int x, int y, int width, int height);
        static void set_clear_color(const glm::vec4 &color);
        static void set_pixel_alignment(PixelStoreMode mode, int count);
        static void set_blend_enabled(bool enabled);
        static void set_blend_func(BlendFactor src, BlendFactor dst);

        static Ref<ShaderLibrary> shader_library() { return s_shader_library; }

    private:
        Renderer() = default;
        static UniqueRef<GraphicsDevice> s_device;
        static glm::mat4 s_view_projection;
        static Ref<ShaderLibrary> s_shader_library;
    };
}
