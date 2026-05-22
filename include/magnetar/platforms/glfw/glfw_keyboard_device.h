#pragma once
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/input/keyboard_device.h"

struct GLFWwindow;

namespace magnetar
{
    class MAGNETAR_API GlfwKeyboardDevice: public KeyboardDevice
    {
    public:
        GlfwKeyboardDevice(GLFWwindow* window);
        ButtonState get_key_state(KeyboardKey key) const override;
        
        void update() override;
        const std::string& name() const override;
    private:
        GLFWwindow* m_window;
        std::string m_name;
        std::unordered_map<KeyboardKey, ButtonState> m_keystates;
    };
}