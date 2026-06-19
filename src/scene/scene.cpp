#include "magnetar/scene/scene.h"
#include "magnetar/scene/entity.h"
#include "magnetar/scene/components.h"
#include "magnetar/scripting/script_engine.h"
#include "magnetar/renderer/renderer2d.h"

magnetar::Scene *magnetar::Scene::s_current = nullptr;

magnetar::Scene::Scene()
{
    s_current = this;
    m_eh_component_added = EventSystem::subscribe<EntityComponentAddedEvent>(this, &Scene::on_component_added);
    m_eh_component_removed = EventSystem::subscribe<EntityComponentRemovedEvent>(this, &Scene::on_component_removed);
}

magnetar::Scene::~Scene()
{
    EventSystem::unsubscribe(m_eh_component_added);
    EventSystem::unsubscribe(m_eh_component_removed);
}

magnetar::Scene *magnetar::Scene::current()
{
    return s_current;
}

magnetar::Entity magnetar::Scene::create_entity()
{
    auto handle = m_registry.create();
    auto entity = Entity(this, handle);
    auto default_tag = fmt::format("entity#{:08x}", static_cast<uint32_t>(handle));
    entity.add_component(TransformComponent(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    entity.add_component(TagComponent(default_tag));
    return entity;
}

magnetar::Entity magnetar::Scene::get_entity_by_id(EntityHandle handle)
{
    if (!m_registry.valid(handle))
        return Entity(this, entt::null);
    return Entity(this, handle);
}

magnetar::Entity magnetar::Scene::get_entity_by_name(const std::string_view &name)
{
    auto view = m_registry.view<TagComponent>();
    for (auto handle : view)
    {
        const TagComponent &tc = view.get<TagComponent>(handle);
        if (tc.tag == name)
            return Entity(this, handle);
    }
    return Entity(this, entt::null);
}

void magnetar::Scene::mark_entity_handle_destroyed(EntityHandle handle)
{
    if (!m_destroyed_entities.contains(handle))
        LOG_DEBUG(logger::tags::scene, "marking entity {} as destroyed", static_cast<uint32_t>(handle));
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
    auto view = view_with_components<TransformComponent, SpriteRendererComponent>();
    for (auto [_, transform, sr] : view.each())
    {
        Renderer2D::draw_quad(transform.position, sr.size, transform.rotation.z, sr.color);
    }
}

void magnetar::Scene::on_update(float delta_time)
{
    auto view = view_with_components<TransformComponent, RigidBody2DComponent>();
    for (auto [_, transform, rb] : view.each())
    {
        transform.position.x += rb.velocity.x * delta_time;
        transform.position.y += rb.velocity.y * delta_time;

        transform.rotation += rb.angular_velocity * delta_time;
    }
    ScriptEngine::update(delta_time);
}

void magnetar::Scene::on_component_added(const EntityComponentAddedEvent &event)
{
    if (event.component_class_name == std::string(MT_STATIC_CLASS_NAME(ScriptComponent)))
    {
        auto &component = m_registry.get<ScriptComponent>(event.handle);
        ScriptEngine::create_entity_instance(component.script_class_name, event.handle);
    }
}

void magnetar::Scene::on_component_removed(const EntityComponentRemovedEvent &event)
{
    if (event.component_class_name == std::string(MT_STATIC_CLASS_NAME(ScriptComponent)))
    {
        ScriptEngine::remove_entity_instance(event.handle);
    }
}