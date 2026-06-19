#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/tokentype.h>

#include "magnetar/scripting/mono/mono_runtime.h"
#include "magnetar/filesystem/native_file_system.h"
#include "magnetar/scripting/script_registry.h"
#include "magnetar/scripting/mono/mono_script_class.h"
#include "magnetar/scripting/mono/mono_script_instance.h"
#include "magnetar/scene/entity.h"
#include "magnetar/scene/components.h"

#define MT_ADD_INTERNAL_CALL(func) \
    mono_add_internal_call("Magnetar.Core.InternalCalls::" #func, reinterpret_cast<const void *>(func))

#define MT_REGISTER_COMPONENT(image, Klass) \
    register_component<Klass>(image, #Klass)

namespace magnetar
{
    static std::unordered_map<MonoClass *, std::function<bool(Entity)>> s_has_component_funcs;

    template <typename T>
    static void register_component(MonoImage *image, const char *class_name)
    {
        MonoClass *klass = mono_class_from_name(image, "Magnetar.Core", class_name);
        if (!klass)
            return;

        std::function<bool(Entity)> func = [](Entity entity)
        { return entity.has_component<T>(); };

        s_has_component_funcs.emplace(klass, func);
        LOG_TRACE(logger::tags::scripting, "registered component script {}", class_name);
    }

    static void Logger_Log(int lvl, MonoObject *object)
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

    static bool Entity_HasComponent(uint32_t id, MonoReflectionType *reflection)
    {
        MonoType *mono_type = mono_reflection_type_get_type(reflection);
        MonoClass *klass = mono_class_from_mono_type(mono_type);
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto it = s_has_component_funcs.find(klass);
        MT_ASSERT(it != s_has_component_funcs.end(), "component {} not found", mono_class_get_name(klass));
        return it->second(entity);
    }

    static uint32_t Entity_GetByName(MonoString *name)
    {
        char *cstr = mono_string_to_utf8(name);
        Scene *scene = Scene::current();
        Entity entity = scene->get_entity_by_name(cstr);
        mono_free(cstr);

        if (!entity)
            return 0;
        return entity;
    }

    static void TransformComponent_GetPosition(uint32_t id, glm::vec3 *position)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &tc = entity.get_component<TransformComponent>();
        *position = tc.position;
    }

    static void TransformComponent_SetPosition(uint32_t id, glm::vec3 *position)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &tc = entity.get_component<TransformComponent>();
        tc.position = *position;
    }

    static void TransformComponent_GetRotation(uint32_t id, glm::vec3 *rotation)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &tc = entity.get_component<TransformComponent>();
        *rotation = tc.rotation;
    }

    static void TransformComponent_SetRotation(uint32_t id, glm::vec3 *rotation)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &tc = entity.get_component<TransformComponent>();
        tc.rotation = *rotation;
    }

    static void TransformComponent_GetScale(uint32_t id, glm::vec3 *scale)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &tc = entity.get_component<TransformComponent>();
        *scale = tc.scale;
    }

    static void TransformComponent_SetScale(uint32_t id, glm::vec3 *scale)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &tc = entity.get_component<TransformComponent>();
        tc.scale = *scale;
    }

    static void SpriteRenderer_GetSize(uint32_t id, glm::vec2 *size)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &sc = entity.get_component<SpriteRendererComponent>();
        *size = sc.size;
    }

    static void SpriteRenderer_SetSize(uint32_t id, glm::vec2 *size)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &sc = entity.get_component<SpriteRendererComponent>();
        sc.size = *size;
    }

    static void SpriteRenderer_GetColor(uint32_t id, glm::vec4 *color)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &sc = entity.get_component<SpriteRendererComponent>();
        *color = sc.color;
    }

    static void SpriteRenderer_SetColor(uint32_t id, glm::vec4 *color)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &sc = entity.get_component<SpriteRendererComponent>();
        sc.color = *color;
    }

    static void RigidBody2D_GetVelocity(uint32_t id, glm::vec2 *velocity)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &rc = entity.get_component<RigidBody2DComponent>();
        *velocity = rc.velocity;
    }

    static void RigidBody2D_SetVelocity(uint32_t id, glm::vec4 *velocity)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &rc = entity.get_component<RigidBody2DComponent>();
        rc.velocity = *velocity;
    }

    static void RigidBody2D_GetAngularVelocity(uint32_t id, float *velocity)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &rc = entity.get_component<RigidBody2DComponent>();
        *velocity = rc.angular_velocity;
    }

    static void RigidBody2D_SetAngularVelocity(uint32_t id, float *velocity)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &rc = entity.get_component<RigidBody2DComponent>();
        rc.angular_velocity = *velocity;
    }

    static void Tag_GetValue(uint32_t id, MonoString **str)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &tc = entity.get_component<TagComponent>();
        *str = mono_string_new(mono_domain_get(), tc.tag.c_str());
    }

    static void Tag_SetValue(uint32_t id, MonoString **str)
    {
        Entity entity = Scene::current()->get_entity_by_id(entt::entity{id});
        auto &tc = entity.get_component<TagComponent>();
        char *cstr = mono_string_to_utf8(*str);
        tc.tag = cstr;
        mono_free(cstr);
    }

    static void add_internal_calls()
    {
        MT_ADD_INTERNAL_CALL(Logger_Log);
        MT_ADD_INTERNAL_CALL(Entity_HasComponent);
        MT_ADD_INTERNAL_CALL(Entity_GetByName);
        MT_ADD_INTERNAL_CALL(TransformComponent_GetPosition);
        MT_ADD_INTERNAL_CALL(TransformComponent_SetPosition);
        MT_ADD_INTERNAL_CALL(TransformComponent_GetRotation);
        MT_ADD_INTERNAL_CALL(TransformComponent_SetRotation);
        MT_ADD_INTERNAL_CALL(TransformComponent_GetScale);
        MT_ADD_INTERNAL_CALL(TransformComponent_SetScale);
        MT_ADD_INTERNAL_CALL(SpriteRenderer_GetSize);
        MT_ADD_INTERNAL_CALL(SpriteRenderer_SetSize);
        MT_ADD_INTERNAL_CALL(SpriteRenderer_GetColor);
        MT_ADD_INTERNAL_CALL(SpriteRenderer_SetColor);
        MT_ADD_INTERNAL_CALL(RigidBody2D_GetVelocity);
        MT_ADD_INTERNAL_CALL(RigidBody2D_SetVelocity);
        MT_ADD_INTERNAL_CALL(RigidBody2D_GetAngularVelocity);
        MT_ADD_INTERNAL_CALL(RigidBody2D_SetAngularVelocity);
        MT_ADD_INTERNAL_CALL(Tag_GetValue);
        MT_ADD_INTERNAL_CALL(Tag_SetValue);
    }

    static void register_components(MonoImage *image)
    {
        MT_REGISTER_COMPONENT(image, TransformComponent);
        MT_REGISTER_COMPONENT(image, SpriteRendererComponent);
        MT_REGISTER_COMPONENT(image, RigidBody2DComponent);
        MT_REGISTER_COMPONENT(image, TagComponent);
    }
}

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
    register_components(m_image);
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

        std::string class_name = mono_class_get_name(klass);
        std::string name_space = mono_class_get_namespace(klass);
        std::string full_name = name_space + "." + class_name;

        if (class_name == "<Module>")
            continue;

        if (full_name == "Magnetar.Core.ScriptableEntity")
            continue;

        LOG_TRACE(logger::tags::scripting, "found class {}", full_name);
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

void magnetar::MonoRuntime::update(float delta_time)
{
    for (auto &pair : m_entity_instances)
        pair.second->invoke_on_update(delta_time);
}

magnetar::ScriptInstance *magnetar::MonoRuntime::create_entity_instance(const std::string &name, EntityHandle handle)
{
    auto klass = ScriptRegistry::find(name);
    auto instance = klass->create_instance();
    m_entity_instances.emplace(handle, std::move(instance));
    m_entity_instances[handle]->invoke_ctor();
    void *args[1];
    args[0] = &handle;
    m_entity_instances[handle]->invoke_set_handle(handle);
    m_entity_instances[handle]->invoke_on_start();
    return m_entity_instances[handle].get();
}

void magnetar::MonoRuntime::remove_entity_instance(EntityHandle handle)
{
    auto it = m_entity_instances.find(handle);
    if (it != m_entity_instances.end())
        m_entity_instances.erase(it);
}