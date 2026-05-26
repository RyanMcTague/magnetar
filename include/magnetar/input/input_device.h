#pragma once
#include "magnetar/core/base.h"
#include "magnetar/input/enums.h"

namespace magnetar
{
    class MAGNETAR_API InputDevice
    {
    public:
        virtual ~InputDevice() = default;

        virtual void update() = 0;
        virtual const std::string& name() const = 0;
        virtual InputDeviceType type() const = 0;
    };
}