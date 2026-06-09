#pragma once
#include <entt/entt.hpp>
#include "magnetar/core/base.h"

namespace magnetar
{
    class Entity;
    class MAGNETAR_API Scene
    {
    public:
        Scene() = default;
        Scene(const Scene &) = delete;
        Scene &operator=(const Scene &) = delete;

        entt::registry& registry() { return m_registry; }

        Entity create_entity();
    private:
        entt::registry m_registry;
    };
}