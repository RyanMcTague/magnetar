#include <algorithm>
#include <magic_enum/magic_enum.hpp>
#include "magnetar/input/input_system.h"
#include "magnetar/input/input_device.h"
#include "magnetar/input/keyboard_device.h"
#include "magnetar/input/mouse_device.h"
#include "magnetar/utils/string_utils.h"

std::vector<magnetar::UniqueRef<magnetar::InputDevice>> magnetar::InputSystem::s_devices;
std::unordered_map<magnetar::MappedInputCode, magnetar::InputAction> magnetar::InputSystem::s_actions;

void magnetar::InputSystem::shutdown()
{
    s_devices.clear();
    s_actions.clear();
}

void magnetar::InputSystem::add_device(UniqueRef<InputDevice> device)
{
    auto type = magic_enum::enum_name(device->type());
    auto type_string = std::string(type);
    s_devices.push_back(std::move(device));
    LOG_INFO(logger::tags::input, "connected {}", string_utils::lowercase(type_string));
}

void magnetar::InputSystem::update()
{
    for (auto &device : s_devices)
        device->update();
}

void magnetar::InputSystem::register_action(MappedInputCode code, const InputCode &input_code)
{
    auto it = s_actions.find(code);
    MT_ASSERT(it == s_actions.end(), "Input action {} already exists", code);
    std::string input_type_string(magic_enum::enum_name(input_code.type()));
    std::string code_string(input_code.code_string());
    LOG_DEBUG(logger::tags::input, "registered input action {} to {}->{}",
              code,
              string_utils::lowercase(input_type_string),
              string_utils::lowercase(code_string));
    s_actions[code] = InputAction(code, input_code);
}

magnetar::ButtonState magnetar::InputSystem::action_state(MappedInputCode code)
{
    ButtonState state = ButtonState::UP;

    auto action_it = s_actions.find(code);
    MT_ASSERT(action_it != s_actions.end(), "Input action {} does not exist", code);

    const InputAction &action = action_it->second;
    auto it = std::find_if(
        s_devices.begin(),
        s_devices.end(),
        [action](const UniqueRef<InputDevice> &device)
        { return device->type() == action.input_device_type(); });

    if (it == s_devices.end())
        return state;
    return action_it->second.check_state(it->get());
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