#pragma once
#include <glm/glm.hpp>
#include "magnetar/core/base.h"
#include "magnetar/input/input_device.h"
#include "magnetar/input/enums.h"
namespace magnetar
{
    class MAGNETAR_API MouseDevice : public InputDevice
    {
    public:
        virtual ButtonState get_button_state(MouseButton button) const = 0;

        bool is_button_down(MouseButton button) const;
        bool is_button_released(MouseButton button) const;

        bool is_button_up(MouseButton button) const;
        bool is_button_pressed(MouseButton button) const;

        bool is_button_active(MouseButton button) const;
        bool is_button_inactive(MouseButton button) const;

        virtual const glm::dvec2& get_position() const = 0;

        InputDeviceType type() const override { return InputDeviceType::MOUSE; }
    };
}
