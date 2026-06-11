#pragma once
#include "magnetar/core/base.h"
#include "magnetar/scene/ecs.h"

namespace magnetar
{
    class MAGNETAR_API MeshRendererSystem: public System
    {
    public:
        MeshRendererSystem(Registry* registry)
            : System(registry) {}

        void setup() override;

        void render();

        const char* class_name() override { return "MeshRendererSystem"; }
    };
}