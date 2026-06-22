#include "magnetar/scripting/mono/mono_script_instance.h"
#include "magnetar/scripting/mono/mono_script_class.h"

magnetar::MonoScriptInstance::MonoScriptInstance(MonoScriptClass *klass, MonoObject *object)
    : m_object(object), m_class(klass)
{
}

void *magnetar::MonoScriptInstance::get_native_handle()
{
    return (void *)m_object;
}

bool magnetar::MonoScriptInstance::has_method(const std::string &name) const
{
    auto it = m_class->m_methods.find(name);
    return it != m_class->m_methods.end();
}

void magnetar::MonoScriptInstance::invoke_method(const char *name, void **args, int argc)
{
    if (!has_method(name))
        return;
    m_class->invoke_method(m_object, name, args, argc);
}