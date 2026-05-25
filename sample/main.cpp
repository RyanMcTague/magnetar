#include <magnetar/magnetar.h>
#include <iostream>

using namespace magnetar;

namespace actions
{
    static constexpr int quit =0;
}

class SandboxApp final: public Application
{
protected:
    void on_initialize() override;
    void on_update(float delta_time) override;
};

void SandboxApp::on_initialize()
{
}
void SandboxApp::on_update(float delta_time)
{
    if(InputSystem::action_pressed(actions::quit))
        close();
}

int main(int argc, char **argv)
{
    SandboxApp app;
    InputSystem::register_action(actions::quit, KeyboardKey::ESCAPE);
    app.run();
    return 0;
}