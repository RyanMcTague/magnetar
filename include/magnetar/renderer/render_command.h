#pragma once
#include <glm/glm.hpp>
#include "magnetar/core/base.h"
#include "magnetar/renderer/mesh.h"
#include "magnetar/renderer/material.h"

namespace magnetar
{
    struct RenderCommand
    {
        Ref<Mesh> mesh;
        Ref<Material> material;
        glm::mat4 transform;

        RenderCommand(const Ref<Mesh>& mesh, const Ref<Material>& material, const glm::mat4& transform)
            : mesh(std::move(mesh)), material(std::move(material)), transform(transform) {}
    };
}