#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/graphics_device.h"
#include "magnetar/renderer/buffer_mask.h"

namespace magnetar
{
    class MAGNETAR_API GLGraphicsDevice : public GraphicsDevice
    {
    public:
        GLGraphicsDevice();

        Ref<Shader> create_shader(const std::string &name, const std::string &source) override;

        Ref<VertexArray> create_vertex_array() override;
        Ref<VertexBuffer> create_vertex_buffer(size_t size, const void *data = nullptr) override;
        Ref<IndexBuffer> create_index_buffer(size_t size, const void *data = nullptr) override;
        Ref<Texture2D> create_texture2D(const TextureSpecification &spec) override;

        void clear(const BufferMask& mask) const override;
        void draw_arrays(Ref<VertexArray> vao, int count, int offset = 0) const override;
        void draw_indexed(Ref<VertexArray> vao, Ref<IndexBuffer> ibo) const override;
        void set_viewport(int x, int y, int width, int height) const override;
        void set_clear_color(const glm::vec4& color) const override;

        const std::string &name() const override { return m_name; }

    private:
        std::string m_name = "OpenGL";
    };
}