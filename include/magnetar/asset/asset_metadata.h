#pragma once
#include "magnetar/core/base.h"
#include "magnetar/asset/enums.h"
#include "magnetar/asset/asset_handle.h"
#include "magnetar/renderer/enums.h"

namespace magnetar
{
    struct MAGNETAR_API AssetMetadata
    {
        AssetHandle handle;
        std::string path;
        AssetType type;
    };

    struct MAGNETAR_API ShaderAssetMetadata : public AssetMetadata
    {
    };

    struct MAGNETAR_API TextureAssetMetadata : public AssetMetadata
    {
        bool generate_mipmaps = false;
        TextureFormat format = TextureFormat::NONE;
        int width = 1;
        int height = 1;
    };
};