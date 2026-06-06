#include "magnetar/assets/asset_manager.h"
#include "magnetar/renderer/renderer.h"
#include "magnetar/utils/image_utils.h"
#include "magnetar/filesystem/native_file_system.h"

std::unordered_map<std::string, magnetar::AssetHandle> magnetar::AssetManager::s_handles;
std::unordered_map<magnetar::AssetHandle, magnetar::Ref<magnetar::Asset>> magnetar::AssetManager::s_loaded_assets;
std::unordered_map<std::type_index, magnetar::AssetManager::Loader> magnetar::AssetManager::s_loaders;

void magnetar::AssetManager::initialize()
{

    s_handles = {
        {"./sample/GL_Sample.glsl", 1000},
        {"./sample/wall.jpg", 1001},
    };

    auto fs = FileSystem::get<NativeFileSystem>();

    Loader texture2D_loader = [fs](const std::string &path)
    {
        auto file_data = fs->open(path, FileMode::READ)->read_all();
        auto result = image_utils::load(&file_data[0], file_data.size(), 3);
        MT_ASSERT(result.success, "{}", result.error);

        TextureSpecification spec;
        spec.width = result.width;
        spec.height = result.height;
        spec.format = TextureFormat::RGB8;
        spec.generate_mipmaps = true;
        auto texture = Renderer::create_texture2D(spec, result.buffer.get());
        return texture;
    };

    Loader shader_loader = [fs](const std::string &path)
    {
        auto file = fs->open(path, FileMode::READ);
        auto source = file->to_string();
        auto shader = Renderer::create_shader(file->uri(), source);
        return shader;
    };

    register_loader<Texture2D>(texture2D_loader);
    register_loader<Shader>(shader_loader);
}

void magnetar::AssetManager::shutdown()
{
    s_loaded_assets.clear();
    s_handles.clear();
}
