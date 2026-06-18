#pragma once
#include <entt/entt.hpp>
#include "magnetar/core/base.h"
#include "magnetar/scene/scene.h"
#include "magnetar/scene/entity_handle.h"

namespace magnetar
{
    class MAGNETAR_API Entity
    {
    public:
        Entity();
        Entity(Scene *scene, EntityHandle handle);

        template <typename T>
        T &add_component(const T &component);

        template <typename T>
        bool has_component();

        template <typename T>
        T &get_component();

        template<typename T>
        void remove_component();

        void mark_destroyed();

        operator bool() const { return m_handle != entt::null; }

        EntityHandle handle() const { return m_handle; }

    private:
        Scene *m_scene;
        EntityHandle m_handle;        
    };

    template <typename T>
    T &Entity::add_component(const T &component)
    {
        auto &c = m_scene->m_registry.emplace<T>(m_handle, component);
        LOG_INFO(logger::tags::scene, "added {} to entity {}", MT_STATIC_CLASS_NAME(T), static_cast<uint32_t>(m_handle));
        EventSystem::emit(EntityComponentAddedEvent(m_handle, MT_STATIC_CLASS_NAME(T)));
        return c;
    }

    template <typename T>
    bool Entity::has_component()
    {
        bool result = m_scene->m_registry.all_of<T>(m_handle);
        return result;
    }

    template <typename T>
    T &Entity::get_component()
    {
        MT_ASSERT(has_component<T>(), "entity {} does not contain {}", static_cast<uint32_t>(m_handle), MT_STATIC_CLASS_NAME(T));
        auto &component = m_scene->m_registry.get<T>(m_handle);
        return component;
    }

    template<typename T>
    void Entity::remove_component()
    {
        m_scene->m_registry.remove<T>(m_handle);
        LOG_INFO(logger::tags::scene, "removed {} from entity {}", MT_STATIC_CLASS_NAME(T), static_cast<uint32_t>(m_handle));
        EventSystem::emit(EntityComponentRemovedEvent(m_handle, MT_STATIC_CLASS_NAME(T)));
    }
}