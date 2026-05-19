#include "magnetar/core/window.h"
#include "magnetar/platforms/glfw/glfw_window.h"

magnetar::Ref<magnetar::Window> magnetar::Window::create(const WindowProps& props)
{
    auto window = create_reference<GlfwWindow>(props);
    return cast_reference<Window>(window);
}