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

    auto shader = AssetManager::get<Shader>(shader_handle);

    auto material = create_reference<Material>(shader);

    for(const auto& pair: config["textures"])
    {
        auto texture_name = pair.first.as<std::string>();
        auto texture_handle = pair.second.as<AssetHandle>();
        material->set_texture("u_" + texture_name, AssetManager::get<Texture2D>(texture_handle));
    }

    return std::static_pointer_cast<Asset>(material);
}