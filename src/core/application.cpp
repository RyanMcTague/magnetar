#include "magnetar/core/application.h"
#include "magnetar/core/base.h"
#include "magnetar/core/window.h"

magnetar::Application::Application(int argc, char **argv)
{
    MAGNETAR_INITIALIZE_LOGGER;
    for (int i = 0; i < argc; i++)
        m_command_line_args.push_back(argv[i]);
    LOG_DEBUG("Starting Magnetar");
}

magnetar::Application::~Application()
{
    LOG_DEBUG("Stopping Magnetar");
}

int magnetar::Application::run()
{
    auto window = Window::create({
        .title = "Untitled",
        .width = 800,
        .height = 600,
    });

    while (!window->should_close())
    {
        window->update();
        window->swap_buffers();
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