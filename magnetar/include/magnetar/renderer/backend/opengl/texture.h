#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/texture.h"
#include "magnetar/renderer/backend/opengl/glad.h"

namespace magnetar
{
    class MAGNETAR_API GLTexture2D : public Texture2D
    {
    public:
        GLTexture2D(const TextureSpecification &spec, const void* data = nullptr);
        ~GLTexture2D() override;

        void bind(uint32_t slot = 0) const override;
        void unbind() const override;

        void set_data(const void *data, uint32_t size) override;

        uint32_t width() const override { return m_spec.width; }
        uint32_t height() const override { return m_spec.height; }

        const TextureSpecification &specification() const override { return m_spec; }

    private:
        TextureSpecification m_spec;
        GLuint m_handle;
    };
}