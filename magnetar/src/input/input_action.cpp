#include "magnetar/input/input_action.h"
#include "magnetar/input/input_device.h"
#include "magnetar/input/keyboard_device.h"
#include "magnetar/input/mouse_device.h"
magnetar::InputAction::InputAction()
    : m_mapped_code(0) {}

magnetar::InputAction::InputAction(const std::string &name, MappedInputCode code, const InputCode &input_code)
    : m_input_code(input_code), m_name(name), m_mapped_code(code)
{
}

magnetar::ButtonState magnetar::InputAction::check_state(InputDevice *device) const
{
    ButtonState state = ButtonState::UP;

    MT_ASSERT(m_input_code.type() == device->type(), "Wrong input type {} for input code", (uint32_t)device->type());

    switch (device->type())
    {
    case InputDeviceType::KEYBOARD:
        state = static_cast<KeyboardDevice *>(device)->get_key_state(m_input_code.get<KeyboardKey>());
        break;
    case InputDeviceType::MOUSE:
        state = static_cast<MouseDevice *>(device)->get_button_state(m_input_code.get<MouseButton>());
    default:
        break;
    }

    return state;
}