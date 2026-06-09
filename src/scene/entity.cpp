#include "magnetar/scene/entity.h"

magnetar::Entity::Entity(Scene* scene, entt::entity handle)
    : m_handle(handle), m_scene(scene) {}