#pragma once
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/events/event_handle.h"
#include "magnetar/input/input_events.h"
namespace magnetar
{
    class MAGNETAR_API VirtualKeyboard
    {
    public:
        VirtualKeyboard();
        ~VirtualKeyboard();

        VirtualKeyState key_state(VirtualKey key) const;
        bool is_key_down(VirtualKey key) const;
        bool is_key_up(VirtualKey key) const;
        bool is_key_pressed(VirtualKey key) const;
        bool is_key_released(VirtualKey key) const;
    private:
        EventHandle m_keyboard_handle;
        std::unordered_map<VirtualKey, VirtualKeyState> m_keystates;

        void on_keyboard_event(const VirtualKeyboardEvent& event);
    };
}