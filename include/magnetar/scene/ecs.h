#pragma once
#include <bitset>
#include <vector>
#include <stack>
#include <unordered_map>
#include "magnetar/core/base.h"

namespace magnetar
{
    class Registry;

    static constexpr uint32_t MAX_COMPONENTS = 10;

    using EntityHandle = uint32_t;
    using ComponentID = uint32_t;
    using ComponentSignature = std::bitset<MAX_COMPONENTS>;

    class MAGNETAR_API Entity
    {
    public:
        Entity(Registry *registry, EntityHandle handle);

        const ComponentSignature &signature() const { return m_signature; }

        EntityHandle handle() const { return m_handle; }

        void mark_destroyed();

        template <typename T, typename... TArgs>
        Ref<T> add_component(TArgs &&...args);

        template <typename T>
        Ref<T> get_component();

        template <typename T>
        bool has_component();

        template <typename T>
        bool remove_component();

    private:
        Registry *m_registry;
        EntityHandle m_handle;
        ComponentSignature m_signature;
    };

    class MAGNETAR_API IComponentPool
    {
    public:
        virtual ~IComponentPool() = default;

        virtual bool destroy(EntityHandle handle) = 0;
        virtual bool contains(EntityHandle handle) = 0;
    };

    template <typename TComponent>
    class MAGNETAR_API ComponentPool : public IComponentPool
    {
    public:
        bool add(EntityHandle handle, Ref<TComponent> component);
        bool replace(EntityHandle handle, Ref<TComponent> component);

        Ref<TComponent> get(EntityHandle handle);
        bool destroy(EntityHandle handle) override;
        bool contains(EntityHandle handle) override;

    private:
        std::unordered_map<EntityHandle, Ref<TComponent>> m_components;
    };

    class IComponent
    {
    public:
        virtual ~IComponent() = default;

        static ComponentID max_id()
        {
            if (s_next_component_id == 0)
                return 0;

            return s_next_component_id - 1;
        }

    protected:
        static std::unordered_map<std::type_index, ComponentID> s_component_ids;
        static ComponentID s_next_component_id;
    };

    template <typename T>
    class MAGNETAR_API Component : public IComponent
    {
    public:
        static ComponentID get_id();
        static const char *class_name();

    private:
        Component() = default;
    };

    class MAGNETAR_API System
    {
    public:
        System(Registry *registry)
            : m_registry(registry) {}

        virtual ~System() = default;
        virtual void setup() = 0;

        void add_entity(EntityHandle handle);
        void remove_entity(EntityHandle handle);

        bool test_signature(const ComponentSignature &signature) const;
        bool entity_is_registered(EntityHandle handle) const;

        virtual const char *class_name() = 0;

    protected:
        std::vector<EntityHandle> entity_handles;

        template <typename T>
        void require_component();

        Registry *registry() { return m_registry; }

    private:
        ComponentSignature m_signature;
        Registry *m_registry;
    };

    class MAGNETAR_API Registry
    {
    public:
        Registry();

        void flush();

        Ref<Entity> create_entity();
        Ref<Entity> get_entity_by_handle(EntityHandle handle);


        void mark_entity_destroyed(EntityHandle handle);
        void mark_entity_destroyed(Ref<Entity> entity);

        template <typename T, typename... TArgs>
        Ref<T> add_component(EntityHandle handle, TArgs &&...args);

        template <typename T>
        Ref<T> get_component(EntityHandle handle);

        template <typename T>
        bool remove_component(EntityHandle handle);

        template <typename T>
        Ref<T> get_system();

        template <typename T, typename ...TArgs>
        void register_system(TArgs&& ...args);

    private:
        EntityHandle m_next_entity_handle;
        std::stack<EntityHandle> m_free_entity_handles;
        std::vector<EntityHandle> m_destroyed_entity_handles;

        std::vector<Ref<Entity>> m_entities;
        std::unordered_map<std::type_index, Ref<IComponentPool>> m_component_pools;
        std::unordered_map<std::type_index, Ref<System>> m_systems;

        template <typename T>
        Ref<ComponentPool<T>> get_component_pool();

        template <typename T>
        Ref<ComponentPool<T>> get_or_create_component_pool();

        void on_signature_change(EntityHandle handle);
    };

    // ================================================================
    //  Entity Template Implementation
    // ================================================================

    template <typename T, typename... TArgs>
    Ref<T> Entity::add_component(TArgs &&...args)
    {
        m_signature.set(Component<T>::get_id(), true);
        auto component = m_registry->add_component<T>(m_handle, std::forward<TArgs>(args)...);
        return component;
    }

    template <typename T>
    Ref<T> Entity::get_component()
    {
        return m_registry->get_component<T>(m_handle);
    }

