#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/enums.h"
#include "magnetar/assets/asset.h"
namespace magnetar
{
    struct MAGNETAR_API TextureSpecification
    {
        uint32_t width = 1;
        uint32_t height = 1;
        TextureFormat format = TextureFormat::RGBA8;
        TextureFilter min_filter = TextureFilter::LINEAR;
        TextureFilter mag_filter = TextureFilter::LINEAR;
        TextureWrap wrap = TextureWrap::REPEAT;
        bool generate_mipmaps = true;
    };

    class MAGNETAR_API Texture: public Asset
    {
    public:
        Texture() = default;
        virtual ~Texture() = default;

        Texture(const Texture &) = delete;
        Texture &operator=(const Texture &) = delete;

        virtual void bind(uint32_t slot) const = 0;
        virtual void unbind() const = 0;

        virtual void set_data(const void *data, uint32_t size) = 0;

        virtual uint32_t width() const = 0;
        virtual uint32_t height() const = 0;

        virtual const TextureSpecification &specification() const = 0;
    };

    class MAGNETAR_API Texture2D : public Texture
    {
    };
}