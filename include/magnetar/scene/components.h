#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "magnetar/core/base.h"
#include "magnetar/assets/asset_handle.h"

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
}