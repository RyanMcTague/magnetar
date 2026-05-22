#include <GLFW/glfw3.h>
#include "magnetar/platforms/glfw/glfw_keyboard_device.h"

namespace magnetar
{
    static std::unordered_map<int, KeyboardKey> s_keymap = {
        {GLFW_KEY_SPACE, KeyboardKey::SPACE},
        {GLFW_KEY_APOSTROPHE, KeyboardKey::APOSTROPHE},
        {GLFW_KEY_COMMA, KeyboardKey::COMMA},
        {GLFW_KEY_MINUS, KeyboardKey::MINUS},
        {GLFW_KEY_PERIOD, KeyboardKey::PERIOD},
        {GLFW_KEY_SLASH, KeyboardKey::SLASH},
        {GLFW_KEY_0, KeyboardKey::NUM0},
        {GLFW_KEY_1, KeyboardKey::NUM1},
        {GLFW_KEY_2, KeyboardKey::NUM2},
        {GLFW_KEY_3, KeyboardKey::NUM3},
        {GLFW_KEY_4, KeyboardKey::NUM4},
        {GLFW_KEY_5, KeyboardKey::NUM5},
        {GLFW_KEY_6, KeyboardKey::NUM6},
        {GLFW_KEY_7, KeyboardKey::NUM7},
        {GLFW_KEY_8, KeyboardKey::NUM8},
        {GLFW_KEY_9, KeyboardKey::NUM9},
        {GLFW_KEY_SEMICOLON, KeyboardKey::SEMICOLON},
        {GLFW_KEY_EQUAL, KeyboardKey::EQUAL},
        {GLFW_KEY_A, KeyboardKey::A},
        {GLFW_KEY_B, KeyboardKey::B},
        {GLFW_KEY_C, KeyboardKey::C},
        {GLFW_KEY_D, KeyboardKey::D},
        {GLFW_KEY_E, KeyboardKey::E},
        {GLFW_KEY_F, KeyboardKey::F},
        {GLFW_KEY_G, KeyboardKey::G},
        {GLFW_KEY_H, KeyboardKey::H},
        {GLFW_KEY_I, KeyboardKey::I},
        {GLFW_KEY_J, KeyboardKey::J},
        {GLFW_KEY_K, KeyboardKey::K},
        {GLFW_KEY_L, KeyboardKey::L},
        {GLFW_KEY_M, KeyboardKey::M},
        {GLFW_KEY_N, KeyboardKey::N},
        {GLFW_KEY_O, KeyboardKey::O},
        {GLFW_KEY_P, KeyboardKey::P},
        {GLFW_KEY_Q, KeyboardKey::Q},
        {GLFW_KEY_R, KeyboardKey::R},
        {GLFW_KEY_S, KeyboardKey::S},
        {GLFW_KEY_T, KeyboardKey::T},
        {GLFW_KEY_U, KeyboardKey::U},
        {GLFW_KEY_V, KeyboardKey::V},
        {GLFW_KEY_W, KeyboardKey::W},
        {GLFW_KEY_X, KeyboardKey::X},
        {GLFW_KEY_Y, KeyboardKey::Y},
        {GLFW_KEY_Z, KeyboardKey::Z},
        {GLFW_KEY_LEFT_BRACKET, KeyboardKey::LEFT_BRACKET},
        {GLFW_KEY_BACKSLASH, KeyboardKey::BACKSLASH},
        {GLFW_KEY_RIGHT_BRACKET, KeyboardKey::RIGHT_BRACKET},
        {GLFW_KEY_GRAVE_ACCENT, KeyboardKey::GRAVE_ACCENT},
        {GLFW_KEY_WORLD_1, KeyboardKey::WORLD_1},
        {GLFW_KEY_WORLD_2, KeyboardKey::WORLD_2},
        {GLFW_KEY_ESCAPE, KeyboardKey::ESCAPE},
        {GLFW_KEY_ENTER, KeyboardKey::ENTER},
        {GLFW_KEY_TAB, KeyboardKey::TAB},
        {GLFW_KEY_BACKSPACE, KeyboardKey::BACKSPACE},
        {GLFW_KEY_INSERT, KeyboardKey::INSERT},
        {GLFW_KEY_DELETE, KeyboardKey::DELETE},
        {GLFW_KEY_RIGHT, KeyboardKey::RIGHT},
        {GLFW_KEY_LEFT, KeyboardKey::LEFT},
        {GLFW_KEY_DOWN, KeyboardKey::DOWN},
        {GLFW_KEY_UP, KeyboardKey::UP},
        {GLFW_KEY_PAGE_UP, KeyboardKey::PAGE_UP},
        {GLFW_KEY_PAGE_DOWN, KeyboardKey::PAGE_DOWN},
        {GLFW_KEY_HOME, KeyboardKey::HOME},
        {GLFW_KEY_END, KeyboardKey::END},
        {GLFW_KEY_CAPS_LOCK, KeyboardKey::CAPS_LOCK},
        {GLFW_KEY_SCROLL_LOCK, KeyboardKey::SCROLL_LOCK},
        {GLFW_KEY_NUM_LOCK, KeyboardKey::NUM_LOCK},
        {GLFW_KEY_PRINT_SCREEN, KeyboardKey::PRINT_SCREEN},
        {GLFW_KEY_PAUSE, KeyboardKey::PAUSE},
        {GLFW_KEY_F1, KeyboardKey::F1},
        {GLFW_KEY_F2, KeyboardKey::F2},
        {GLFW_KEY_F3, KeyboardKey::F3},
        {GLFW_KEY_F4, KeyboardKey::F4},
        {GLFW_KEY_F5, KeyboardKey::F5},
        {GLFW_KEY_F6, KeyboardKey::F6},
        {GLFW_KEY_F7, KeyboardKey::F7},
        {GLFW_KEY_F8, KeyboardKey::F8},
        {GLFW_KEY_F9, KeyboardKey::F9},
        {GLFW_KEY_F10, KeyboardKey::F10},
        {GLFW_KEY_F11, KeyboardKey::F11},
        {GLFW_KEY_F12, KeyboardKey::F12},
        {GLFW_KEY_F13, KeyboardKey::F13},
        {GLFW_KEY_F14, KeyboardKey::F14},
        {GLFW_KEY_F15, KeyboardKey::F15},
        {GLFW_KEY_F16, KeyboardKey::F16},
        {GLFW_KEY_F17, KeyboardKey::F17},
        {GLFW_KEY_F18, KeyboardKey::F18},
        {GLFW_KEY_F19, KeyboardKey::F19},
        {GLFW_KEY_F20, KeyboardKey::F20},
        {GLFW_KEY_F21, KeyboardKey::F21},
        {GLFW_KEY_F22, KeyboardKey::F22},
        {GLFW_KEY_F23, KeyboardKey::F23},
        {GLFW_KEY_F24, KeyboardKey::F24},
        {GLFW_KEY_F25, KeyboardKey::F25},
        {GLFW_KEY_KP_0, KeyboardKey::KP_0},
        {GLFW_KEY_KP_1, KeyboardKey::KP_1},
        {GLFW_KEY_KP_2, KeyboardKey::KP_2},
        {GLFW_KEY_KP_3, KeyboardKey::KP_3},
        {GLFW_KEY_KP_4, KeyboardKey::KP_4},
        {GLFW_KEY_KP_5, KeyboardKey::KP_5},
        {GLFW_KEY_KP_6, KeyboardKey::KP_6},
        {GLFW_KEY_KP_7, KeyboardKey::KP_7},
        {GLFW_KEY_KP_8, KeyboardKey::KP_8},
        {GLFW_KEY_KP_9, KeyboardKey::KP_9},
        {GLFW_KEY_KP_DECIMAL, KeyboardKey::KP_DECIMAL},
        {GLFW_KEY_KP_DIVIDE, KeyboardKey::KP_DIVIDE},
        {GLFW_KEY_KP_MULTIPLY, KeyboardKey::KP_MULTIPLY},
        {GLFW_KEY_KP_SUBTRACT, KeyboardKey::KP_SUBTRACT},
        {GLFW_KEY_KP_ADD, KeyboardKey::KP_ADD},
        {GLFW_KEY_KP_ENTER, KeyboardKey::KP_ENTER},
        {GLFW_KEY_KP_EQUAL, KeyboardKey::KP_EQUAL},
        {GLFW_KEY_LEFT_SHIFT, KeyboardKey::LEFT_SHIFT},
        {GLFW_KEY_LEFT_CONTROL, KeyboardKey::LEFT_CONTROL},
        {GLFW_KEY_LEFT_ALT, KeyboardKey::LEFT_ALT},
        {GLFW_KEY_LEFT_SUPER, KeyboardKey::LEFT_SUPER},
        {GLFW_KEY_RIGHT_SHIFT, KeyboardKey::RIGHT_SHIFT},
        {GLFW_KEY_RIGHT_CONTROL, KeyboardKey::RIGHT_CONTROL},
        {GLFW_KEY_RIGHT_ALT, KeyboardKey::RIGHT_ALT},
        {GLFW_KEY_RIGHT_SUPER, KeyboardKey::RIGHT_SUPER},
        {GLFW_KEY_MENU, KeyboardKey::MENU},
    };
}

