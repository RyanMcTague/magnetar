#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    enum class MAGNETAR_API ScriptFieldType
    {
        NONE = 0,
        BOOL,
        INT,
        FLOAT,
        STRING,
        VEC2,
        VEC3,
        VEC4,
    };

    enum class MAGNETAR_API ScriptLifecycleMethod
    {
        ON_START = 0,
        ON_UPDATE = 1
    };

    enum class MAGNETAR_API ScriptVisibility
    {
        PUBLIC,
        PROTECTED,
        PRIVATE
    };
}