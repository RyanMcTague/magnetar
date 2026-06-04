#pragma once
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/asset/asset.h"
#include "magnetar/asset/asset_registry.h"

namespace magnetar
{
    class MAGNETAR_API AssetManager
    {
    public:
        static void initialize(const std::string &config);
        static void shutdown();

        template <typename T>
        static Ref<T> load(AssetHandle handle);

        static void unload(AssetHandle handle);

    private:
        static std::unordered_map<AssetHandle, Ref<Asset>> s_asset_cache;
        static AssetRegistry s_registry;
    };

    template <typename T>
    Ref<T> AssetManager::load(AssetHandle handle)
    {
        auto it = s_asset_cache.find(handle);
        if (it != s_asset_cache.end())
            return std::static_pointer_cast<T>(it->second);

        if (!s_registry.exists(handle))
        {
            LOG_WARN(logger::tags::assets, "could not find asset {:x}", handle);
            return nullptr;
        }

        auto metadata = s_registry.get_metadata(handle);
    }
}