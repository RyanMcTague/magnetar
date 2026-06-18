#pragma once
#include <vector>
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/input/mapped_input_code.h"
#include "magnetar/input/input_action.h"

namespace magnetar
{
    class InputDevice;

    struct InputActionEvent
    {
        MT_DECLARE_CLASS_NAME(InputActionEvent)
        MappedInputCode code;
        ButtonState state;

        InputActionEvent(MappedInputCode code, ButtonState state)
            : code(code), state(state) {}
    };

    class MAGNETAR_API InputSystem
    {
    public:
        static void shutdown();
        static void update();

        static void add_device(UniqueRef<InputDevice> device);
        static void register_action(const std::string &name, MappedInputCode code, const InputCode &input_code);

        static ButtonState action_state(MappedInputCode code);

        static bool action_pressed(MappedInputCode code);
        static bool action_down(MappedInputCode code);

        static bool action_released(MappedInputCode code);
        static bool action_up(MappedInputCode code);

        static bool action_active(MappedInputCode code);
        static bool action_inactive(MappedInputCode code);

    private:
        static std::vector<UniqueRef<InputDevice>> s_devices;
        static std::unordered_map<MappedInputCode, InputAction> s_actions;
    };

    using input = InputSystem;
}