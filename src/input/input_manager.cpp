#include "magnetar/input/input_manager.h"

void magnetar::InputManager::connect(uint8_t controller)
{
    m_virtual_keyboards[controller] = create_reference<VirtualKeyboard>();
}
magnetar::VirtualKeyState magnetar::InputManager::key_state(VirtualKey key, uint8_t controller) const
{
    return m_virtual_keyboards[controller]->key_state(key);
}
bool magnetar::InputManager::is_key_down(VirtualKey key, uint8_t controller) const
{
    return m_virtual_keyboards[controller]->is_key_down(key);
}
bool magnetar::InputManager::is_key_up(VirtualKey key, uint8_t controller) const
{
    return m_virtual_keyboards[controller]->is_key_up(key);
}
bool magnetar::InputManager::is_key_pressed(VirtualKey key, uint8_t controller) const
{
    return m_virtual_keyboards[controller]->is_key_pressed(key);
}
bool magnetar::InputManager::is_key_released(VirtualKey key, uint8_t controller) const
{
    return m_virtual_keyboards[controller]->is_key_released(key);
}