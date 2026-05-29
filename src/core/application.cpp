#include "magnetar/core/application.h"
#include "magnetar/core/window.h"
#include "magnetar/core/time.h"
#include "magnetar/input/input_system.h"
#include "magnetar/events/event_system.h"
#include "magnetar/filesystem/native_file_system.h"

magnetar::Application::Application()
    : m_is_running(true), m_is_initialized(false), m_window(nullptr)
{
    Logger::initialize(MAGNETAR_LOG_LEVEL);
}

magnetar::Application::~Application()
{
    shutdown();
}

void magnetar::Application::run()
{
    Timer timer;
    while (m_is_running)
    {
        auto elapsed = timer.elapsed();
        float delta_time = (float)((double)elapsed / 1000.0);
        timer.reset();

        m_window->poll_events();
        InputSystem::update();

        on_update(delta_time);

        m_window->swap_buffers();
        EventSystem::process();

        if (m_window->should_close())
            m_is_running = false;
    }
}

void magnetar::Application::close()
{
    m_is_running = false;
}

magnetar::Window *magnetar::Application::get_window()
{
    return m_window.get();
}

void magnetar::Application::initialize()
{
    if (m_is_initialized)
        return;
    m_is_initialized = true;
    LOG_INFO(logger::tags::application, "initialzing application");
    FileSystem::register_filesystem<NativeFileSystem>();
    m_window = Window::create({"Untitled", 800, 600});
    on_initialize();
}

void magnetar::Application::shutdown()
{
    on_shutdown();
    LOG_INFO(logger::tags::application, "destroying application");
}

void magnetar::Application::on_initialize()
{
}

void magnetar::Application::on_shutdown()
{
}

void magnetar::Application::on_update(float)
{
}
