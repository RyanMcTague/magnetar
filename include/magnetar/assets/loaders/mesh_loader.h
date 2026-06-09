#pragma once
#include <assimp/scene.h>
#include "magnetar/core/base.h"
#include "magnetar/assets/resouce_loader.h"
#include "magnetar/renderer/mesh.h"

namespace magnetar
{
    class MAGNETAR_API MeshLoader : public ResourceLoader
    {
    public:
        const std::string resource_name() const override { return m_resource_name; }

        Ref<Asset> load(const YAML::Node &node) const override;

        std::type_index type_index() const override { return typeid(Mesh); }

    private:
        std::string m_resource_name = "mesh";

        // void process_node(aiNode* node, const aiScene* scene) const;

        Ref<Mesh> process_mesh(aiMesh* mesh, const aiScene* scene) const;
    };
}