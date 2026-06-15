#pragma once
#include <vector>
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/input/mapped_input_code.h"
#include "magnetar/input/input_code.h"
#include "magnetar/input/enums.h"

namespace magnetar
{
    class InputDevice;

    class MAGNETAR_API InputAction
    {
    public:
        InputAction();
        InputAction(const std::string& name, MappedInputCode code, const InputCode &input_code);
        virtual ~InputAction() = default;

        bool operator==(MappedInputCode code) const { return m_mapped_code == code; }
        bool operator!=(MappedInputCode code) const { return !(*this == code); }

        ButtonState check_state(InputDevice *device) const;
        InputDeviceType input_device_type() const { return m_input_code.type(); }

    private:
        InputCode m_input_code;
        std::string m_name;
        MappedInputCode m_mapped_code;
    };
}