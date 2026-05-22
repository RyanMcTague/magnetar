#include <algorithm>
#include "magnetar/input/input_system.h"
#include "magnetar/input/input_device.h"
#include "magnetar/input/keyboard_device.h"
#include "magnetar/input/mouse_device.h"

magnetar::InputSystem *magnetar::InputSystem::s_instance = nullptr;

magnetar::ButtonState magnetar::input::action_state(MappedInputCode code)
{
    return InputSystem::get()->action_state(code);
}

bool magnetar::input::action_pressed(MappedInputCode code)
{
    return InputSystem::get()->action_pressed(code);
}

bool magnetar::input::action_down(MappedInputCode code)
{
    return InputSystem::get()->action_down(code);
}

bool magnetar::input::action_released(MappedInputCode code)
{
    return InputSystem::get()->action_released(code);
}

bool magnetar::input::action_up(MappedInputCode code)
{
    return InputSystem::get()->action_up(code);
}

bool magnetar::input::action_active(MappedInputCode code)
{
    return InputSystem::get()->action_active(code);
}

bool magnetar::input::action_inactive(MappedInputCode code)
{
    return InputSystem::get()->action_inactive(code);
}

void magnetar::InputSystem::initialize()
{
    if (s_instance)
        return;
    s_instance = new InputSystem();
}

void magnetar::InputSystem::shutdown()
{
    if (!s_instance)
        return;
    delete s_instance;
}

magnetar::InputSystem *magnetar::InputSystem::get()
{
    return s_instance;
}

void magnetar::InputSystem::add_device(UniqueRef<InputDevice> device)
{
    m_devices.push_back(std::move(device));
}

void magnetar::InputSystem::update()
{
    for (auto &device : m_devices)
        device->update();
}

void magnetar::InputSystem::register_action(MappedInputCode code, MouseButton button)
{
    auto it = m_actions.find(code);
    MAGNETAR_ASSERT(it == m_actions.end(), "Input action {} already exists", code);
    m_actions[code] = InputAction(InputDeviceType::MOUSE, button);
}
void magnetar::InputSystem::register_action(MappedInputCode code, KeyboardKey key)
{
    auto it = m_actions.find(code);
    MAGNETAR_ASSERT(it == m_actions.end(), "Input action {} already exists", code);
    m_actions[code] = InputAction(InputDeviceType::KEYBOARD, key);
}

magnetar::ButtonState magnetar::InputSystem::action_state(MappedInputCode code) const
{
    auto action_it = m_actions.find(code);
    MAGNETAR_ASSERT(action_it != m_actions.end(), "Input action {} does not exist", code);
    ButtonState state = ButtonState::UP;

    if (action_it->second.input_type == InputDeviceType::KEYBOARD)
    {
        auto it = std::find_if(
            m_devices.begin(),
            m_devices.end(),
            [](const UniqueRef<InputDevice> &device)
            {
                return device->type() == InputDeviceType::KEYBOARD;
            });
        MAGNETAR_ASSERT(it != m_devices.end(), "no keyboard connected");
        state = static_cast<KeyboardDevice *>(it->get())->get_key_state(action_it->second.keyboard_key);
    }
    else if (action_it->second.input_type == InputDeviceType::MOUSE)
    {
        auto it = std::find_if(
            m_devices.begin(),
            m_devices.end(),
            [](const UniqueRef<InputDevice> &device)
            {
                return device->type() == InputDeviceType::MOUSE;
            });
        MAGNETAR_ASSERT(it != m_devices.end(), "no mouse connected");
        state = static_cast<MouseDevice *>(it->get())->get_button_state(action_it->second.mouse_button);
    }
    return state;
}

bool magnetar::InputSystem::action_pressed(MappedInputCode code) const
{
    return action_state(code) == ButtonState::PRESSED;
}

bool magnetar::InputSystem::action_down(MappedInputCode code) const
{
    return action_state(code) == ButtonState::DOWN;
}

bool magnetar::InputSystem::action_released(MappedInputCode code) const
{
    return action_state(code) == ButtonState::RELEASED;
}

bool magnetar::InputSystem::action_up(MappedInputCode code) const
{
    return action_state(code) == ButtonState::UP;
}

bool magnetar::InputSystem::action_active(MappedInputCode code) const
{
    auto state = action_state(code);
    return state == ButtonState::PRESSED || state == ButtonState::DOWN;
}

bool magnetar::InputSystem::action_inactive(MappedInputCode code) const
{
    auto state = action_state(code);
    return state == ButtonState::RELEASED || state == ButtonState::UP;
}