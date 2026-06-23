#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    enum class MAGNETAR_API DrawMode
    {
        TRIANGLES,
        LINES
    };

    enum class MAGNETAR_API ShaderType
    {
        VERTEX = 0,
        FRAGMENT
    };

    enum class MAGNETAR_API ShaderErrorLevel
    {
        ERROR = 0
    };

    enum class MAGNETAR_API ShaderErrorType
    {
        COMPILE = 0,
        LINK
    };

    enum class MAGNETAR_API TextureFormat
    {
        NONE = 0,
        R8,
        RA8,
        RGB8,
        RGBA8,
        RGBA16F,
        DEPTH24_STENCIL8
    };

    enum class MAGNETAR_API TextureFilter
    {
        NEAREST = 0,
        LINEAR
    };

    enum class MAGNETAR_API TextureWrap
    {
        REPEAT = 0,
        CLAMP_TO_EDGE
    };

    enum class MAGNETAR_API RendererDataType
    {
        INT = 0,
        FLOAT,
        VEC2,
        VEC3,
        VEC4,
        MAT2,
        MAT3,
        MAT4,
        MAT2X3,
        MAT2X4,
        MAT3X2,
        MAT3X4,
        MAT4X2,
        MAT4X3,
        TEXTURE2D
    };

    MAGNETAR_API inline size_t renderer_data_type_size(RendererDataType type)
    {
        size_t size = 0;
        switch (type)
        {
        case RendererDataType::INT:
            size = sizeof(int);
            break;
        case RendererDataType::FLOAT:
            size = sizeof(float);
            break;
        case RendererDataType::VEC2:
            size = 2 * sizeof(float);
            break;
        case RendererDataType::VEC3:
            size = 3 * sizeof(float);
            break;
        case RendererDataType::VEC4:
            size = 4 * sizeof(float);
            break;
        case RendererDataType::MAT2:
            size = 2 * 2 * sizeof(float);
            break;
        case RendererDataType::MAT3:
            size = 3 * 3 * sizeof(float);
            break;
        case RendererDataType::MAT4:
            size = 4 * 4 * sizeof(float);
            break;
        case RendererDataType::MAT2X3:
            size = 2 * 3 * sizeof(float);
            break;
        case RendererDataType::MAT2X4:
            size = 2 * 4 * sizeof(float);
            break;
        case RendererDataType::MAT3X2:
            size = 3 * 2 * sizeof(float);
            break;
        case RendererDataType::MAT3X4:
            size = 3 * 4 * sizeof(float);
            break;
        case RendererDataType::MAT4X2:
            size = 4 * 2 * sizeof(float);
            break;
        case RendererDataType::MAT4X3:
            size = 4 * 3 * sizeof(float);
            break;
        default:
            break;
        }
        return size;
    }
}