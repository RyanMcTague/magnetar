#include <algorithm>
#include "magnetar/input/input_system.h"
#include "magnetar/input/input_device.h"
#include "magnetar/input/keyboard_device.h"
#include "magnetar/input/mouse_device.h"

std::vector<magnetar::UniqueRef<magnetar::InputDevice>> magnetar::InputSystem::s_devices;
std::unordered_map<magnetar::MappedInputCode, magnetar::InputAction> magnetar::InputSystem::s_actions;

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

void magnetar::InputSystem::register_action(MappedInputCode code, const std::vector<InputCode> &input_codes)
{
    auto it = s_actions.find(code);
    MAGNETAR_ASSERT(it == s_actions.end(), "Input action {} already exists", code);
    s_actions[code] = InputAction(code, input_codes);
}

magnetar::ButtonState magnetar::InputSystem::action_state(MappedInputCode code)
{
    bool was_found = false;
    ButtonState state = ButtonState::UP;
    
    auto action_it = s_actions.find(code);
    MAGNETAR_ASSERT(action_it != s_actions.end(), "Input action {} does not exist", code);

    for (const auto &device : s_devices)
    {
        state = action_it->second.check_state(device.get(), &was_found);
        if (was_found)
            break;
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