#include "magnetar/assets/loaders/material_loader.h"
#include "magnetar/assets/asset_manager.h"
#include "magnetar/filesystem/native_file_system.h"
magnetar::Ref<magnetar::Asset> magnetar::MaterialLoader::load(const YAML::Node &node) const
{
    auto path = node["path"].as<std::string>();
    auto file = FileSystem::get<NativeFileSystem>()->open(path, FileMode::READ);
    auto raw = file->to_string();

    auto config = YAML::Load(raw);

    auto shader_handle = config["shader"].as<AssetHandle>();

    auto shader = AssetManager::load<Shader>(shader_handle);
    MT_ASSERT(shader != nullptr, "shader {} not found in material {}", shader_handle, path);

    auto material = create_reference<Material>(shader);

    if (config["textures"])
    {
        for (const auto &pair : config["textures"])
        {
            auto texture_name = pair.first.as<std::string>();
            auto texture_handle = pair.second.as<AssetHandle>();
            auto texture = AssetManager::load<Texture2D>(texture_handle);
            MT_ASSERT(texture != nullptr, "texture {} not found in material {}", texture_handle, path);
            material->set_texture("u_" + texture_name, texture);
        }
    }

    if (config["color"])
    {
        auto color = glm::vec4(0.0f);
        color.x = config["color"]["red"].as<float>();
        color.y = config["color"]["green"].as<float>();
        color.z = config["color"]["blue"].as<float>();
        color.w = config["color"]["alpha"].as<float>();
        material->set_color("u_color", color);
    }

    return std::static_pointer_cast<Asset>(material);
}