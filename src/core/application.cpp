#include <spdlog/spdlog.h>
#include "magnetar/core/application.h"

magnetar::Application::Application()
{
    
}

int magnetar::Application::run(int argc, char** argv)
{
    spdlog::set_level(spdlog::level::trace);
    spdlog::debug("Hello Magnetar");
    return 0;
}