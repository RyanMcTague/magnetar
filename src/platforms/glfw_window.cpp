#include <GLFW/glfw3.h>
#include "magnetar/platforms/glfw/glfw_window.h"
#include "magnetar/platforms/glfw/glfw_keyboard_device.h"
#include "magnetar/platforms/glfw/glfw_mouse_device.h"
#include "magnetar/events/event_system.h"
#include "magnetar/input/input_system.h"


magnetar::GlfwWindow::GlfwWindow(const WindowProps &props)
    : m_handle(nullptr), m_height(props.height), m_width(props.width), m_title(props.title)
{
    LOG_TRACE("Creating window");
    glfwInit();
    m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_handle);

    InputSystem::add_device(create_unique_reference<GlfwKeyboardDevice>(m_handle));
    InputSystem::add_device(create_unique_reference<GlfwMouseDevice>(m_handle));

}
magnetar::GlfwWindow::~GlfwWindow()
{
    LOG_TRACE("destroying window");
    if (m_handle)
        glfwDestroyWindow(m_handle);
    glfwTerminate();
}
int magnetar::GlfwWindow::width() const
{
    return m_width;
}
int magnetar::GlfwWindow::height() const
{
    return m_height;
}
const std::string &magnetar::GlfwWindow::title() const
{
    return m_title;
}
void magnetar::GlfwWindow::update()
{
    glfwPollEvents();
}
void magnetar::GlfwWindow::swap_buffers() const
{
    glfwSwapBuffers(m_handle);
}
bool magnetar::GlfwWindow::should_close() const
{
    return glfwWindowShouldClose(m_handle);
}
void *magnetar::GlfwWindow::handle()
{
    return m_handle;
}