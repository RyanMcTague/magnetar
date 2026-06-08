#include "magnetar/assets/asset_manager.h"
#include "magnetar/renderer/renderer.h"
#include "magnetar/utils/image_utils.h"
#include "magnetar/filesystem/native_file_system.h"


magnetar::Ref<magnetar::AssetRegistry> magnetar::AssetManager::s_registry;
std::unordered_map<magnetar::AssetHandle, magnetar::Ref<magnetar::Asset>> magnetar::AssetManager::s_loaded_assets;

std::unordered_map<std::string, magnetar::Ref<magnetar::ResourceLoader>> magnetar::AssetManager::s_loaders;


magnetar::AssetRegistry::AssetRegistry(const char *raw_config)
{
    auto config = YAML::Load(raw_config);
    MT_ASSERT(config.IsSequence(), "asset metadata is not an yaml array");

    for (const auto &node : config)
    {
        auto guid = node["guid"].as<AssetHandle>();
        auto type = node["type"].as<std::string>();
        auto path = node["path"].as<std::string>();
        m_handles.emplace(path, guid);
        m_metadata.emplace(guid, node);
        LOG_TRACE(logger::tags::assets, "imported metadata for asset {}#{:x} {}", type, guid, path);
    }
}

const YAML::Node& magnetar::AssetRegistry::get(AssetHandle handle) const
{
    auto it = m_metadata.find(handle);
    MT_ASSERT(it != m_metadata.end(), "cannot find metadata for asset {:x}", handle);
    return it->second;
}

magnetar::AssetHandle magnetar::AssetRegistry::get_handle_for_path(const std::string& path) const
{
    auto it = m_handles.find(path);
    MT_ASSERT(it != m_handles.end(), "handle fot asset {} does not exist", path);
    return it->second;
}

void magnetar::AssetManager::initialize(const char *raw_config)
{
    s_registry = create_reference<AssetRegistry>(raw_config);
}

void magnetar::AssetManager::shutdown()
{
    s_loaded_assets.clear();
    s_registry = nullptr;
}


magnetar::Ref<magnetar::ResourceLoader> magnetar::AssetManager::get_loader_from_type_index(const std::type_index& idx)
{
    Ref<ResourceLoader> loader = nullptr;

    for(auto& pair: s_loaders)
    {
        if(pair.second->type_index() == idx)
        {
            loader = pair.second;
            break;
        }
    }

    MT_ASSERT(loader != nullptr, "expected loader for type {} to exist", idx.name());

    return loader;
}