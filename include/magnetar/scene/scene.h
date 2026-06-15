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

    class MAGNETAR_API Scene
    {
    public:
        Scene();

        Entity create_entity();

        Entity get_entity_by_id(EntityHandle handle);

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

        void set_camera(Ref<Camera> camera) { m_camera = camera; }

    private:
        friend class Entity;
        entt::registry m_registry;
        Ref<Camera> m_camera;
        std::set<EntityHandle> m_destroyed_entities;
    };

}