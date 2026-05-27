#pragma once 
#include "magnetar/core/base.h"

namespace magnetar
{
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
    };
}