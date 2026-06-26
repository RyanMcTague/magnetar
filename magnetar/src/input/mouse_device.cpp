#include "magnetar/input/mouse_device.h"

bool magnetar::MouseDevice::is_button_down(MouseButton key) const
{
    return get_button_state(key) == ButtonState::DOWN;
}
bool magnetar::MouseDevice::is_button_released(MouseButton key) const
{
    return get_button_state(key) == ButtonState::DOWN;
}
bool magnetar::MouseDevice::is_button_up(MouseButton key) const
{
    return get_button_state(key) == ButtonState::DOWN;
}
bool magnetar::MouseDevice::is_button_pressed(MouseButton key) const
{
    return get_button_state(key) == ButtonState::DOWN;
}
bool magnetar::MouseDevice::is_button_active(MouseButton key) const
{
    return is_button_down(key) || is_button_pressed(key);
}
bool magnetar::MouseDevice::is_button_inactive(MouseButton key) const
{
    return is_button_up(key) || is_button_released(key);
}