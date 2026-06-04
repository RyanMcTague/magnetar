#pragma once
#include "magnetar/core/base.h"
#include "magnetar/importer/asset_importer.h"
#include "magnetar/renderer/enums.h"

namespace magnetar
{
    struct TextureImportData
    {
        TextureFormat format;
        int width;
        int height;
        Ref<uint8_t> buffer;
    };

    class MAGNETAR_API TextureImporter: public AssetImporter<TextureImportData>
    {
    public:
        ImportResult<TextureImportData> import(const std::string &path) override;
    };
}