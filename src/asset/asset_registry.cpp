#include "magnetar/asset/asset_registry.h"

void magnetar::AssetRegistry::initialize(const std::string &raw_config)
{
    YAML::Node config = YAML::Load(raw_config);
    for (auto const &element : config)
    {
        std::string name = element.first.as<std::string>();
        for (const auto &item : element.second)
        {
            AssetType type = asset_type_from_string(name);
            switch (type)
            {
            case AssetType::TEXTURE:
            {
                TextureAssetMetadata metadata;
                metadata.type = AssetType::TEXTURE;
                metadata.handle = item["guid"].as<AssetHandle>();
                metadata.path = item["path"].as<std::string>();
                metadata.generate_mipmaps = item["generate_mipmaps"].as<bool>();
                metadata.width = item["width"].as<int>();
                metadata.height = item["height"].as<int>();
                auto format = item["format"].as<std::string>();
                if (format == "rgb")
                    metadata.format = TextureFormat::RGB8;
                else if (format == "rgba")
                    metadata.format = TextureFormat::RGBA8;
                else
                {
                    LOG_WARN(logger::tags::assets, "unknown texture asset format {}", format);
                    metadata.format = TextureFormat::NONE;
                }
                m_metadata.emplace(metadata.handle, metadata);
                LOG_TRACE(logger::tags::assets, "registered texture asset metadata {:x}", metadata.handle);
            }
            break;
            case AssetType::SHADER:
            {
                ShaderAssetMetadata metadata;
                metadata.type = AssetType::TEXTURE;
                metadata.handle = item["guid"].as<AssetHandle>();
                metadata.path = item["path"].as<std::string>();
                m_metadata.emplace(metadata.handle, metadata);
                LOG_TRACE(logger::tags::assets, "registered texture shader metadata {:x}", metadata.handle);
            }
            break;
            default:
                break;
            }
        }
    }
}

bool magnetar::AssetRegistry::exists(AssetHandle handle) const
{
    auto it = m_metadata.find(handle);
    return it != m_metadata.end();
}

const magnetar::AssetMetadata &magnetar::AssetRegistry::get_metadata(AssetHandle handle) const
{
    auto it = m_metadata.find(handle);
    MT_ASSERT(it != m_metadata.end(), "could not find asset {:x}", handle);
    return it->second;
}

magnetar::AssetType magnetar::AssetRegistry::asset_type_from_string(const std::string &string)
{
    AssetType type = AssetType::UNKNOWN;
    if (string == "textures")
        type = AssetType::TEXTURE;
    else if (string == "shaders")
        type = AssetType::SHADER;
    return type;
}
