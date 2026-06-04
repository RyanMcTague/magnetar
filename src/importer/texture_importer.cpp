#define STB_IMAGE_IMPLEMENTATION
#include "magnetar/importer/texture_importer.h"
#include "magnetar/vendor/stb_image.h"
#include "magnetar/filesystem/file_system.h"
#include "magnetar/filesystem/native_file_system.h"

magnetar::ImportResult<magnetar::TextureImportData> magnetar::TextureImporter::import(const std::string &path)
{
    ImportResult<TextureImportData> result;

    auto file = FileSystem::get<NativeFileSystem>()->open(path, FileMode::READ);
    auto data = file->read_all();
    int width, height, channels;
    uint8_t *buffer = stbi_load_from_memory(&data[0], data.size(), &width, &height, &channels, 3);
    if (!buffer)
    {
        result.status = ImportStatus::FAILURE;
        result.message = stbi_failure_reason();
        return result;
    }

    result.data.width = width;
    result.data.height = height;
    result.data.format = channels == 4 ? TextureFormat::RGBA8 : TextureFormat::RGB8;
    result.data.buffer = std::shared_ptr<uint8_t>(buffer, [](uint8_t *ptr)
                                                  { stbi_image_free(ptr); });
    result.status = ImportStatus::SUCCESS;
    return result;
}