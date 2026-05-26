#pragma once
#include <cstdint>
#include <string>
#include "magnetar/core/base.h"

namespace magnetar::string_utils
{
    MAGNETAR_API std::vector<std::string> split(const std::string& str, char character);
    MAGNETAR_API std::string lowercase(const std::string& str);
    MAGNETAR_API std::string uppercase(const std::string& str);
    MAGNETAR_API std::string replace(const std::string& str, char from, char to);
}