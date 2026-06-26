#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "magnetar/assets/loaders/mesh_loader.h"
#include "magnetar/filesystem/native_file_system.h"

magnetar::Ref<magnetar::Asset> magnetar::MeshLoader::load(const YAML::Node &node) const
{
    auto path = node["path"].as<std::string>();
    auto file = FileSystem::get<NativeFileSystem>()->open(path, FileMode::READ);
    auto raw = file->read_all();

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFileFromMemory(&raw[0], raw.size(), aiProcess_Triangulate | aiProcess_FlipUVs);
    bool failure = !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode;
    MT_ASSERT(!failure, "could not import {}", path);
    auto directory = path.substr(0, path.find_last_of('/'));

    auto root = scene->mRootNode;
    auto child = root->mChildren[0];
    aiMesh *amesh = scene->mMeshes[child->mMeshes[0]];
    auto mesh = process_mesh(amesh, scene);
    return std::static_pointer_cast<Asset>(mesh);
}

// void magnetar::MeshLoader::process_node(aiNode *node, const aiScene *scene) const
// {
//     for (uint32_t i = 0; i < node->mNumMeshes; i++)
//     {
//         aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
//         auto m = process_mesh(mesh, scene);
//         // meshes.push_back(process_mesh(mesh, scene));
//     }

//     for (unsigned int i = 0; i < node->mNumChildren; i++)
//     {
//         process_node(node->mChildren[i], scene);
//     }
// }

magnetar::Ref<magnetar::Mesh> magnetar::MeshLoader::process_mesh(aiMesh *mesh, const aiScene *) const
{
    std::vector<Mesh::Vertex> vertices;
    std::vector<uint32_t> indices;

    for (uint32_t i = 0; i < mesh->mNumVertices; i++)
    {
        Mesh::Vertex vertex;
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        if (mesh->mTextureCoords[0])
        {
            vertex.texcoord.x = mesh->mTextureCoords[0][i].x;
            vertex.texcoord.y = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            vertex.texcoord = glm::vec2(0.0f, 0.0f);
        }

        vertex.color.x = 1.0f;
        vertex.color.y = 1.0f;
        vertex.color.z = 1.0f;
        vertex.color.w = 1.0f;

        vertices.push_back(vertex);
    }

    for (uint32_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (uint32_t j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return create_reference<Mesh>(vertices, indices);
}