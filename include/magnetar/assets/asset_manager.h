#pragma once
#include <unordered_map>
#include <functional>
#include "magnetar/core/base.h"
#include "magnetar/assets/asset.h"

namespace magnetar
{
    using AssetHandle = uint32_t;

    class MAGNETAR_API AssetManager
    {
    public:
        using Loader = std::function<Ref<Asset>(const std::string &path)>;
        static void initialize();
        static void shutdown();

        template <typename T>
        static AssetHandle load(const std::string &path);

        template <typename T>
        static Ref<T> get(AssetHandle handle);

    private:
        AssetManager() = default;
        static std::unordered_map<std::string, AssetHandle> s_handles;
        static std::unordered_map<AssetHandle, Ref<Asset>> s_loaded_assets;
        static std::unordered_map<std::type_index, Loader> s_loaders;

        template <typename T>
        static void register_loader(Loader loader);
    };
}

template <typename T>
magnetar::AssetHandle magnetar::AssetManager::load(const std::string &path)
{
    auto handle_it = s_handles.find(path);
    MT_ASSERT(handle_it != s_handles.end(), "handle not found for {}", path);

    auto handle = handle_it->second;
    auto asset_it = s_loaded_assets.find(handle);
    if (asset_it != s_loaded_assets.end())
        return handle;

    auto loader_it = s_loaders.find(typeid(T));
    MT_ASSERT(loader_it != s_loaders.end(), "loader not found for asset");
    auto loader = loader_it->second;
    auto asset = loader(path);

    LOG_INFO(logger::tags::assets, "loaded asset {}", path);

    s_loaded_assets.emplace(handle, std::move(asset));
    return handle;
}

template <typename T>
magnetar::Ref<T> magnetar::AssetManager::get(AssetHandle handle)
{
    auto it = s_loaded_assets.find(handle);
    MT_ASSERT(it != s_loaded_assets.end(), "asset {:x} is not loaded into asset manager", handle);
    return std::static_pointer_cast<T>(it->second);
}

template <typename T>
void magnetar::AssetManager::register_loader(Loader loader)
{
    s_loaders.emplace(typeid(T), loader);
}