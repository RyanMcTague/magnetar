#include "magnetar/assets/loaders/font_loader.h"
#include "magnetar/filesystem/native_file_system.h"
#include "magnetar/renderer/renderer.h"

magnetar::Ref<magnetar::Asset> magnetar::FontLoader::load(const YAML::Node &node) const
{
    auto path = node["path"].as<std::string>();
    auto file = FileSystem::get<NativeFileSystem>()->open(path, FileMode::READ);
    auto bytes = file->read_all();
    auto font = create_reference<Font>(&bytes[0], bytes.size());
    return font;
}