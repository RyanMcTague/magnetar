#include "magnetar/core/application.h"
#include "magnetar/core/window.h"
#include "magnetar/core/time.h"
#include "magnetar/input/input_system.h"
#include "magnetar/events/event_system.h"
#include "magnetar/filesystem/native_file_system.h"
#include "magnetar/renderer/renderer.h"
#include "magnetar/assets/asset_manager.h"

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

        update(delta_time);
        render();

        m_window->poll_events();
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
    m_mask.set(BufferMask::COLOR_BUFFER);

    LOG_INFO(logger::tags::application, "initialzing application");

    FileSystem::register_filesystem<NativeFileSystem>();

    m_window = Window::create({"Untitled", 1200, 800});
    Renderer::initialize();
    AssetManager::initialize(asset_config());
    on_initialize();
}

void magnetar::Application::update(float delta_time)
{
    EventSystem::process();
    InputSystem::update();

    on_update(delta_time);

    for (auto layer : m_layer_stack)
        layer->on_update(delta_time);
}

void magnetar::Application::render()
{
    Renderer::clear(m_mask);
    on_render();
    for (auto layer : m_layer_stack)
        layer->on_render();
    m_window->swap_buffers();
}

void magnetar::Application::shutdown()
{
    LOG_INFO(logger::tags::application, "destroying application");
    on_shutdown();

    for (auto layer : m_layer_stack)
        layer->on_detach();
    m_layer_stack.clear();
    
    AssetManager::shutdown();
    Renderer::shutdown();
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

void magnetar::Application::on_render()
{
}