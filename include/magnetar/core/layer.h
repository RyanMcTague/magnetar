#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    class MAGNETAR_API Layer
    {
    public:
        virtual ~Layer() = default;

        virtual void on_attach() {}
        virtual void on_detach() {}

        virtual void on_update(float) {}
        virtual void on_render() {} 
    };
}