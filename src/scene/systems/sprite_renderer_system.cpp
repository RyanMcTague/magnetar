#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "magnetar/scene/systems/sprite_renderer_system.h"
#include "magnetar/scene/components.h"
#include "magnetar/renderer/renderer.h"
#include "magnetar/assets/asset_manager.h"

void magnetar::SpriteRendererSystem::setup()
{
    m_batch = create_reference<SpriteBatch>(80);
    require_component<TransformComponent>();
    require_component<SpriteRendererComponent>();
}

void magnetar::SpriteRendererSystem::render()
{
    for (auto handle : entity_handles)
    {
        auto entity = registry()->get_entity_by_handle(handle);
        auto transform = entity->get_component<TransformComponent>();
        auto sprite_renderer = entity->get_component<SpriteRendererComponent>();
    }
}