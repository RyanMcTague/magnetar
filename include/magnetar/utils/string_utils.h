#pragma once
#include <cstdint>
#include <string>
#include "magnetar/core/base.h"

namespace magnetar::string_utils
{
    MAGNETAR_API std::vector<std::string> split(const std::string& str, char character);
}