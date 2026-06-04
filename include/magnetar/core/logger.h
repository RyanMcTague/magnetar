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
        static constexpr const char *events = "events";
        static constexpr const char *input = "input";
        static constexpr const char *renderer = "renderer";
    }

    class Logger
    {
    public:
        static void initialize(LogLevel level);
        static void set_level(LogLevel level);
        static void add_tag(const std::string &name);
        static std::shared_ptr<spdlog::logger> get(const char* name);

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
        std::shared_ptr<spdlog::logger> logger = spdlog::default_logger();

        if(subsystem)
            logger = get(subsystem);

        switch (level)
        {
        case LogLevel::critical:
            logger->critical(std::forward<TArgs>(args)...);
            break;
        case LogLevel::err:
            logger->error(std::forward<TArgs>(args)...);
            break;
        case LogLevel::warn:
            logger->warn(std::forward<TArgs>(args)...);
            break;
        case LogLevel::info:
            logger->info(std::forward<TArgs>(args)...);
            break;
        case LogLevel::debug:
            logger->debug(std::forward<TArgs>(args)...);
            break;
        case LogLevel::trace:
            logger->trace(std::forward<TArgs>(args)...);
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