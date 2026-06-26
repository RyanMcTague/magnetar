#pragma once
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/scripting/script_class.h"
#include "magnetar/scripting/script_instance.h"

namespace magnetar
{
    class MAGNETAR_API ScriptRegistry
    {
    public:
        static ScriptClass* find(const std::string& name);
        static void register_class(UniqueRef<ScriptClass> klass);

        static void shutdown();

        static void set_entity_class(void* klass) { s_entity_class = klass; }
        static void* entity_class() { return s_entity_class; }
    private:
        static std::unordered_map<std::string, UniqueRef<ScriptClass>> s_classes;
        static void* s_entity_class;
    };
}