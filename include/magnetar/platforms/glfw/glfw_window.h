#pragma once
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/core/window.h"

struct GLFWwindow;

namespace magnetar
{
    class MAGNETAR_API GlfwWindow: public Window
    {
    public:
        GlfwWindow(const WindowProps& props);
        ~GlfwWindow() override;

        int width() const override;
        int height() const override;
        const std::string& title() const override;

        void poll_events() override;
        void swap_buffers() const override;
        bool should_close() const override;
        void* handle() override;

    private:
        int m_width;
        int m_height;
        std::string m_title;
        GLFWwindow* m_handle;
        
    };
}