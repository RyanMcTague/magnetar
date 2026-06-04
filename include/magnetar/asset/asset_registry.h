#pragma once
#include <unordered_map>
#include <yaml-cpp/yaml.h>
#include "magnetar/core/base.h"
#include "magnetar/asset/asset_metadata.h"
#include "magnetar/asset/asset_handle.h"
namespace magnetar
{
    class MAGNETAR_API AssetRegistry
    {
    public:
        void initialize(const std::string& raw_config);

        bool exists(AssetHandle handle) const;
        const AssetMetadata& get_metadata(AssetHandle handle) const;
    private:
        std::unordered_map<AssetHandle, AssetMetadata> m_metadata; 
        AssetType asset_type_from_string(const std::string& string);
    };
}