#include <glm/gtc/matrix_transform.hpp>
#include "magnetar/core/game_layer.h"
#include "magnetar/scene/components.h"
#include "magnetar/scene/entity.h"
#include "magnetar/assets/asset_manager.h"
#include "magnetar/renderer/renderer.h"

void magnetar::GameLayer::on_attach()
{
}

void magnetar::GameLayer::on_detach()
{
}

void magnetar::GameLayer::on_update(float)
{
}

void magnetar::GameLayer::on_render()
{
    glm::mat4 model;
    auto view = m_scene->registry().view<TransformComponent, MeshRendererComponent>();

    Renderer::begin_scene(m_scene->camera());
    for (auto &handle : view)
    {
        auto entity = m_scene->get_entity(handle);
        auto &transform = entity.get_component<TransformComponent>();
        auto &mesh_renderer = entity.get_component<MeshRendererComponent>();

        model = glm::mat4(1.0f);
        model = glm::translate(glm::mat4(1.0f), transform.position);
        model = glm::rotate(model, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, transform.scale);

        Renderer::submit(AssetManager::get<Mesh>(mesh_renderer.mesh),
                         AssetManager::get<Material>(mesh_renderer.material), model);
    }
    Renderer::end_scene();
}
