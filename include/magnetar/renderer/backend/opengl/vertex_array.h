#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/backend/opengl/glad.h"
#include "magnetar/renderer/vertex_array.h"

namespace magnetar
{
    class MAGNETAR_API GLVertexArray: public VertexArray
    {
    public:
        GLVertexArray();
        ~GLVertexArray();
        void bind() const override;
        void unbind() const override;
        void add_vertex_buffer(Ref<VertexBuffer> vertex_buffer) override;
    private:
        GLuint m_handle;
    };
}