#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "magnetar/core/base.h"
#include "magnetar/assets/asset_handle.h"
#include "magnetar/renderer/camera.h"

namespace magnetar
{
    struct MAGNETAR_API TransformComponent
    {
        MT_DECLARE_CLASS_NAME(TransformComponent)

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        TransformComponent(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
            : position(position), rotation(rotation), scale(scale) {}
    };

    struct MAGNETAR_API MeshRendererComponent
    {
        MT_DECLARE_CLASS_NAME(MeshRendererComponent)

        AssetHandle mesh;
        AssetHandle material;

        MeshRendererComponent(AssetHandle mesh, AssetHandle material)
            : mesh(mesh), material(material) {}
    };

    struct MAGNETAR_API SpriteRendererComponent
    {
        MT_DECLARE_CLASS_NAME(SpriteRendererComponent)
        
        glm::vec2 size;
        glm::vec4 color;

        SpriteRendererComponent(const glm::vec2& size, const glm::vec4& color)
            : size(size), color(color) {}
    };

    struct MAGNETAR_API Camera2DComponent
    {
        MT_DECLARE_CLASS_NAME(Camera2DComponent)
        
        glm::vec2 size;
        float near;
        float far;
        bool is_primary;

        Camera2DComponent(const glm::vec2& size, float near, float far, bool is_primary = false)
            : size(size), near(near), far(far), is_primary(is_primary) {}
    };
}