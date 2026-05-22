#pragma once
#include <vector>
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/input/mapped_input_code.h"
#include "magnetar/input/input_action.h"

namespace magnetar
{
    class InputDevice;

    namespace input
    {
        ButtonState action_state(MappedInputCode code);

        bool action_pressed(MappedInputCode code);
        bool action_down(MappedInputCode code);

        bool action_released(MappedInputCode code);
        bool action_up(MappedInputCode code);

        bool action_active(MappedInputCode code);
        bool action_inactive(MappedInputCode code);
    };
    class MAGNETAR_API InputSystem
    {
    public:
        static void initialize();
        static void shutdown();
        static InputSystem* get();

        void update();
        void add_device(UniqueRef<InputDevice> device);
        void register_action(MappedInputCode code, MouseButton button);
        void register_action(MappedInputCode code, KeyboardKey key);

        ButtonState action_state(MappedInputCode code) const;

        bool action_pressed(MappedInputCode code) const;
        bool action_down(MappedInputCode code) const;

        bool action_released(MappedInputCode code) const;
        bool action_up(MappedInputCode code) const;

        bool action_active(MappedInputCode code) const;
        bool action_inactive(MappedInputCode code) const;

    private:
        static InputSystem *s_instance;
        std::vector<UniqueRef<InputDevice>> m_devices;
        std::unordered_map<MappedInputCode, InputAction> m_actions;

        InputSystem() = default;
    };
}