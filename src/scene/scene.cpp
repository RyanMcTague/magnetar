#include "magnetar/scene/scene.h"
#include "magnetar/scene/entity.h"

magnetar::Entity magnetar::Scene::create_entity()
{
    auto handle = m_registry.create();
    return Entity(this, handle);
}