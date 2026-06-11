#include "magnetar/asset/asset_manager.h"

std::unordered_map<magnetar::AssetHandle, magnetar::Ref<magnetar::Asset>> magnetar::AssetManager::s_asset_cache;
magnetar::AssetRegistry magnetar::AssetManager::s_registry;
void magnetar::AssetManager::initialize(const std::string& config)
{
    s_registry.initialize(config);
}

void magnetar::AssetManager::shutdown()
{
    s_asset_cache.clear();
}

void magnetar::AssetManager::unload(AssetHandle handle)
{
}