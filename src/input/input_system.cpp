#include <algorithm>
#include "magnetar/input/input_system.h"
#include "magnetar/input/input_device.h"
#include "magnetar/input/keyboard_device.h"
#include "magnetar/input/mouse_device.h"

std::vector<magnetar::UniqueRef<magnetar::InputDevice>> magnetar::InputSystem::s_devices;
std::unordered_map<magnetar::MappedInputCode, magnetar::InputAction> magnetar::InputSystem::s_actions;

magnetar::ButtonState magnetar::input::action_state(MappedInputCode code)
{
    return InputSystem::action_state(code);
}

bool magnetar::input::action_pressed(MappedInputCode code)
{
    return InputSystem::action_pressed(code);
}

bool magnetar::input::action_down(MappedInputCode code)
{
    return InputSystem::action_down(code);
}

bool magnetar::input::action_released(MappedInputCode code)
{
    return InputSystem::action_released(code);
}

bool magnetar::input::action_up(MappedInputCode code)
{
    return InputSystem::action_up(code);
}

bool magnetar::input::action_active(MappedInputCode code)
{
    return InputSystem::action_active(code);
}

bool magnetar::input::action_inactive(MappedInputCode code)
{
    return InputSystem::action_inactive(code);
}

void magnetar::InputSystem::shutdown()
{
    s_devices.clear();
    s_actions.clear();
}

void magnetar::InputSystem::add_device(UniqueRef<InputDevice> device)
{
    s_devices.push_back(std::move(device));
}

void magnetar::InputSystem::update()
{
    for (auto &device : s_devices)
        device->update();
}

void magnetar::InputSystem::register_action(MappedInputCode code, MouseButton button)
{
    auto it = s_actions.find(code);
    MAGNETAR_ASSERT(it == s_actions.end(), "Input action {} already exists", code);
    s_actions[code] = InputAction(InputDeviceType::MOUSE, button);
}
void magnetar::InputSystem::register_action(MappedInputCode code, KeyboardKey key)
{
    auto it = s_actions.find(code);
    MAGNETAR_ASSERT(it == s_actions.end(), "Input action {} already exists", code);
    s_actions[code] = InputAction(InputDeviceType::KEYBOARD, key);
}

magnetar::ButtonState magnetar::InputSystem::action_state(MappedInputCode code) 
{
    auto action_it = s_actions.find(code);
    MAGNETAR_ASSERT(action_it != s_actions.end(), "Input action {} does not exist", code);
    ButtonState state = ButtonState::UP;

    if (action_it->second.input_type == InputDeviceType::KEYBOARD)
    {
        auto it = std::find_if(
            s_devices.begin(),
            s_devices.end(),
            [](const UniqueRef<InputDevice> &device)
            {
                return device->type() == InputDeviceType::KEYBOARD;
            });
        MAGNETAR_ASSERT(it != s_devices.end(), "no keyboard connected");
        state = static_cast<KeyboardDevice *>(it->get())->get_key_state(action_it->second.keyboard_key);
    }
    else if (action_it->second.input_type == InputDeviceType::MOUSE)
    {
        auto it = std::find_if(
            s_devices.begin(),
            s_devices.end(),
            [](const UniqueRef<InputDevice> &device)
            {
                return device->type() == InputDeviceType::MOUSE;
            });
        MAGNETAR_ASSERT(it != s_devices.end(), "no mouse connected");
        state = static_cast<MouseDevice *>(it->get())->get_button_state(action_it->second.mouse_button);
    }
    return state;
}

bool magnetar::InputSystem::action_pressed(MappedInputCode code) 
{
    return action_state(code) == ButtonState::PRESSED;
}

bool magnetar::InputSystem::action_down(MappedInputCode code) 
{
    return action_state(code) == ButtonState::DOWN;
}

bool magnetar::InputSystem::action_released(MappedInputCode code) 
{
    return action_state(code) == ButtonState::RELEASED;
}

bool magnetar::InputSystem::action_up(MappedInputCode code) 
{
    return action_state(code) == ButtonState::UP;
}

bool magnetar::InputSystem::action_active(MappedInputCode code) 
{
    auto state = action_state(code);
    return state == ButtonState::PRESSED || state == ButtonState::DOWN;
}

bool magnetar::InputSystem::action_inactive(MappedInputCode code) 
{
    auto state = action_state(code);
    return state == ButtonState::RELEASED || state == ButtonState::UP;
}