#include <algorithm>
#include "magnetar/scene/ecs.h"
#include "magnetar/scene/components.h"

std::unordered_map<std::type_index, magnetar::ComponentID> magnetar::IComponent::s_component_ids;
magnetar::ComponentID magnetar::IComponent::s_next_component_id = 0;

magnetar::Entity::Entity(Registry *registry, EntityHandle handle)
    : m_registry(registry), m_handle(handle) {}

void magnetar::Entity::mark_destroyed()
{
    m_signature.reset();
    m_registry->mark_entity_destroyed(m_handle);
}

void magnetar::System::add_entity(EntityHandle handle)
{
    auto it = std::find(entity_handles.begin(), entity_handles.end(), handle);
    if (it != entity_handles.end())
        return;
    LOG_INFO(logger::tags::scene, "added entity {} to {}", handle, class_name());
    entity_handles.push_back(handle);
}

void magnetar::System::remove_entity(EntityHandle handle)
{
    auto it = std::find(entity_handles.begin(), entity_handles.end(), handle);
    if (it == entity_handles.end())
        return;
    LOG_INFO(logger::tags::scene, "removed entity {} from {}", handle, class_name());
    entity_handles.erase(it);
}

bool magnetar::System::test_signature(const ComponentSignature &signature) const
{
    bool success = true;
    for (ComponentID id = 0; id < MAX_COMPONENTS; id++)
    {
        if (m_signature.test(id) && !signature.test(id))
        {
            success = false;
            break;
        }
    }

    return success;
}

bool magnetar::System::entity_is_registered(EntityHandle handle) const
{
    auto it = std::find(entity_handles.begin(), entity_handles.end(), handle);
    return it != entity_handles.end();
}

magnetar::Registry::Registry()
    : m_next_entity_handle(0) {}

magnetar::Ref<magnetar::Entity> magnetar::Registry::create_entity()
{
    EntityHandle handle = 0;
    if (m_free_entity_handles.empty())
    {
        handle = m_next_entity_handle++;
        m_entities.push_back(nullptr);
    }
    else
    {
        handle = m_free_entity_handles.top();
        m_free_entity_handles.pop();
    }

    auto entity = create_reference<Entity>(this, handle);
    m_entities[entity->handle()] = entity;
    LOG_DEBUG(logger::tags::scene, "created entity {}", entity->handle());

    entity->add_component<TransformComponent>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    return entity;
}

magnetar::Ref<magnetar::Entity> magnetar::Registry::get_entity_by_handle(EntityHandle handle)
{
    if (handle >= m_entities.size())
        return nullptr;
    return m_entities[handle];
}

void magnetar::Registry::flush()
{
    for (auto handle : m_destroyed_entity_handles)
    {
        for (auto &pair : m_component_pools)
            pair.second->destroy(handle);
        on_signature_change(handle);
        m_entities[handle] = nullptr;
        m_free_entity_handles.push(handle);
        LOG_INFO(logger::tags::scene, "destroyed entity {}", handle);
    }

    m_destroyed_entity_handles.clear();
}

void magnetar::Registry::mark_entity_destroyed(EntityHandle handle)
{
    auto it = std::find(m_destroyed_entity_handles.begin(), m_destroyed_entity_handles.end(), handle);
    if (it != m_destroyed_entity_handles.end())
        return;

    LOG_DEBUG(logger::tags::scene, "marked entity {} as destroyed", handle);
    m_destroyed_entity_handles.push_back(handle);
}

void magnetar::Registry::mark_entity_destroyed(Ref<Entity> entity)
{
    mark_entity_destroyed(entity->handle());
}

void magnetar::Registry::on_signature_change(EntityHandle handle)
{
    for (auto &pair : m_systems)
    {
        auto system = pair.second;
        bool matches = system->test_signature(m_entities[handle]->signature());
        bool is_registered = system->entity_is_registered(handle);
        if (matches && !is_registered)
        {
            LOG_TRACE(logger::tags::scene, "entity {} matches {} signature", handle, system->class_name());
            system->add_entity(handle);
        }
        else if (!matches && is_registered)
        {
            LOG_TRACE(logger::tags::scene, "entity {} no longer matches {} signature", handle, system->class_name());
            system->remove_entity(handle);
        }
    }
}