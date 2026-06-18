#pragma once
#include "magnetar/core/base.h"
#include "magnetar/scene/entity_handle.h"
#include "magnetar/scripting/script_instance.h"
namespace magnetar
{
    class MAGNETAR_API ScriptRuntime
    {
    public:
        virtual ~ScriptRuntime() = default;

        virtual bool initialize() = 0;
        virtual bool shutdown() = 0;

        virtual bool load_assembly(const std::string &path) = 0;
        virtual bool reload_assembly() = 0;

        virtual void update(float delta_time) = 0;

        virtual ScriptInstance* create_entity_instance(const std::string& name, EntityHandle handle) = 0;

        virtual void remove_entity_instance(EntityHandle handle) = 0;
    };
}