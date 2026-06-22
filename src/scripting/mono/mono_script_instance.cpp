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
    return m_class->m_methods.contains(name);
}

void magnetar::MonoScriptInstance::invoke_ctor()
{
    m_class->invoke_ctor(m_object);
}
void magnetar::MonoScriptInstance::invoke_set_id(EntityHandle handle)
{
    m_class->invoke_set_id(m_object, handle);
}
void magnetar::MonoScriptInstance::invoke_on_start()
{
    m_class->invoke_on_start(m_object);
}
void magnetar::MonoScriptInstance::invoke_on_update(float delta_time)
{
    m_class->invoke_on_update(m_object, delta_time);
}
void magnetar::MonoScriptInstance::invoke_on_collision(ScriptInstance *entity)
{
    m_class->invoke_on_collision(m_object, (MonoObject *)entity->get_native_handle());
}