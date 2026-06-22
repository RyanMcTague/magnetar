#pragma once
#include "magnetar/core/base.h"
#include "magnetar/scripting/script_runtime.h"
#include "magnetar/scripting/script_instance.h"

namespace magnetar
{
    class MAGNETAR_API ScriptEngine
    {
    public:

        static bool initialize();
        static bool shutdown();

        static bool load_assembly(const std::string &path);
        static bool reload_assembly();

        static void update(float delta_time);

        static ScriptInstance* create_entity_instance(const std::string& name, EntityHandle handle);

        static ScriptInstance* allocate_entity_instance(const std::string& name, EntityHandle handle);

        static void start_all_entity_instances();

        static ScriptInstance* get_entity_instance(EntityHandle handle);

        static void remove_entity_instance(EntityHandle handle);

    private:
        ScriptEngine() = default;
        static Ref<ScriptRuntime> s_runtime;
    };
}