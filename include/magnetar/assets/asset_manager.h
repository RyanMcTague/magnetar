#pragma once
#include <unordered_map>
#include <functional>
#include "magnetar/core/base.h"
#include "magnetar/assets/asset.h"
#include "magnetar/assets/asset_handle.h"
#include "magnetar/assets/resouce_loader.h"
#include "magnetar/events/event_system.h"

namespace magnetar
{

    struct MAGNETAR_API AssetLoadedEvent
    {
        MT_DECLARE_CLASS_NAME(AssetLoadedEvent)
        std::string path;
        std::string type;
        AssetHandle guid;
    };

    class MAGNETAR_API AssetRegistry
    {
    public:
        AssetRegistry(const char *raw_config);

        const YAML::Node &get(AssetHandle handle) const;

        AssetHandle get_handle_for_path(const std::string &path) const;

    private:
        std::unordered_map<std::string, AssetHandle> m_handles;
        std::unordered_map<AssetHandle, YAML::Node> m_metadata;
    };

    class MAGNETAR_API AssetManager
    {
    public:
        static void initialize(const char *raw_config);
        static void shutdown();

        template <typename T>
        static AssetHandle load(const std::string &path);

        template <typename T>
        static Ref<T> get(AssetHandle handle);

        template <typename T>
        static void register_loader();

    private:
        AssetManager() = default;
        static Ref<AssetRegistry> s_registry;
        static std::unordered_map<AssetHandle, Ref<Asset>> s_loaded_assets;
        static std::unordered_map<std::string, Ref<ResourceLoader>> s_loaders;

        static Ref<ResourceLoader> get_loader_from_type_index(const std::type_index& idx) ;
    };
}

template <typename T>
void magnetar::AssetManager::register_loader()
{
    Ref<ResourceLoader> loader = std::static_pointer_cast<ResourceLoader>(create_reference<T>());
    s_loaders.emplace(loader->resource_name(), loader);
}

template <typename T>
magnetar::AssetHandle magnetar::AssetManager::load(const std::string &path)
{
    auto handle = s_registry->get_handle_for_path(path);
    auto asset_it = s_loaded_assets.find(handle);
    if(asset_it != s_loaded_assets.end())
    {
        LOG_TRACE(logger::tags::assets, "asset {:} already loaded", path);
        return handle;
    }

    auto loader = get_loader_from_type_index(typeid(T));

    auto asset = loader->load(s_registry->get(handle));
    s_loaded_assets.emplace(handle, asset);
    LOG_INFO(logger::tags::assets, "imported asset {}", path);
    EventSystem::emit(AssetLoadedEvent { path, loader->resource_name(), handle });
    return handle;
}

template <typename T>
magnetar::Ref<T> magnetar::AssetManager::get(AssetHandle handle)
{
    auto it = s_loaded_assets.find(handle);
    if (it == s_loaded_assets.end())
    {
        LOG_WARN(logger::tags::assets, "asset {:x} is not loaded", handle);
        return nullptr;
    }

    return std::static_pointer_cast<T>(it->second);
}
