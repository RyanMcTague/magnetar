#pragma once
#include <string>
#include <forward_list>
#include <memory>
#include <spdlog/spdlog.h>
namespace magnetar
{
    using LogLevel = spdlog::level::level_enum;

    namespace logger::tags
    {
        static constexpr const char *application = "application";
    }

    class Logger
    {
    public:
        static void initialize(LogLevel level);
        static void add_tag(const std::string &name);
        static std::shared_ptr<spdlog::logger> get(const std::string &name);

        template <typename... TArgs>
        static void log(const char *subsystem, LogLevel level, TArgs &&...args);

        template <typename... TArgs>
        static void log(LogLevel level, TArgs &&...args);

    private:
        static LogLevel s_level;
    };

    template <typename... TArgs>
    void Logger::log(const char *subsystem, LogLevel level, TArgs &&...args)
    {
        switch (level)
        {
        case LogLevel::critical:
            get(subsystem)->critical(std::forward<TArgs>(args)...);
            break;
        case LogLevel::err:
            get(subsystem)->error(std::forward<TArgs>(args)...);
            break;
        case LogLevel::warn:
            get(subsystem)->warn(std::forward<TArgs>(args)...);
            break;
        case LogLevel::info:
            get(subsystem)->info(std::forward<TArgs>(args)...);
            break;
        case LogLevel::debug:
            get(subsystem)->debug(std::forward<TArgs>(args)...);
            break;
        case LogLevel::trace:
            get(subsystem)->trace(std::forward<TArgs>(args)...);
            break;
        default:
            break;
        }
    }

    template <typename... TArgs>
    void  Logger::log(LogLevel level, TArgs &&...args)
    {
        log(nullptr, level, std::forward<TArgs>(args)...);
    }
}