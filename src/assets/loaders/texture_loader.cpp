#include "magnetar/assets/loaders/texture_loader.h"
#include "magnetar/utils/enum_utils.h"
#include "magnetar/utils/image_utils.h"
#include "magnetar/filesystem/native_file_system.h"
#include "magnetar/renderer/renderer.h"

magnetar::Ref<magnetar::Asset> magnetar::Texture2DLoader::load(const YAML::Node &node) const
{
    TextureSpecification spec;

    if (node["minification_filter"])
        spec.min_filter = enum_utils::cast_from_string<TextureFilter>(node["minification_filter"].as<std::string>());

    if (node["magnification_filter"])
        spec.mag_filter = enum_utils::cast_from_string<TextureFilter>(node["magnification_filter"].as<std::string>());

    if (node["wrap"])
        spec.wrap = enum_utils::cast_from_string<TextureWrap>(node["wrap"].as<std::string>());

    if (node["generate_mipmaps"])
        spec.generate_mipmaps = node["generate_mipmaps"].as<bool>();

    auto path = node["path"].as<std::string>();
    auto file = FileSystem::get<NativeFileSystem>()->open(path, FileMode::READ);
    auto file_data = file->read_all();
    auto result = image_utils::load(&file_data[0], file_data.size());
    MT_ASSERT(result.success, "could not parse image {}: {}", path, result.error);

    spec.width = result.width;
    spec.height = result.height;
    switch (result.channels)
    {
    case 3:
        spec.format = TextureFormat::RGB8;
        break;
    case 4:
        spec.format = TextureFormat::RGBA8;
        break;
    default:
        MT_ASSERT(false, "unknown texture format for channels", result.channels);
        break;
    }

    auto texture = Renderer::create_texture2D(spec, result.buffer.get());
    LOG_DEBUG(logger::tags::assets, "texture spec: min: {} mag: {} wrap: {} format: {}",
              enum_utils::lowercase_name(spec.min_filter),
              enum_utils::lowercase_name(spec.mag_filter),
              enum_utils::lowercase_name(spec.wrap),
              enum_utils::lowercase_name(spec.format));

    return std::static_pointer_cast<Asset>(texture);
}