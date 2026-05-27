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
}