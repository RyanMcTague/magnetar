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
        InputAction(MappedInputCode code, const std::vector<InputCode> &input_codes);
        virtual ~InputAction() = default;

        bool operator==(MappedInputCode code) const { return m_mapped_code == code; }
        bool operator!=(MappedInputCode code) const { return !(*this == code); }

        ButtonState check_state(InputDevice *device, bool *found = nullptr) const;

    private:
        std::unordered_map<InputDeviceType, InputCode> m_input_codes;
        MappedInputCode m_mapped_code;
    };
}