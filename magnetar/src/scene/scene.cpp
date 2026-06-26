#include "magnetar/scene/scene.h"
#include "magnetar/scene/entity.h"
#include "magnetar/scene/components.h"
#include "magnetar/scripting/script_engine.h"
#include "magnetar/renderer/renderer2d.h"
#include "magnetar/math/rect.h"
#include "magnetar/assets/asset_manager.h"
#include "magnetar/renderer/font.h"

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
    {
        ScriptEngine::remove_entity_instance(handle);
        m_registry.destroy(handle);
    }
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
    {
        auto view = view_with_components<TransformComponent, SpriteRendererComponent>();
        for (auto [_, transform, sr] : view.each())
        {
            if (sr.texture)
                Renderer2D::draw_quad(transform.position, sr.size, transform.rotation.z, AssetManager::load<Texture2D>(sr.texture));
            else
                Renderer2D::draw_quad(transform.position, sr.size, transform.rotation.z, sr.color);
        }
    }
    {
        auto view = view_with_components<TransformComponent, TextRendererComponent>();
        for (auto [_, transform, tr] : view.each())
        {
            if (tr.font != 0)
            {
                Renderer2D::draw_text(tr.value, AssetManager::load<Font>(tr.font), transform.position, tr.color);
            }
        }
    }
}

void magnetar::Scene::on_update(float delta_time)
{
    ScriptEngine::update(delta_time);
    ScriptEngine::start_all_entity_instances();
    {
        auto view = view_with_components<TransformComponent, RigidBody2DComponent>();
        for (auto [_, transform, rb] : view.each())
        {
            transform.position.x += rb.velocity.x * delta_time;
            transform.position.y += rb.velocity.y * delta_time;
            transform.rotation.z += rb.angular_velocity * delta_time;
        }
    }
    {
        auto view = view_with_components<TransformComponent, BoxColliderComponent>();
        for (auto [handle, transform, collider] : view.each())
        {
            Rect rect;
            rect.bl = glm::vec2(collider.position.x + transform.position.x, collider.position.y + transform.position.y);
            rect.tr = glm::vec2(rect.bl.x + collider.size.x, rect.bl.y + collider.size.y);

            for (auto [o_handle, o_transform, o_collider] : view.each())
            {
                if (handle == o_handle)
                    continue;

                Rect o_rect;
                o_rect.bl = glm::vec2(o_collider.position.x + o_transform.position.x, o_collider.position.y + o_transform.position.y);
                o_rect.tr = glm::vec2(o_rect.bl.x + o_collider.size.x, o_rect.bl.y + o_collider.size.y);

                if (rect.is_overlapping(o_rect))
                {
                    auto instance = ScriptEngine::get_entity_instance(handle);
                    auto o_instance = ScriptEngine::get_entity_instance(o_handle);
                    if (instance && o_instance && instance->has_method("OnCollision"))
                    {
                        instance->invoke_on_collision(o_instance);
                    }
                }
            }
        }
    }
    flush_entities();
}

void magnetar::Scene::on_component_added(const EntityComponentAddedEvent &event)
{
    if (event.component_class_name == std::string(MT_STATIC_CLASS_NAME(ScriptComponent)))
    {
        auto &component = m_registry.get<ScriptComponent>(event.handle);
        if (component.skip_add)
            return;
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