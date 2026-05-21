#include "magnetar/core/input/virtual_keyboard.h"

magnetar::VirtualKeyboard::VirtualKeyboard()
{
    m_keyboard_handle = EventSystem::get()->subscribe<VirtualKeyboardEvent>(this, &VirtualKeyboard::on_keyboard_event);

    m_keystates[VirtualKey::SPACE] = VirtualKeyState::UP;
    m_keystates[VirtualKey::APOSTROPHE] = VirtualKeyState::UP;
    m_keystates[VirtualKey::COMMA] = VirtualKeyState::UP;
    m_keystates[VirtualKey::MINUS] = VirtualKeyState::UP;
    m_keystates[VirtualKey::PERIOD] = VirtualKeyState::UP;
    m_keystates[VirtualKey::SLASH] = VirtualKeyState::UP;
    m_keystates[VirtualKey::NUM0] = VirtualKeyState::UP;
    m_keystates[VirtualKey::NUM1] = VirtualKeyState::UP;
    m_keystates[VirtualKey::NUM2] = VirtualKeyState::UP;
    m_keystates[VirtualKey::NUM3] = VirtualKeyState::UP;
    m_keystates[VirtualKey::NUM4] = VirtualKeyState::UP;
    m_keystates[VirtualKey::NUM5] = VirtualKeyState::UP;
    m_keystates[VirtualKey::NUM6] = VirtualKeyState::UP;
    m_keystates[VirtualKey::NUM7] = VirtualKeyState::UP;
    m_keystates[VirtualKey::NUM8] = VirtualKeyState::UP;
    m_keystates[VirtualKey::NUM9] = VirtualKeyState::UP;
    m_keystates[VirtualKey::SEMICOLON] = VirtualKeyState::UP;
    m_keystates[VirtualKey::EQUAL] = VirtualKeyState::UP;
    m_keystates[VirtualKey::A] = VirtualKeyState::UP;
    m_keystates[VirtualKey::B] = VirtualKeyState::UP;
    m_keystates[VirtualKey::C] = VirtualKeyState::UP;
    m_keystates[VirtualKey::D] = VirtualKeyState::UP;
    m_keystates[VirtualKey::E] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F] = VirtualKeyState::UP;
    m_keystates[VirtualKey::G] = VirtualKeyState::UP;
    m_keystates[VirtualKey::H] = VirtualKeyState::UP;
    m_keystates[VirtualKey::I] = VirtualKeyState::UP;
    m_keystates[VirtualKey::J] = VirtualKeyState::UP;
    m_keystates[VirtualKey::K] = VirtualKeyState::UP;
    m_keystates[VirtualKey::L] = VirtualKeyState::UP;
    m_keystates[VirtualKey::M] = VirtualKeyState::UP;
    m_keystates[VirtualKey::N] = VirtualKeyState::UP;
    m_keystates[VirtualKey::O] = VirtualKeyState::UP;
    m_keystates[VirtualKey::P] = VirtualKeyState::UP;
    m_keystates[VirtualKey::Q] = VirtualKeyState::UP;
    m_keystates[VirtualKey::R] = VirtualKeyState::UP;
    m_keystates[VirtualKey::S] = VirtualKeyState::UP;
    m_keystates[VirtualKey::T] = VirtualKeyState::UP;
    m_keystates[VirtualKey::U] = VirtualKeyState::UP;
    m_keystates[VirtualKey::V] = VirtualKeyState::UP;
    m_keystates[VirtualKey::W] = VirtualKeyState::UP;
    m_keystates[VirtualKey::X] = VirtualKeyState::UP;
    m_keystates[VirtualKey::Y] = VirtualKeyState::UP;
    m_keystates[VirtualKey::Z] = VirtualKeyState::UP;
    m_keystates[VirtualKey::LEFT_BRACKET] = VirtualKeyState::UP;
    m_keystates[VirtualKey::BACKSLASH] = VirtualKeyState::UP;
    m_keystates[VirtualKey::RIGHT_BRACKET] = VirtualKeyState::UP;
    m_keystates[VirtualKey::GRAVE_ACCENT] = VirtualKeyState::UP;
    m_keystates[VirtualKey::WORLD_1] = VirtualKeyState::UP;
    m_keystates[VirtualKey::WORLD_2] = VirtualKeyState::UP;
    m_keystates[VirtualKey::ESCAPE] = VirtualKeyState::UP;
    m_keystates[VirtualKey::ENTER] = VirtualKeyState::UP;
    m_keystates[VirtualKey::TAB] = VirtualKeyState::UP;
    m_keystates[VirtualKey::BACKSPACE] = VirtualKeyState::UP;
    m_keystates[VirtualKey::INSERT] = VirtualKeyState::UP;
    m_keystates[VirtualKey::DELETE] = VirtualKeyState::UP;
    m_keystates[VirtualKey::RIGHT] = VirtualKeyState::UP;
    m_keystates[VirtualKey::LEFT] = VirtualKeyState::UP;
    m_keystates[VirtualKey::DOWN] = VirtualKeyState::UP;
    m_keystates[VirtualKey::UP] = VirtualKeyState::UP;
    m_keystates[VirtualKey::PAGE_UP] = VirtualKeyState::UP;
    m_keystates[VirtualKey::PAGE_DOWN] = VirtualKeyState::UP;
    m_keystates[VirtualKey::HOME] = VirtualKeyState::UP;
    m_keystates[VirtualKey::END] = VirtualKeyState::UP;
    m_keystates[VirtualKey::CAPS_LOCK] = VirtualKeyState::UP;
    m_keystates[VirtualKey::SCROLL_LOCK] = VirtualKeyState::UP;
    m_keystates[VirtualKey::NUM_LOCK] = VirtualKeyState::UP;
    m_keystates[VirtualKey::PRINT_SCREEN] = VirtualKeyState::UP;
    m_keystates[VirtualKey::PAUSE] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F1] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F2] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F3] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F4] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F5] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F6] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F7] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F8] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F9] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F10] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F11] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F12] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F13] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F14] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F15] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F16] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F17] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F18] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F19] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F20] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F21] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F22] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F23] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F24] = VirtualKeyState::UP;
    m_keystates[VirtualKey::F25] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_0] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_1] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_2] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_3] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_4] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_5] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_6] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_7] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_8] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_9] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_DECIMAL] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_DIVIDE] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_MULTIPLY] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_SUBTRACT] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_ADD] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_ENTER] = VirtualKeyState::UP;
    m_keystates[VirtualKey::KP_EQUAL] = VirtualKeyState::UP;
    m_keystates[VirtualKey::LEFT_SHIFT] = VirtualKeyState::UP;
    m_keystates[VirtualKey::LEFT_CONTROL] = VirtualKeyState::UP;
    m_keystates[VirtualKey::LEFT_ALT] = VirtualKeyState::UP;
    m_keystates[VirtualKey::LEFT_SUPER] = VirtualKeyState::UP;
    m_keystates[VirtualKey::RIGHT_SHIFT] = VirtualKeyState::UP;
    m_keystates[VirtualKey::RIGHT_CONTROL] = VirtualKeyState::UP;
    m_keystates[VirtualKey::RIGHT_ALT] = VirtualKeyState::UP;
    m_keystates[VirtualKey::RIGHT_SUPER] = VirtualKeyState::UP;
    m_keystates[VirtualKey::MENU] = VirtualKeyState::UP;
}

