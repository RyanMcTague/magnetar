#pragma once
#include <array>
#include "magnetar/core/base.h"
#include "magnetar/core/input/virtual_keyboard.h"
#include "magnetar/core/input/virtual_key.h"
namespace magnetar
{
    class MAGNETAR_API InputManager
    {
    public:
        void connect(uint8_t controller);

        VirtualKeyState key_state(VirtualKey key, uint8_t controller = 0) const;
        bool is_key_down(VirtualKey key, uint8_t controller = 0) const;
        bool is_key_up(VirtualKey key, uint8_t controller = 0) const;
        bool is_key_pressed(VirtualKey key, uint8_t controller = 0) const;
        bool is_key_released(VirtualKey key, uint8_t controller = 0) const;

    private:
        std::array<Ref<VirtualKeyboard>, 4> m_virtual_keyboards;
    };
}