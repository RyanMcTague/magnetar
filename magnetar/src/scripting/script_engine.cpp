#include "magnetar/scripting/script_engine.h"
#include "magnetar/scripting/mono/mono_runtime.h"
magnetar::Ref<magnetar::ScriptRuntime> magnetar::ScriptEngine::s_runtime;

bool magnetar::ScriptEngine::initialize()
{
    static bool first = true;
    if (!first)
        return true;
    first = false;
    s_runtime = create_unique_reference<MonoRuntime>();
    return s_runtime->initialize();
}

bool magnetar::ScriptEngine::shutdown()
{
    bool value = s_runtime->shutdown();
    s_runtime = nullptr;
    return value;
}

bool magnetar::ScriptEngine::load_assembly(const std::string &path)
{
    return s_runtime->load_assembly(path);
}

bool magnetar::ScriptEngine::reload_assembly()
{
    return s_runtime->reload_assembly();
}

void magnetar::ScriptEngine::update(float delta_time)
{
    return s_runtime->update(delta_time);
}

magnetar::ScriptInstance *magnetar::ScriptEngine::create_entity_instance(const std::string &name, EntityHandle handle)
{
    return s_runtime->create_entity_instance(name, handle);
}

magnetar::ScriptInstance *magnetar::ScriptEngine::allocate_entity_instance(const std::string &name, EntityHandle handle)
{
    return s_runtime->allocate_entity_instance(name, handle);
}

void magnetar::ScriptEngine::start_all_entity_instances()
{
    s_runtime->start_all_entity_instances();
}

magnetar::ScriptInstance* magnetar::ScriptEngine::get_entity_instance(EntityHandle handle)
{
    return s_runtime->get_entity_instance(handle);
}

void magnetar::ScriptEngine::remove_entity_instance(EntityHandle handle)
{
    return s_runtime->remove_entity_instance(handle);
}