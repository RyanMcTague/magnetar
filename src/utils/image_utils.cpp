#define STB_IMAGE_IMPLEMENTATION
#include "magnetar/utils/image_utils.h"
#include "magnetar/vendor/stb_image.h"
MAGNETAR_API magnetar::image_utils::LoadResult magnetar::image_utils::load(uint8_t *data, int size, int requested_channels)
{
    LoadResult result;
    int width, height, channels;
    uint8_t *buffer = stbi_load_from_memory(data, size, &width, &height, &channels, requested_channels);
    if (!buffer)
    {
        result.success = false;
        result.error = stbi_failure_reason();
        return result;
    }

    result.success = true;
    result.height = height;
    result.width = width;
    result.channels = channels;
    result.buffer = std::shared_ptr<uint8_t>(buffer, stbi_image_free);

    return result;
}