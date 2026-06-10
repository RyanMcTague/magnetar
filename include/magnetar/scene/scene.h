#pragma once
#include <entt/entt.hpp>
#include "magnetar/core/base.h"
#include "magnetar/renderer/camera.h"
namespace magnetar
{
    class Entity;
    class MAGNETAR_API Scene
    {
    public:
        Scene(): m_camera(nullptr) {}
        Scene(Ref<Camera> camera): m_camera(camera) {};
        // Scene(const Scene &) = delete;
        // Scene &operator=(const Scene &) = delete;

        entt::registry& registry() { return m_registry; }

        Entity create_entity();

        void destroy_entity(const Entity& entity);

        Entity get_entity(entt::entity id);

        Ref<Camera> camera() { return m_camera; }
    private:
        entt::registry m_registry;
        Ref<Camera> m_camera;
    };
}