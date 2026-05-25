#pragma once
#include <memory>
#include <string>
#include <forward_list>
#include <exception>
#include <typeindex>
#include <cstddef>
#include <spdlog/spdlog.h>

#ifdef MAGNETAR_BUILD_SHARED
#define MAGNETAR_API
#elif defined(MAGNETAR_BUILD_STATIC)
#define MAGNETAR_API
#endif

#ifdef MAGNETAR_BUILD_DEBUG
#define MAGNETAR_USE_ASSERTS
#define MAGNETAR_LOG_LEVEL spdlog::level::debug
#else
#define MAGNETAR_LOG_LEVEL spdlog::level::info
#endif

namespace magnetar
{
    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T>
    using UniqueRef = std::unique_ptr<T>;

    template <typename T, typename... TArgs>
    MAGNETAR_API Ref<T> create_reference(TArgs &&...args)
    {
        return std::make_shared<T>(std::forward<TArgs>(args)...);
    }

    template <typename T, typename... TArgs>
    MAGNETAR_API UniqueRef<T> create_unique_reference(TArgs &&...args)
    {
        return std::make_unique<T>(std::forward<TArgs>(args)...);
    }

    class MAGNETAR_API Exception : public std::exception
    {
    };

    class MAGNETAR_API AssertionException : public Exception
    {
    public:
        AssertionException(const char *file, int line, const std::string &message)
        {
            m_message = fmt::format("{}:{} {}", file, line, message);
        }

        const char *what() const noexcept
        {
            return m_message.c_str();
        }

    private:
        std::string m_message;
    };
}

#define LOG(...)  Logger::log(__VA_ARGS__)

#define LOG_TRACE(tag, ...) Logger::get(tag)->trace(__VA_ARGS__)
#define LOG_DEBUG(tag, ...) Logger::get(tag)->debug(__VA_ARGS__)
#define LOG_INFO(tag, ...) Logger::get(tag)->info(__VA_ARGS__)
#define LOG_WARN(tag, ...) Logger::get(tag)->warn(__VA_ARGS__)
#define LOG_ERROR(tag, ...) Logger::get(tag)->error(__VA_ARGS__)
#define LOG_FATAL(tag, ...) Logger::get(tag)->fatal(__VA_ARGS__)

#ifdef MAGNETAR_USE_ASSERTS
#define MAGNETAR_ASSERT(condition, ...)                                                       \
    do                                                                                        \
    {                                                                                         \
        if (!(condition))                                                                     \
            throw magnetar::AssertionException(__FILE__, __LINE__, fmt::format(__VA_ARGS__)); \
    } while (false)

#else
#define MAGNETAR_ASSERT(condition, ...)
#endif

#include "magnetar/core/logger.h"