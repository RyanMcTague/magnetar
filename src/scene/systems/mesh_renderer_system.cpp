#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "magnetar/scene/systems/mesh_renderer_system.h"
#include "magnetar/scene/components.h"
#include "magnetar/renderer/renderer.h"
#include "magnetar/assets/asset_manager.h"

void magnetar::MeshRendererSystem::setup()
{
    require_component<TransformComponent>();
    require_component<MeshRendererComponent>();
}

void magnetar::MeshRendererSystem::render()
{
    static glm::mat4 model;

    for (auto handle : entity_handles)
    {
        auto entity = registry()->get_entity_by_handle(handle);
        auto transform = entity->get_component<TransformComponent>();
        auto mesh_renderer = entity->get_component<MeshRendererComponent>();

        model = glm::mat4(1.0f);
        model = glm::translate(model, transform->position);
        model = glm::rotate(model, transform->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, transform->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, transform->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, transform->scale);
        Renderer::submit(
            AssetManager::get<Mesh>(mesh_renderer->mesh),
            AssetManager::get<Material>(mesh_renderer->material),
            model);
    }
}