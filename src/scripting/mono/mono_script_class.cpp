#include <mono/jit/jit.h>
#include <mono/metadata/object.h>
#include <mono/metadata/class.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/loader.h>
#include "magnetar/scripting/mono/mono_script_class.h"
#include "magnetar/scripting/mono/mono_script_instance.h"
#include "magnetar/utils/string_utils.h"
// ECMA-335 II.23.1.10 — not exposed in Mono's public headers
// static constexpr uint32_t METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK = 0x0007;
// static constexpr uint32_t METHOD_ATTRIBUTE_PRIVATE = 0x0001;
// static constexpr uint32_t METHOD_ATTRIBUTE_FAM_AND_ASSEM = 0x0002;
// static constexpr uint32_t METHOD_ATTRIBUTE_ASSEM = 0x0003;
// static constexpr uint32_t METHOD_ATTRIBUTE_FAMILY = 0x0004;       // protected
// static constexpr uint32_t METHOD_ATTRIBUTE_FAM_OR_ASSEM = 0x0005; // protected internal
// static constexpr uint32_t METHOD_ATTRIBUTE_PUBLIC = 0x0006;

magnetar::MonoScriptClass::MonoScriptClass(MonoDomain *domain, MonoImage *image, const std::string &ns, const std::string &name)
{
    m_domain = domain;
    m_class = mono_class_from_name(image, ns.c_str(), name.c_str());
    MT_ASSERT(m_class != nullptr, "could not find class {}.{}", ns, name);
    m_name = ns + "." + name;

    MonoClass *parent = mono_class_from_name(image, "Magnetar.Core", "ScriptableEntity");

    m_method_constructor = mono_class_get_method_from_name(m_class, ".ctor", 0);
    m_method_on_start = mono_class_get_method_from_name(m_class, "OnStart", 0);
    m_method_on_update = mono_class_get_method_from_name(m_class, "OnUpdate", 1);

    MonoProperty *prop = mono_class_get_property_from_name(parent, "Handle");
    m_method_set_handle = mono_property_get_set_method(prop);
}

const std::string &magnetar::MonoScriptClass::name() const
{
    return m_name;
}

magnetar::UniqueRef<magnetar::ScriptInstance> magnetar::MonoScriptClass::create_instance()
{
    MonoObject *object = mono_object_new(m_domain, m_class);
    auto ref = create_unique_reference<MonoScriptInstance>(this, object);
    return ref;
}

void magnetar::MonoScriptClass::invoke_ctor(MonoObject *object)
{
    MonoObject *exception = nullptr;
    mono_runtime_invoke(m_method_constructor, object, nullptr, &exception);
    if (exception)
        mono_print_unhandled_exception(exception);
}
void magnetar::MonoScriptClass::invoke_set_handle(MonoObject *object, EntityHandle handle)
{
    void *args[1];
    args[0] = &handle;
    MonoObject *exception = nullptr;
    mono_runtime_invoke(m_method_set_handle, object, args, &exception);
    if (exception)
        mono_print_unhandled_exception(exception);
}
void magnetar::MonoScriptClass::invoke_on_start(MonoObject *object)
{
    MonoObject *exception = nullptr;
    mono_runtime_invoke(m_method_on_start, object, nullptr, &exception);
    if (exception)
        mono_print_unhandled_exception(exception);
}
void magnetar::MonoScriptClass::invoke_on_update(MonoObject *object, float delta_time)
{
    void *args[1];
    args[0] = &delta_time;
    MonoObject *exception = nullptr;
    mono_runtime_invoke(m_method_on_update, object, args, &exception);
    if (exception)
        mono_print_unhandled_exception(exception);
}