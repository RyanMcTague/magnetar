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
        const glm::dvec2& get_position() const override;

        void update() override;
        const std::string &name() const override;

    private:
        GLFWwindow *m_window;
        glm::dvec2 m_position;
        std::string m_name;
        std::unordered_map<MouseButton, ButtonState> m_buttonstates;
    };
}
