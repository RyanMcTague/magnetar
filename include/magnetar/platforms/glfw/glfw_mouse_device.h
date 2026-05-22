#pragma once
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/input/mouse_device.h"

struct GLFWwindow;

namespace magnetar
{
    class MAGNETAR_API GlfwMouseDevice : public MouseDevice
    {
    public:
        GlfwMouseDevice(GLFWwindow *window);
        
        ButtonState get_button_state(MouseButton button) const override;
        Vector2D get_position() const override;

        void update() override;
        const std::string &name() const override;

    private:
        GLFWwindow *m_window;
        Vector2D m_position;
        std::string m_name;
        std::unordered_map<MouseButton, ButtonState> m_buttonstates;
    };
}
