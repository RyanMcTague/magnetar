#include "magnetar/core/application.h"
#include "magnetar/core/base.h"
#include "magnetar/core/window.h"
#include "magnetar/events/event_system.h"
#include "magnetar/core/time.h"
#include "magnetar/input/input_system.h"
magnetar::Application::Application(int argc, char **argv)
{
    MAGNETAR_INITIALIZE_LOGGER;
    for (int i = 0; i < argc; i++)
        m_command_line_args.push_back(argv[i]);
    LOG_DEBUG("Starting Magnetar");

    InputSystem::initialize();
}

magnetar::Application::~Application()
{
    LOG_DEBUG("Stopping Magnetar");
    InputSystem::shutdown();
}

namespace magnetar::actions
{
    static constexpr MappedInputCode print_message = 1;
}
int magnetar::Application::run()
{
    m_window = Window::create({"Untitled", 800, 600});

    InputSystem::get()->register_action(actions::print_message, KeyboardKey::A);

    while (!m_window->should_close())
    {
        m_window->update();
        InputSystem::get()->update();
        m_window->swap_buffers();
    }

    return 0;
}

int magnetar::Application::runApp(int argc, char **argv)
{
    auto app = new Application(argc, argv);
    int status = app->run();
    delete app;
    return status;
}