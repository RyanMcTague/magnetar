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
    bool value =  s_runtime->shutdown();
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
