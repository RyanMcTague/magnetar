#pragma once
#include <memory>
#include <string>
#include <forward_list>
#include <exception>
#include <cstddef>
#include <spdlog/spdlog.h>
#define MAGNETAR_API
#define MAGNETAR_USE_ASSERTS
#define MAGNETAR_LOG_LEVEL spdlog::level::debug

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
    MAGNETAR_API UniqueRef<T> create_unqiue_reference(TArgs &&...args)
    {
        return std::make_unique<T>(std::forward<TArgs>(args)...);
    }

    template <typename T, typename U>
    MAGNETAR_API Ref<T> cast_reference(Ref<U> ptr)
    {
        return std::static_pointer_cast<T>(ptr);
    }

    template <typename T, typename U>
    MAGNETAR_API UniqueRef<T> cast_reference(UniqueRef<U> ptr)
    {
        return std::static_pointer_cast<T>(ptr);
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

#define MAGNETAR_INITIALIZE_LOGGER spdlog::set_level(MAGNETAR_LOG_LEVEL)
#define LOG_TRACE(...) spdlog::trace(__VA_ARGS__)
#define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_FATAL(...) spdlog::critical(__VA_ARGS__)

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