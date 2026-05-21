#include <GLFW/glfw3.h>
#include "magnetar/platforms/glfw/glfw_window.h"
#include "magnetar/core/input/input_events.h"
#include "magnetar/core/events/event_system.h"


magnetar::GlfwWindow::GlfwWindow(const WindowProps &props)
    : m_handle(nullptr), m_height(props.height), m_width(props.width), m_title(props.title)
{
    LOG_TRACE("Creating window");
    glfwInit();
    m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_handle);

    m_keymap[GLFW_KEY_SPACE] = VirtualKey::SPACE;
    m_keymap[GLFW_KEY_APOSTROPHE] = VirtualKey::APOSTROPHE;
    m_keymap[GLFW_KEY_COMMA] = VirtualKey::COMMA;
    m_keymap[GLFW_KEY_MINUS] = VirtualKey::MINUS;
    m_keymap[GLFW_KEY_PERIOD] = VirtualKey::PERIOD;
    m_keymap[GLFW_KEY_SLASH] = VirtualKey::SLASH;
    m_keymap[GLFW_KEY_0] = VirtualKey::NUM0;
    m_keymap[GLFW_KEY_1] = VirtualKey::NUM1;
    m_keymap[GLFW_KEY_2] = VirtualKey::NUM2;
    m_keymap[GLFW_KEY_3] = VirtualKey::NUM3;
    m_keymap[GLFW_KEY_4] = VirtualKey::NUM4;
    m_keymap[GLFW_KEY_5] = VirtualKey::NUM5;
    m_keymap[GLFW_KEY_6] = VirtualKey::NUM6;
    m_keymap[GLFW_KEY_7] = VirtualKey::NUM7;
    m_keymap[GLFW_KEY_8] = VirtualKey::NUM8;
    m_keymap[GLFW_KEY_9] = VirtualKey::NUM9;
    m_keymap[GLFW_KEY_SEMICOLON] = VirtualKey::SEMICOLON;
    m_keymap[GLFW_KEY_EQUAL] = VirtualKey::EQUAL;
    m_keymap[GLFW_KEY_A] = VirtualKey::A;
    m_keymap[GLFW_KEY_B] = VirtualKey::B;
    m_keymap[GLFW_KEY_C] = VirtualKey::C;
    m_keymap[GLFW_KEY_D] = VirtualKey::D;
    m_keymap[GLFW_KEY_E] = VirtualKey::E;
    m_keymap[GLFW_KEY_F] = VirtualKey::F;
    m_keymap[GLFW_KEY_G] = VirtualKey::G;
    m_keymap[GLFW_KEY_H] = VirtualKey::H;
    m_keymap[GLFW_KEY_I] = VirtualKey::I;
    m_keymap[GLFW_KEY_J] = VirtualKey::J;
    m_keymap[GLFW_KEY_K] = VirtualKey::K;
    m_keymap[GLFW_KEY_L] = VirtualKey::L;
    m_keymap[GLFW_KEY_M] = VirtualKey::M;
    m_keymap[GLFW_KEY_N] = VirtualKey::N;
    m_keymap[GLFW_KEY_O] = VirtualKey::O;
    m_keymap[GLFW_KEY_P] = VirtualKey::P;
    m_keymap[GLFW_KEY_Q] = VirtualKey::Q;
    m_keymap[GLFW_KEY_R] = VirtualKey::R;
    m_keymap[GLFW_KEY_S] = VirtualKey::S;
    m_keymap[GLFW_KEY_T] = VirtualKey::T;
    m_keymap[GLFW_KEY_U] = VirtualKey::U;
    m_keymap[GLFW_KEY_V] = VirtualKey::V;
    m_keymap[GLFW_KEY_W] = VirtualKey::W;
    m_keymap[GLFW_KEY_X] = VirtualKey::X;
    m_keymap[GLFW_KEY_Y] = VirtualKey::Y;
    m_keymap[GLFW_KEY_Z] = VirtualKey::Z;
    m_keymap[GLFW_KEY_LEFT_BRACKET] = VirtualKey::LEFT_BRACKET;
    m_keymap[GLFW_KEY_BACKSLASH] = VirtualKey::BACKSLASH;
    m_keymap[GLFW_KEY_RIGHT_BRACKET] = VirtualKey::RIGHT_BRACKET;
    m_keymap[GLFW_KEY_GRAVE_ACCENT] = VirtualKey::GRAVE_ACCENT;
    m_keymap[GLFW_KEY_WORLD_1] = VirtualKey::WORLD_1;
    m_keymap[GLFW_KEY_WORLD_2] = VirtualKey::WORLD_2;
    m_keymap[GLFW_KEY_ESCAPE] = VirtualKey::ESCAPE;
    m_keymap[GLFW_KEY_ENTER] = VirtualKey::ENTER;
    m_keymap[GLFW_KEY_TAB] = VirtualKey::TAB;
    m_keymap[GLFW_KEY_BACKSPACE] = VirtualKey::BACKSPACE;
    m_keymap[GLFW_KEY_INSERT] = VirtualKey::INSERT;
    m_keymap[GLFW_KEY_DELETE] = VirtualKey::DELETE;
    m_keymap[GLFW_KEY_RIGHT] = VirtualKey::RIGHT;
    m_keymap[GLFW_KEY_LEFT] = VirtualKey::LEFT;
    m_keymap[GLFW_KEY_DOWN] = VirtualKey::DOWN;
    m_keymap[GLFW_KEY_UP] = VirtualKey::UP;
    m_keymap[GLFW_KEY_PAGE_UP] = VirtualKey::PAGE_UP;
    m_keymap[GLFW_KEY_PAGE_DOWN] = VirtualKey::PAGE_DOWN;
    m_keymap[GLFW_KEY_HOME] = VirtualKey::HOME;
    m_keymap[GLFW_KEY_END] = VirtualKey::END;
    m_keymap[GLFW_KEY_CAPS_LOCK] = VirtualKey::CAPS_LOCK;
    m_keymap[GLFW_KEY_SCROLL_LOCK] = VirtualKey::SCROLL_LOCK;
    m_keymap[GLFW_KEY_NUM_LOCK] = VirtualKey::NUM_LOCK;
    m_keymap[GLFW_KEY_PRINT_SCREEN] = VirtualKey::PRINT_SCREEN;
    m_keymap[GLFW_KEY_PAUSE] = VirtualKey::PAUSE;
    m_keymap[GLFW_KEY_F1] = VirtualKey::F1;
    m_keymap[GLFW_KEY_F2] = VirtualKey::F2;
    m_keymap[GLFW_KEY_F3] = VirtualKey::F3;
    m_keymap[GLFW_KEY_F4] = VirtualKey::F4;
    m_keymap[GLFW_KEY_F5] = VirtualKey::F5;
    m_keymap[GLFW_KEY_F6] = VirtualKey::F6;
    m_keymap[GLFW_KEY_F7] = VirtualKey::F7;
    m_keymap[GLFW_KEY_F8] = VirtualKey::F8;
    m_keymap[GLFW_KEY_F9] = VirtualKey::F9;
    m_keymap[GLFW_KEY_F10] = VirtualKey::F10;
    m_keymap[GLFW_KEY_F11] = VirtualKey::F11;
    m_keymap[GLFW_KEY_F12] = VirtualKey::F12;
    m_keymap[GLFW_KEY_F13] = VirtualKey::F13;
    m_keymap[GLFW_KEY_F14] = VirtualKey::F14;
    m_keymap[GLFW_KEY_F15] = VirtualKey::F15;
    m_keymap[GLFW_KEY_F16] = VirtualKey::F16;
    m_keymap[GLFW_KEY_F17] = VirtualKey::F17;
    m_keymap[GLFW_KEY_F18] = VirtualKey::F18;
    m_keymap[GLFW_KEY_F19] = VirtualKey::F19;
    m_keymap[GLFW_KEY_F20] = VirtualKey::F20;
    m_keymap[GLFW_KEY_F21] = VirtualKey::F21;
    m_keymap[GLFW_KEY_F22] = VirtualKey::F22;
    m_keymap[GLFW_KEY_F23] = VirtualKey::F23;
    m_keymap[GLFW_KEY_F24] = VirtualKey::F24;
    m_keymap[GLFW_KEY_F25] = VirtualKey::F25;
    m_keymap[GLFW_KEY_KP_0] = VirtualKey::KP_0;
    m_keymap[GLFW_KEY_KP_1] = VirtualKey::KP_1;
    m_keymap[GLFW_KEY_KP_2] = VirtualKey::KP_2;
    m_keymap[GLFW_KEY_KP_3] = VirtualKey::KP_3;
    m_keymap[GLFW_KEY_KP_4] = VirtualKey::KP_4;
    m_keymap[GLFW_KEY_KP_5] = VirtualKey::KP_5;
    m_keymap[GLFW_KEY_KP_6] = VirtualKey::KP_6;
    m_keymap[GLFW_KEY_KP_7] = VirtualKey::KP_7;
    m_keymap[GLFW_KEY_KP_8] = VirtualKey::KP_8;
    m_keymap[GLFW_KEY_KP_9] = VirtualKey::KP_9;
    m_keymap[GLFW_KEY_KP_DECIMAL] = VirtualKey::KP_DECIMAL;
    m_keymap[GLFW_KEY_KP_DIVIDE] = VirtualKey::KP_DIVIDE;
    m_keymap[GLFW_KEY_KP_MULTIPLY] = VirtualKey::KP_MULTIPLY;
    m_keymap[GLFW_KEY_KP_SUBTRACT] = VirtualKey::KP_SUBTRACT;
    m_keymap[GLFW_KEY_KP_ADD] = VirtualKey::KP_ADD;
    m_keymap[GLFW_KEY_KP_ENTER] = VirtualKey::KP_ENTER;
    m_keymap[GLFW_KEY_KP_EQUAL] = VirtualKey::KP_EQUAL;
    m_keymap[GLFW_KEY_LEFT_SHIFT] = VirtualKey::LEFT_SHIFT;
    m_keymap[GLFW_KEY_LEFT_CONTROL] = VirtualKey::LEFT_CONTROL;
    m_keymap[GLFW_KEY_LEFT_ALT] = VirtualKey::LEFT_ALT;
    m_keymap[GLFW_KEY_LEFT_SUPER] = VirtualKey::LEFT_SUPER;
    m_keymap[GLFW_KEY_RIGHT_SHIFT] = VirtualKey::RIGHT_SHIFT;
    m_keymap[GLFW_KEY_RIGHT_CONTROL] = VirtualKey::RIGHT_CONTROL;
    m_keymap[GLFW_KEY_RIGHT_ALT] = VirtualKey::RIGHT_ALT;
    m_keymap[GLFW_KEY_RIGHT_SUPER] = VirtualKey::RIGHT_SUPER;
    m_keymap[GLFW_KEY_MENU] = VirtualKey::MENU;
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

    for (auto &pair : m_keymap)
    {
        int glfw_key = pair.first;
        VirtualKey vk = pair.second;
        bool was_pressed = glfwGetKey(m_handle, glfw_key) == GLFW_PRESS;
        EventSystem::emit(VirtualKeyboardEvent{vk, was_pressed});
    }
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