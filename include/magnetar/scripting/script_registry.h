#pragma once
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/scripting/script_class.h"
namespace magnetar
{
    class MAGNETAR_API ScriptRegistry
    {
    public:
        static ScriptClass* find(const std::string& name);
        static void register_class(UniqueRef<ScriptClass> klass);
    private:
        static std::unordered_map<std::string, UniqueRef<ScriptClass>> s_classes;
    };
}