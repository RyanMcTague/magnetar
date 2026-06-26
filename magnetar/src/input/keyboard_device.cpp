#include "magnetar/input/keyboard_device.h"

bool magnetar::KeyboardDevice::is_key_down(KeyboardKey key) const
{
    return get_key_state(key) == ButtonState::DOWN;
}
bool magnetar::KeyboardDevice::is_key_up(KeyboardKey key) const
{
    return get_key_state(key) == ButtonState::UP;
}
bool magnetar::KeyboardDevice::is_key_pressed(KeyboardKey key) const
{
    return get_key_state(key) == ButtonState::PRESSED;
}
bool magnetar::KeyboardDevice::is_key_released(KeyboardKey key) const
{
    return get_key_state(key) == ButtonState::RELEASED;
}
bool magnetar::KeyboardDevice::is_key_active(KeyboardKey key) const
{
    return is_key_down(key) || is_key_pressed(key);
}
bool magnetar::KeyboardDevice::is_key_inactive(KeyboardKey key) const
{
    return is_key_up(key) || is_key_released(key);
}