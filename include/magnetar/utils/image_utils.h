#pragma once
#include "magnetar/core/base.h"

namespace magnetar::image_utils
{
    struct MAGNETAR_API LoadResult
    {
        bool success = false;
        std::string error;
        int width = 0;
        int height = 0;
        int channels = 0;
        Ref<uint8_t> buffer = nullptr;
    }; 

    MAGNETAR_API LoadResult load(uint8_t* data, int size, int requested_channels);
}