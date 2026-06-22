#include <mono/jit/jit.h>
#include <mono/metadata/object.h>
#include <mono/metadata/class.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/loader.h>
#include "magnetar/scripting/mono/mono_script_class.h"
#include "magnetar/scripting/mono/mono_script_instance.h"
#include "magnetar/scripting/script_registry.h"
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

    MonoClass *parent = (MonoClass *)ScriptRegistry::entity_class();
    MonoProperty *id_prop = mono_class_get_property_from_name(parent, "ID");

    auto try_add = [&](const char *key, MonoMethod *method) {
        if (method) m_methods[key] = method;
    };
    try_add(".ctor", mono_class_get_method_from_name(m_class, ".ctor", 0));
    try_add("OnStart", mono_class_get_method_from_name(m_class, "OnStart", 0));
    try_add("OnUpdate", mono_class_get_method_from_name(m_class, "OnUpdate", 1));
    try_add("OnCollision", mono_class_get_method_from_name(m_class, "OnCollision", 1));
    try_add("set_ID", mono_property_get_set_method(id_prop));
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

void *magnetar::MonoScriptClass::get_native_handle()
{
    return (void *)m_class;
}

void magnetar::MonoScriptClass::invoke_ctor(MonoObject *object)
{
    if (!m_methods.contains(".ctor"))
        return;
    MonoObject *exception = nullptr;
    mono_runtime_invoke(m_methods[".ctor"], object, nullptr, &exception);
    if (exception)
        mono_print_unhandled_exception(exception);
}

void magnetar::MonoScriptClass::invoke_set_id(MonoObject *object, EntityHandle handle)
{
    if (!m_methods.contains("set_ID"))
        return;

    MonoObject *exception = nullptr;
    void *args[1];
    args[0] = &handle;
    mono_runtime_invoke(m_methods["set_ID"], object, args, &exception);
    if (exception)
        mono_print_unhandled_exception(exception);
}
void magnetar::MonoScriptClass::invoke_on_start(MonoObject *object)
{
    if (!m_methods.contains("OnStart"))
        return;
    MonoObject *exception = nullptr;
    mono_runtime_invoke(m_methods["OnStart"], object, nullptr, &exception);
    if (exception)
        mono_print_unhandled_exception(exception);
}
void magnetar::MonoScriptClass::invoke_on_update(MonoObject *object, float delta_time)
{
    if (!m_methods.contains("OnUpdate"))
        return;

    MonoObject *exception = nullptr;
    void *args[1];
    args[0] = &delta_time;
    mono_runtime_invoke(m_methods["OnUpdate"], object, args, &exception);
    if (exception)
        mono_print_unhandled_exception(exception);
}
void magnetar::MonoScriptClass::invoke_on_collision(MonoObject *object, MonoObject *entity)
{
    if (!m_methods.contains("OnCollision"))
        return;

    MonoObject *exception = nullptr;
    void *args[1];
    args[0] = entity;
    mono_runtime_invoke(m_methods["OnCollision"], object, args, &exception);
    if (exception)
        mono_print_unhandled_exception(exception);
}