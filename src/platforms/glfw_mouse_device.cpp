#include <GLFW/glfw3.h>
#include "magnetar/platforms/glfw/glfw_mouse_device.h"

namespace magnetar
{
    static std::unordered_map<int, MouseButton> s_buttonmap = {
        {GLFW_MOUSE_BUTTON_LEFT, MouseButton::LEFT},
        {GLFW_MOUSE_BUTTON_MIDDLE, MouseButton::MIDDLE},
        {GLFW_MOUSE_BUTTON_RIGHT, MouseButton::RIGHT},
    };
}

magnetar::GlfwMouseDevice::GlfwMouseDevice(GLFWwindow *window)
    : m_window(window), m_name("GlfwMouseDevice")
{
    for(auto& pair: s_buttonmap)
        m_buttonstates[pair.second] = ButtonState::UP;
}

magnetar::ButtonState magnetar::GlfwMouseDevice::get_button_state(MouseButton button) const
{
    auto it = m_buttonstates.find(button);
    return it->second;
}
magnetar::Vector2D magnetar::GlfwMouseDevice::get_position() const
{
    return m_position;
}
void magnetar::GlfwMouseDevice::update()
{
    glfwGetCursorPos(m_window, &m_position.x, &m_position.y);
    
    for (auto &pair : s_buttonmap)
    {
        MouseButton button = pair.second;

        bool is_down = glfwGetMouseButton(m_window, pair.first) == GLFW_PRESS;

        if (is_down)
        {
            switch (m_buttonstates[button])
            {
            case ButtonState::DOWN:
            case ButtonState::PRESSED:
                m_buttonstates[button] = ButtonState::DOWN;
                break;
            case ButtonState::RELEASED:
            case ButtonState::UP:
                m_buttonstates[button] = ButtonState::PRESSED;
                break;
            default:
                break;
            }
        }
        else
        {
            switch (m_buttonstates[button])
            {
            case ButtonState::DOWN:
            case ButtonState::PRESSED:
                m_buttonstates[button] = ButtonState::RELEASED;
                break;
            case ButtonState::RELEASED:
            case ButtonState::UP:
                m_buttonstates[button] = ButtonState::UP;
                break;
            default:
                break;
            }
        }
    }
}
const std::string &magnetar::GlfwMouseDevice::name() const
{
    return m_name;
}