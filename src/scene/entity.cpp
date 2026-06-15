#include "magnetar/scene/entity.h"

magnetar::Entity::Entity()
    : m_scene(nullptr), m_handle(entt::null) {}


magnetar::Entity::Entity(Scene *scene, EntityHandle handle)
    : m_scene(scene), m_handle(handle) {}

void magnetar::Entity::mark_destroyed()
{
    m_scene->mark_entity_handle_destroyed(m_handle);
}