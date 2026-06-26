#pragma once
#include "magnetar/core/base.h"
#include "magnetar/scene/entity_handle.h"
namespace magnetar
{
    class MAGNETAR_API ScriptInstance
    {
    public:
        virtual ~ScriptInstance() = default;

        virtual void *get_native_handle() = 0;

        virtual bool has_method(const std::string &name) const = 0;
        virtual void invoke_ctor() = 0;
        virtual void invoke_set_id(EntityHandle handle) = 0;
        virtual void invoke_on_start() = 0;
        virtual void invoke_on_update(float delta_time) = 0;
        virtual void invoke_on_collision(ScriptInstance *entity) = 0;
    };
}