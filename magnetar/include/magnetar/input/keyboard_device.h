#pragma once
#include "magnetar/core/base.h"
#include "magnetar/input/input_device.h"
#include "magnetar/input/enums.h"

namespace magnetar
{
    class KeyboardDevice : public InputDevice
    {
    public:
        virtual ButtonState get_key_state(KeyboardKey key) const = 0;

        bool is_key_down(KeyboardKey key) const;
        bool is_key_released(KeyboardKey key) const;
        
        bool is_key_up(KeyboardKey key) const;
        bool is_key_pressed(KeyboardKey key) const;
        
        bool is_key_active(KeyboardKey key) const;
        bool is_key_inactive(KeyboardKey key) const;

        InputDeviceType type() const override { return InputDeviceType::KEYBOARD; }
    };
}