magnetar::VirtualKeyboard::~VirtualKeyboard()
{
    EventSystem::get()->unsubscribe(m_keyboard_handle);
}

magnetar::VirtualKeyState magnetar::VirtualKeyboard::key_state(VirtualKey key) const
{
    auto it = m_keystates.find(key);
    return it->second;
}

bool magnetar::VirtualKeyboard::is_key_down(VirtualKey key) const
{
    return key_state(key) == VirtualKeyState::DOWN || key_state(key) == VirtualKeyState::PRESSED;
}
bool magnetar::VirtualKeyboard::is_key_up(VirtualKey key) const
{
    return key_state(key) == VirtualKeyState::UP || key_state(key) == VirtualKeyState::RELEASED;
}
bool magnetar::VirtualKeyboard::is_key_pressed(VirtualKey key) const
{
    return key_state(key) == VirtualKeyState::PRESSED;
}
bool magnetar::VirtualKeyboard::is_key_released(VirtualKey key) const
{
    return key_state(key) == VirtualKeyState::RELEASED;
}

void magnetar::VirtualKeyboard::on_keyboard_event(const VirtualKeyboardEvent &event)
{
    VirtualKeyState state = m_keystates[event.key];
    if (event.was_pressed)
    {
        switch (state)
        {
        case VirtualKeyState::DOWN:
        case VirtualKeyState::PRESSED:
            m_keystates[event.key] = VirtualKeyState::DOWN;
            break;
        case VirtualKeyState::RELEASED:
        case VirtualKeyState::UP:
            m_keystates[event.key] = VirtualKeyState::PRESSED;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (state)
        {
        case VirtualKeyState::DOWN:
        case VirtualKeyState::PRESSED:
            m_keystates[event.key] = VirtualKeyState::RELEASED;
            break;
        case VirtualKeyState::RELEASED:
        case VirtualKeyState::UP:
            m_keystates[event.key] = VirtualKeyState::UP;
            break;
        default:
            break;
        }
    }
}
