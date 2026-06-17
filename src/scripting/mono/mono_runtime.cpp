#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/tokentype.h>

#include "magnetar/scripting/mono/mono_runtime.h"
#include "magnetar/filesystem/native_file_system.h"
#include "magnetar/scripting/script_registry.h"
#include "magnetar/scripting/mono/mono_script_class.h"
#include "magnetar/scripting/mono/mono_script_instance.h"

namespace magnetar
{
    static void internal_log(int lvl, MonoObject *object)
    {
        LogLevel level = static_cast<LogLevel>(lvl);
        char *str = mono_string_to_utf8((MonoString *)object);
        const char *tag = logger::tags::client;
        switch (level)
        {
        case LogLevel::critical:
            LOG_FATAL(tag, str);
            break;
        case LogLevel::err:
            LOG_ERROR(tag, str);
            break;
        case LogLevel::warn:
            LOG_WARN(tag, str);
            break;
        case LogLevel::info:
            LOG_INFO(tag, str);
            break;
        case LogLevel::debug:
            LOG_DEBUG(tag, str);
            break;
        case LogLevel::trace:
            LOG_TRACE(tag, str);
            break;
        default:
            break;
        }
        mono_free(str);
    }

    static void add_internal_calls()
    {
        mono_add_internal_call("Magnetar.Core.InternalCalls::Log", reinterpret_cast<const void *>(internal_log));
    }
}

#undef MT_INTERNAL_CALL

bool magnetar::MonoRuntime::initialize()
{
    m_domain = mono_jit_init("Magnetar.Core");
    add_internal_calls();
    return true;
}

bool magnetar::MonoRuntime::shutdown()
{
    return true;
}

bool magnetar::MonoRuntime::load_assembly(const std::string &path)
{
    auto fs = FileSystem::get<NativeFileSystem>();
    auto file = fs->open(path, FileMode::READ);
    auto data = file->read_all();
    m_image = mono_image_open_from_data((char *)&data[0], data.size(), true, nullptr);
    if (!m_image)
    {
        LOG_ERROR(logger::tags::scripting, "could not open {}", path);
        return false;
    }
    m_assembly = mono_assembly_load_from_full(m_image, path.c_str(), nullptr, false);

    const MonoTableInfo *type_info = mono_image_get_table_info(m_image, MONO_TABLE_TYPEDEF);
    int num_rows = mono_table_info_get_rows(type_info);

    for (int i = 1; i <= num_rows; i++)
    {
        uint32_t token = MONO_TOKEN_TYPE_DEF | i;
        MonoClass *klass = mono_class_get(m_image, token);
        if (!klass)
            continue;

        const char *class_name = mono_class_get_name(klass);
        const char *name_space = mono_class_get_namespace(klass);
        if (std::string(class_name) == "<Module>")
            continue;

        LOG_TRACE(logger::tags::scripting, "found class {}.{}", name_space, class_name);
        auto ref = create_unique_reference<MonoScriptClass>(m_domain, m_image, name_space, class_name);
        ScriptRegistry::register_class(std::move(ref));
    }
    LOG_DEBUG(logger::tags::scripting, "loaded assembly {}", path);
    return true;
}

bool magnetar::MonoRuntime::reload_assembly()
{
    return false;
}

void magnetar::MonoRuntime::update(float)
{
}