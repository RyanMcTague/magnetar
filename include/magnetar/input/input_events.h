#pragma once
#include "magnetar/core/base.h"
#include "magnetar/input/virtual_key.h"

namespace magnetar
{
    struct MAGNETAR_API VirtualKeyboardEvent
    {
        VirtualKey key;
        bool was_pressed;
    };
}