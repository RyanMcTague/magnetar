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
static constexpr uint32_t METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK = 0x0007;
static constexpr uint32_t METHOD_ATTRIBUTE_PRIVATE = 0x0001;
static constexpr uint32_t METHOD_ATTRIBUTE_FAM_AND_ASSEM = 0x0002;
static constexpr uint32_t METHOD_ATTRIBUTE_ASSEM = 0x0003;
static constexpr uint32_t METHOD_ATTRIBUTE_FAMILY = 0x0004;       // protected
static constexpr uint32_t METHOD_ATTRIBUTE_FAM_OR_ASSEM = 0x0005; // protected internal
static constexpr uint32_t METHOD_ATTRIBUTE_PUBLIC = 0x0006;

magnetar::MonoScriptClass::MonoScriptClass(MonoDomain *domain, MonoImage *image, const std::string &ns, const std::string &name)
{
    m_domain = domain;
    m_class = mono_class_from_name(image, ns.c_str(), name.c_str());
    MT_ASSERT(m_class != nullptr, "could not find class {}.{}", ns, name);
    m_name = ns + "." + name;

    void *iter = nullptr;
    MonoMethod *method;
    while ((method = mono_class_get_methods(m_class, &iter)))
        parse_method(method);
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

void magnetar::MonoScriptClass::parse_method(MonoMethod *method)
{
    const char *method_name = mono_method_full_name(method, 1);
    uint32_t iflags;
    uint32_t flags = mono_method_get_flags(method, &iflags);
    uint32_t mask = flags & METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK;
    ScriptVisibility visibility = ScriptVisibility::PRIVATE;
    switch (mask)
    {
    case METHOD_ATTRIBUTE_PRIVATE:
    case METHOD_ATTRIBUTE_FAM_AND_ASSEM:
    case METHOD_ATTRIBUTE_ASSEM:
        visibility = ScriptVisibility::PRIVATE;
        break;
    case METHOD_ATTRIBUTE_FAMILY:
    case METHOD_ATTRIBUTE_FAM_OR_ASSEM:
        visibility = ScriptVisibility::PROTECTED;
        break;
    case METHOD_ATTRIBUTE_PUBLIC:
        visibility = ScriptVisibility::PUBLIC;
        break;
    default:
        break;
    }
    auto stripped_name = string_utils::remove_from_start(method_name, m_name + ":");
    m_methods.emplace(stripped_name, MethodEntry{method, visibility});
    LOG_TRACE(logger::tags::scripting, stripped_name);
}

void magnetar::MonoScriptClass::invoke(MonoObject *object, const std::string &method_sig, void **args)
{
    auto it = m_methods.find(method_sig);
    MT_ASSERT(it != m_methods.end(), "method {}:{} not found", m_name, method_sig);
    MonoObject *exception = nullptr;
    mono_runtime_invoke(it->second.method, object, args, &exception);
    if(exception)
        mono_print_unhandled_exception(exception);
}