    template <typename T>
    bool Entity::has_component()
    {
        return m_signature.test(Component<T>::get_id());
    }

    template <typename T>
    bool Entity::remove_component()
    {
        m_signature.reset(Component<T>::get_id());
        return m_registry->remove_component<T>(m_handle);
    }

    // ================================================================
    //  ComponentPool Template Implementation
    // ================================================================

    template <typename TComponent>
    bool ComponentPool<TComponent>::add(EntityHandle handle, Ref<TComponent> component)
    {
        auto it = m_components.find(handle);
        if (it != m_components.end())
            return false;

        m_components.emplace(handle, component);
        return true;
    }

    template <typename TComponent>
    bool ComponentPool<TComponent>::replace(EntityHandle handle, Ref<TComponent> component)
    {
        auto it = m_components.find(handle);
        if (it == m_components.end())
            return false;

        m_components[handle] = component;
        return true;
    }

    template <typename TComponent>
    Ref<TComponent> ComponentPool<TComponent>::get(EntityHandle handle)
    {
        auto it = m_components.find(handle);
        if (it == m_components.end())
            return nullptr;
        return it->second;
    }

    template <typename TComponent>
    bool ComponentPool<TComponent>::destroy(EntityHandle handle)
    {
        auto it = m_components.find(handle);
        if (it == m_components.end())
            return false;

        m_components.erase(it);
        return true;
    }

    template <typename TComponent>
    bool ComponentPool<TComponent>::contains(EntityHandle handle)
    {
        auto it = m_components.find(handle);
        return it != m_components.end();
    }

    // ================================================================
    //  Component Template Implementation
    // ================================================================

    template <typename T>
    ComponentID Component<T>::get_id()
    {
        auto it = s_component_ids.find(typeid(T));
        if (it != s_component_ids.end())
            return it->second;

        ComponentID id = s_next_component_id++;
        s_component_ids.emplace(typeid(T), id);
        return id;
    }

    template <typename T>
    const char *Component<T>::class_name()
    {
        return MT_STATIC_CLASS_NAME(T);
    }

    // ================================================================
    //  System Template Implementation
    // ================================================================

    template <typename T>
    void System::require_component()
    {
        m_signature.set(Component<T>::get_id());
    }

    // ================================================================
    //  Registry Template Implementation
    // ================================================================

    template <typename T, typename... TArgs>
    Ref<T> Registry::add_component(EntityHandle handle, TArgs &&...args)
    {
        Ref<ComponentPool<T>> pool = get_or_create_component_pool<T>();
        auto component = create_reference<T>(std::forward<TArgs>(args)...);
        if (!pool->add(handle, component))
        {
            LOG_DEBUG(logger::tags::scene, "entity {} already has {}", handle, Component<T>::class_name());
            return nullptr;
        }
        LOG_DEBUG(logger::tags::scene, "added {} to entity {}", Component<T>::class_name(), handle);
        on_signature_change(handle);
        return component;
    }

    template <typename T>
    Ref<T> Registry::get_component(EntityHandle handle)
    {
        auto pool = get_component_pool<T>();
        if (!pool)
            return nullptr;

        return pool->get(handle);
    }

    template <typename T>
    bool Registry::remove_component(EntityHandle handle)
    {
        auto pool = get_component_pool<T>();
        if (!pool)
            return false;

        if (!pool->remove(handle))
            return false;
        on_signature_change(handle);

        LOG_DEBUG(logger::tags::scene, "removed {} from entity {}", Component<T>::class_name(), handle);
        return true;
    }

    template <typename T>
    Ref<T> Registry::get_system()
    {
        auto it = m_systems.find(typeid(T));
        return it == m_systems.end() ? nullptr : std::static_pointer_cast<T>(it->second);
    }

    template <typename T, typename ...TArgs>
    void Registry::register_system(TArgs&& ...args)
    {
        if (get_system<T>() != nullptr)
            return;

        Ref<T> ref = create_reference<T>(this, std::forward<TArgs>(args)...);
        Ref<System> system = std::static_pointer_cast<T>(ref);
        m_systems.emplace(typeid(T), system);
        system->setup();
    }

    template <typename T>
    Ref<ComponentPool<T>> Registry::get_component_pool()
    {
        auto it = m_component_pools.find(typeid(T));
        if (it == m_component_pools.end())
            return nullptr;
        return std::static_pointer_cast<ComponentPool<T>>(it->second);
    }

    template <typename T>
    Ref<ComponentPool<T>> Registry::get_or_create_component_pool()
    {
        auto pool = get_component_pool<T>();
        if (pool)
            return pool;

        pool = create_reference<ComponentPool<T>>();
        m_component_pools.emplace(typeid(T), std::static_pointer_cast<IComponentPool>(pool));
        return pool;
    }
}