#pragma once
#include "magnetar/core/base.h"
#include "magnetar/scene/entity_handle.h"

namespace magnetar
{
    class MAGNETAR_API ScriptClass
    {
    public:
        virtual ~ScriptClass() = default;

        virtual const std::string &name() const = 0;

        virtual UniqueRef<class ScriptInstance> create_instance() = 0;

        virtual void *get_native_handle() = 0;
    };
}