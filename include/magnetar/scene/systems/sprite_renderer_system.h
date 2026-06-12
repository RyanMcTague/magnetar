#pragma once
#include "magnetar/core/base.h"
#include "magnetar/scene/ecs.h"
#include "magnetar/renderer/sprite_batch.h"

namespace magnetar
{
    class MAGNETAR_API SpriteRendererSystem: public System
    {
    public:
        SpriteRendererSystem(Registry* registry)
            : System(registry) {}

        void setup() override;

        void render();

        const char* class_name() override { return "SpriteRendererSystem"; }

    private:
        Ref<SpriteBatch> m_batch;
    };
}