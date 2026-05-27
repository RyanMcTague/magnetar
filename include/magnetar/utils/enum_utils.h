#pragma once
#include <magic_enum/magic_enum.hpp>
#include "magnetar/core/base.h"
#include "magnetar/utils/string_utils.h"
namespace magnetar::enum_utils
{
    template<typename T>
    MAGNETAR_API std::string lowercase_name(T value)
    {
        return string_utils::lowercase(std::string(magic_enum::enum_name(value)));
    }
}