#include <magnetar/magnetar.h>
#include <iostream>

using namespace magnetar;

int main(int argc, char **argv)
{
    MAGNETAR_INITIALIZE_LOGGER;
    LOG_DEBUG("Starting Magnetar");

    auto window = Window::create({"Untitled", 800, 600});
    while (!window->should_close())
    {
        window->update();
        InputSystem::update();
        window->swap_buffers();
        EventSystem::process();
    }


    LOG_DEBUG("Stopping Magnetar");
    InputSystem::shutdown();
}