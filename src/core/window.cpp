#include "magnetar/core/window.h"
#include "magnetar/platforms/glfw/glfw_window.h"

magnetar::Ref<magnetar::Window> magnetar::Window::create(const WindowProps& props)
{
    static bool first = true;
    if(first)
    {
        first = false;
        LOG_INFO(logger::tags::application, "using window api: {}", "GLFW");
    }
    auto window = create_reference<GlfwWindow>(props);
    return std::static_pointer_cast<Window>(window);
}