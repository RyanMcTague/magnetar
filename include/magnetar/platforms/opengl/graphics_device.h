#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/graphics_device.h"

namespace magnetar
{
    class MAGNETAR_API OpenGLGraphicsDevice: public GraphicsDevice
    {
    public:
        OpenGLGraphicsDevice();

        Ref<Shader> create_shader(const std::string &name, const std::string &source) override;
        Ref<Shader> get_shader(const std::string &name) override;
        void remove_shader(const std::string &name) override;

        Ref<VertexArray> create_vertex_array() override;
        Ref<VertexBuffer> create_vertex_buffer(size_t size, const void *data = nullptr) override;
        Ref<IndexBuffer> create_index_buffer(size_t count, uint32_t *data = nullptr) override;

        void clear() const override;
        void draw_arrays(Ref<VertexArray> vao, int count, int offset = 0) const override;

        const std::string& name() const override { return m_name; }

    private:
        std::string m_name = "OpenGL";
    };
}