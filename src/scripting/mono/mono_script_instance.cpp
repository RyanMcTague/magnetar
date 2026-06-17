#include "magnetar/scripting/mono/mono_script_instance.h"
#include "magnetar/scripting/mono/mono_script_class.h"

magnetar::MonoScriptInstance::MonoScriptInstance(MonoScriptClass* klass,MonoObject* object)
    : m_object(object), m_class(klass)
{
}

void magnetar::MonoScriptInstance::invoke(const std::string& method, void** args)
{
    m_class->invoke(m_object, method, args);
}