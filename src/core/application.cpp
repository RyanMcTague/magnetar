#include <iostream>
#include "magnetar/core/application.h"

magnetar::Application::Application()
{
    
}

int magnetar::Application::run(int argc, char** argv)
{
    std::cout << "Welcome Magnetar" << std::endl;
    return 0;
}