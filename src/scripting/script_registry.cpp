#include "magnetar/scripting/script_registry.h"

void* magnetar::ScriptRegistry::s_entity_class = nullptr;

std::unordered_map<std::string, magnetar::UniqueRef<magnetar::ScriptClass>> magnetar::ScriptRegistry::s_classes;

magnetar::ScriptClass* magnetar::ScriptRegistry::find(const std::string& name)
{
    auto it = s_classes.find(name);
    MT_ASSERT(it != s_classes.end(), "scripting class {} cannot be found", name);
    return it->second.get();
}

void magnetar::ScriptRegistry::register_class(UniqueRef<ScriptClass> klass)
{
    s_classes.emplace(klass->name(), std::move(klass));
}

void magnetar::ScriptRegistry::shutdown()
{
    s_classes.clear();
}