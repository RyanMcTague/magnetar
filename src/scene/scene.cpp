#include "magnetar/scene/scene.h"
#include "magnetar/scene/entity.h"
#include "magnetar/scene/components.h"
#include "magnetar/renderer/renderer2d.h"
namespace magnetar
{
    static inline Entity create_null_entity(Scene *scene)
    {
        return Entity(scene, entt::null);
    }
}

magnetar::Scene::Scene()
{
}

magnetar::Entity magnetar::Scene::create_entity()
{
    auto handle = m_registry.create();
    auto entity = Entity(this, handle);
    entity.add_component(TransformComponent(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    return entity;
}

magnetar::Entity magnetar::Scene::get_entity_by_id(EntityHandle handle)
{
    if (!m_registry.valid(handle))
        return Entity(this, entt::null);
    return create_null_entity(this);
}

void magnetar::Scene::mark_entity_handle_destroyed(EntityHandle handle)
{
    m_destroyed_entities.emplace(handle);
}

void magnetar::Scene::flush_entities()
{
    for (auto handle : m_destroyed_entities)
        m_registry.destroy(handle);

    m_destroyed_entities.clear();
}

void magnetar::Scene::begin_scene()
{
    Renderer2D::start(m_camera->matrix());
}
void magnetar::Scene::end_scene()
{
    Renderer2D::submit();
}

void magnetar::Scene::on_render()
{
    auto view = m_registry.view<TransformComponent, SpriteRendererComponent>();
    for (auto [_, transform, sr] : view.each())
    {
        Renderer2D::draw_quad(transform.position, sr.size, transform.rotation.z, sr.color);
    }
}