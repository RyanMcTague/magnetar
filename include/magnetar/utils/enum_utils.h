#pragma once
#include <magic_enum/magic_enum.hpp>
#include "magnetar/core/base.h"
#include "magnetar/utils/string_utils.h"
namespace magnetar::enum_utils
{
    template <typename T>
    MAGNETAR_API std::string lowercase_name(T value)
    {
        return string_utils::lowercase(std::string(magic_enum::enum_name(value)));
    }

    template <typename T>
    MAGNETAR_API T cast_from_string(const std::string &str)
    {
        auto result = magic_enum::enum_cast<T>(str, magic_enum::case_insensitive);
        MT_ASSERT(result.has_value(), "unknown {} type {}", magic_enum::enum_type_name<T>(), str);
        return result.value();
    }
}
