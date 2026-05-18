#include "magnetar/core/application.h"
#include "magnetar/core/base.h"

magnetar::Application::Application(int argc, char** argv)
{
    MAGNETAR_INITIALIZE_LOGGER;
    for(int i = 0; i < argc; i++)
        m_command_line_args.push_back(argv[i]);
}

int magnetar::Application::run()
{
    LOG_DEBUG("Hello Magnetar");
    return 0;
}

int magnetar::Application::runApp(int argc, char** argv)
{
    auto app = new Application(argc, argv);
    int status = app->run();
    delete app;
    return status;
}