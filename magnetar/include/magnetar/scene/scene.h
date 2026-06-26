#pragma once
#include <entt/entt.hpp>
#include <vector>
#include <unordered_map>
#include <set>
#include "magnetar/core/base.h"
#include "magnetar/renderer/camera.h"
#include "magnetar/events/event_system.h"
#include "magnetar/scene/entity_handle.h"

namespace magnetar
{
    class Entity;

    struct MAGNETAR_API EntityDestroyedEvent
    {
        MT_DECLARE_CLASS_NAME(EntityDestroyedEvent)

        EntityHandle handle;
    };

    struct EntityComponentAddedEvent
    {
        MT_DECLARE_CLASS_NAME(EntityComponentAddedEvent)

        EntityHandle handle;
        std::string component_class_name;

        EntityComponentAddedEvent(EntityHandle handle, const std::string& component_class_name)
            : handle(handle), component_class_name(component_class_name) {}
    };

    struct EntityComponentRemovedEvent
    {
        MT_DECLARE_CLASS_NAME(EntityComponentRemovedEvent)

        EntityHandle handle;
        std::string component_class_name;

        EntityComponentRemovedEvent(EntityHandle handle, const std::string& component_class_name)
            : handle(handle), component_class_name(component_class_name) {}
    };

    class MAGNETAR_API Scene
    {
    public:
        Scene();
        ~Scene();

        static Scene* current();

        Entity create_entity();

        Entity get_entity_by_id(EntityHandle handle);

        Entity get_entity_by_name(const std::string_view& name);

        void mark_entity_handle_destroyed(EntityHandle handle);

        void flush_entities();

        template <typename... T>
        auto view_with_components()
        {
            return m_registry.view<T...>();
        }

        void begin_scene();
        void end_scene();

        void on_render();
        void on_update(float delta_time);

        void set_camera(Ref<Camera> camera) { m_camera = camera; }
        Ref<Camera> camera() { return m_camera; }

    private:
        friend class Entity;
        static Scene* s_current;
        entt::registry m_registry;
        Ref<Camera> m_camera;
        std::set<EntityHandle> m_destroyed_entities;
        EventHandle m_eh_component_added;
        EventHandle m_eh_component_removed;


        void on_component_added(const EntityComponentAddedEvent& event);
        void on_component_removed(const EntityComponentRemovedEvent& event);
    };

}