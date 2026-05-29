#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/vertex_array.h"
#include "magnetar/renderer/vertex_buffer.h"
#include "magnetar/renderer/index_buffer.h"
#include "magnetar/renderer/shader.h"
#include "magnetar/renderer/shader_library.h"

namespace magnetar
{
    class MAGNETAR_API GraphicsDevice
    {
    public:
        GraphicsDevice()
            : m_shader_library(create_reference<ShaderLibrary>()) {}
            
        virtual ~GraphicsDevice() = default;

        GraphicsDevice(const GraphicsDevice &) = delete;
        GraphicsDevice &operator=(const GraphicsDevice &) = delete;

        virtual Ref<Shader> create_shader(const std::string &name, const std::string &source) = 0;
        virtual Ref<Shader> get_shader(const std::string &name) = 0;
        virtual void remove_shader(const std::string &name) = 0;

        virtual Ref<VertexArray> create_vertex_array() = 0;
        virtual Ref<VertexBuffer> create_vertex_buffer(size_t size, const void *data) = 0;
        virtual Ref<IndexBuffer> create_index_buffer(size_t count, uint32_t *data) = 0;

        virtual void clear() const = 0;

        virtual const std::string &name() const = 0;

    protected:
        Ref<ShaderLibrary> shader_library() const { return m_shader_library; }

    private:
        Ref<ShaderLibrary> m_shader_library;
    };
}