#pragma once
#include <entt/entt.hpp>
#include "magnetar/core/base.h"
#include "magnetar/scene/scene.h"

namespace magnetar
{
    class MAGNETAR_API Entity
    {
    public:
        Entity(Scene *scene, entt::entity handle = entt::null);

        bool exists() const { return m_handle != entt::null; }

        template<typename T, typename ...TArgs>
        T& add_component(TArgs&& ...args) const;

        template<typename T, typename ...TArgs>
        T& add_or_replace_component(TArgs&& ...args) const;

        template<typename T>
        T& get_component() const;

        template<typename T>
        bool has_component() const;

        template<typename T>
        void remove_component() const;

    private:
        entt::entity m_handle;
        Scene *m_scene;
    };


    template<typename T, typename ...TArgs>
    T& Entity::add_component(TArgs&& ...args) const
    {
        auto& component = m_scene->registry().emplace<T>(m_handle, std::forward<TArgs>(args)...);
        LOG_INFO(logger::tags::scene, "added {} component to entity {}", MT_STATIC_CLASS_NAME(T), static_cast<int>(m_handle));
        return component;
    }

    template<typename T, typename ...TArgs>
    T& Entity::add_or_replace_component(TArgs&& ...args) const
    {
        bool replaced = has_component<T>();
        auto& component = m_scene->registry().emplace_or_replace<T>(m_handle, std::forward<TArgs>(args)...);
        if(replaced)
            LOG_INFO(logger::tags::scene, "replaced {} component from entity {}", MT_STATIC_CLASS_NAME(T), static_cast<int>(m_handle));
        else
            LOG_INFO(logger::tags::scene, "added {} component to entity {}", MT_STATIC_CLASS_NAME(T), static_cast<int>(m_handle));
        return component;
    }

    template<typename T>
    bool Entity::has_component() const
    {
        bool result = m_scene->registry().all_of<T>(m_handle);
        return result;
    }

    template<typename T>
    T& Entity::get_component() const
    {
        MT_ASSERT(has_component<T>(), "expected entity to have a {} component but it does not", MT_STATIC_CLASS_NAME(T));
        auto& component = m_scene->registry().get<T>(m_handle);
        return component;
    }

    template<typename T>
    void Entity::remove_component() const
    {
        auto num_removed = m_scene->registry().remove<T>(m_handle);
        if(num_removed > 0)
            LOG_INFO(logger::tags::scene, "removed {} component from entity {}", MT_STATIC_CLASS_NAME(T), static_cast<int>(m_handle));
    }
}