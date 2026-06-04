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
    MAGNETAR_API std::string trim(const std::string& str);
    MAGNETAR_API std::string line(const std::string& str, int line);
    MAGNETAR_API std::string substitute(const std::string& str, const std::string& from, const std::string& to);
}