magnetar::GlfwKeyboardDevice::GlfwKeyboardDevice(GLFWwindow *window)
    : m_name("GlfwKeyboardDevice"), m_window(window)
{

    for (auto &pair : s_keymap)
        m_keystates[pair.second] = ButtonState::UP;
}

magnetar::ButtonState magnetar::GlfwKeyboardDevice::get_key_state(KeyboardKey key) const
{
    auto it = m_keystates.find(key);
    return it->second;
}
void magnetar::GlfwKeyboardDevice::update()
{
    for (auto &pair : s_keymap)
    {
        KeyboardKey key = pair.second;

        bool is_down = glfwGetKey(m_window, pair.first) == GLFW_PRESS;

        if (is_down)
        {
            switch (m_keystates[key])
            {
            case ButtonState::DOWN:
            case ButtonState::PRESSED:
                m_keystates[key] = ButtonState::DOWN;
                break;
            case ButtonState::RELEASED:
            case ButtonState::UP:
                m_keystates[key] = ButtonState::PRESSED;
                break;
            default:
                break;
            }
        }
        else
        {
            switch (m_keystates[key])
            {
            case ButtonState::DOWN:
            case ButtonState::PRESSED:
                m_keystates[key] = ButtonState::RELEASED;
                break;
            case ButtonState::RELEASED:
            case ButtonState::UP:
                m_keystates[key] = ButtonState::UP;
                break;
            default:
                break;
            }
        }
    }
}
const std::string &magnetar::GlfwKeyboardDevice::name() const
{
    return m_name;
}