#pragma once
#include "magnetar/core/base.h"
#include "magnetar/input/enums.h"

namespace magnetar
{
    struct MAGNETAR_API InputAction
    {
        InputDeviceType input_type;
        KeyboardKey keyboard_key;
        MouseButton mouse_button;

        InputAction() = default;
        InputAction(InputDeviceType type, KeyboardKey key)
            : input_type(type), keyboard_key(key) {}
        InputAction(InputDeviceType type, MouseButton button)
            : input_type(type), mouse_button(button) {}
    };
}