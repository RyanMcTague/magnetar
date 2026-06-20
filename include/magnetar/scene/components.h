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

        TransformComponent(const glm::vec3 &position = glm::vec3(0.0f),
                           const glm::vec3 &rotation = glm::vec3(0.0f), 
                           const glm::vec3 &scale = glm::vec3(0.0f))
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

        SpriteRendererComponent(const glm::vec2 &size = glm::vec2(0.0f), const glm::vec4 &color = glm::vec4(0.0f))
            : size(size), color(color) {}
    };

    struct MAGNETAR_API Camera2DComponent
    {
        MT_DECLARE_CLASS_NAME(Camera2DComponent)

        glm::vec2 size;
        float near;
        float far;
        bool is_primary;

        Camera2DComponent(const glm::vec2 &size, float near, float far, bool is_primary = false)
            : size(size), near(near), far(far), is_primary(is_primary) {}
    };

    struct MAGNETAR_API RigidBody2DComponent
    {
        MT_DECLARE_CLASS_NAME(RigidBody2DComponent)
        glm::vec2 velocity;
        float angular_velocity;

        RigidBody2DComponent(const glm::vec2 &velocity = glm::vec2(0.0f), float angular_velocity = 0.0f)
            : velocity(velocity), angular_velocity(angular_velocity) {}
    };

    struct MAGNETAR_API ScriptComponent
    {
        MT_DECLARE_CLASS_NAME(ScriptComponent)
        std::string script_class_name;
        bool skip_add;

        ScriptComponent(const std::string &class_name, bool skip_add = false)
            : script_class_name(class_name), skip_add(skip_add) {}
    };

    struct MAGNETAR_API TagComponent
    {
        MT_DECLARE_CLASS_NAME(TagComponent)
        std::string tag;

        TagComponent(const std::string &tag = "")
            : tag(tag) {}
    };
}