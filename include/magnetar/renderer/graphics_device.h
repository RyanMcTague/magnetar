#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/vertex_array.h"
#include "magnetar/renderer/vertex_buffer.h"
#include "magnetar/renderer/index_buffer.h"
#include "magnetar/renderer/shader.h"
#include "magnetar/renderer/shader_library.h"
#include "magnetar/renderer/texture.h"

namespace magnetar
{
    class MAGNETAR_API GraphicsDevice
    {
    public:
        GraphicsDevice() = default;
        virtual ~GraphicsDevice() = default;

        GraphicsDevice(const GraphicsDevice &) = delete;
        GraphicsDevice &operator=(const GraphicsDevice &) = delete;

        virtual Ref<Shader> create_shader(const std::string &name, const std::string &source) = 0;

        virtual Ref<VertexArray> create_vertex_array() = 0;
        virtual Ref<VertexBuffer> create_vertex_buffer(size_t size, const void *data) = 0;
        virtual Ref<IndexBuffer> create_index_buffer(size_t count, const void *data) = 0;
        virtual Ref<Texture2D> create_texture2D(const TextureSpecification& spec) = 0;

        virtual void clear() const = 0;
        virtual void draw_arrays(Ref<VertexArray> vao, int count, int offset) const = 0;
        virtual void draw_indexed(Ref<VertexArray> vao, Ref<IndexBuffer> ibo) const = 0;

        virtual const std::string &name() const = 0;
    };
}