#pragma once
#include <variant>
#include "magnetar/core/base.h"
#include "magnetar/input/enums.h"

namespace magnetar
{
    class MAGNETAR_API InputCode
    {
    public:
        using Variant = std::variant<std::monostate, KeyboardKey, MouseButton>;

        InputCode()
            : m_type(InputDeviceType::KEYBOARD) {}

        InputCode(KeyboardKey key)
            : m_type(InputDeviceType::KEYBOARD), m_code(key) {}

        InputCode(MouseButton button)
            : m_type(InputDeviceType::MOUSE), m_code(button) {}

        template <typename T>
        T get() const { return std::get<T>(m_code); }
        InputDeviceType type() const { return m_type; }

    private:
        Variant m_code;
        InputDeviceType m_type;
    };
}