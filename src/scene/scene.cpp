#include "magnetar/scene/scene.h"
#include "magnetar/scene/entity.h"
#include "magnetar/scene/components.h"

magnetar::Entity magnetar::Scene::create_entity()
{
    auto handle = m_registry.create();
    auto entity = Entity(this, handle);
    entity.add_component<TransformComponent>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    return entity;
}

void magnetar::Scene::destroy_entity(const Entity& entity)
{
    m_registry.destroy(entity.handle());
}

magnetar::Entity magnetar::Scene::get_entity(entt::entity id)
{
    return Entity(this, id);
}