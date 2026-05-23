#include "magnetar/input/input_action.h"
#include "magnetar/input/input_device.h"
#include "magnetar/input/keyboard_device.h"
#include "magnetar/input/mouse_device.h"
magnetar::InputAction::InputAction()
    : m_mapped_code(0) {}

magnetar::InputAction::InputAction(MappedInputCode code, const std::vector<InputCode> &input_codes)
    : m_mapped_code(code)
{
    for (const auto &input_code : input_codes)
        m_input_codes[input_code.type()] = input_code;
}

magnetar::ButtonState magnetar::InputAction::check_state(InputDevice *device, bool *found) const
{
    auto it = m_input_codes.find(device->type());
    ButtonState state = ButtonState::UP;

    if (it == m_input_codes.end())
    {
        if (found)
            *found = false;
        return ButtonState::UP;
    }

    switch (device->type())
    {
    case InputDeviceType::KEYBOARD:
        state = static_cast<KeyboardDevice *>(device)->get_key_state(it->second.get<KeyboardKey>());
        if (found)
            *found = true;
        break;
    case InputDeviceType::MOUSE:
        state = static_cast<MouseDevice *>(device)->get_button_state(it->second.get<MouseButton>());
        if (found)
            *found = true;
    default:
        if (found)
            *found = false;
        break;
    }

    return state;
}