#include <unordered_map>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "magnetar/core/logger.h"

magnetar::LogLevel magnetar::Logger::s_level = magnetar::LogLevel::debug;

void magnetar::Logger::initialize(LogLevel level)
{
    static std::vector<const char*> tags = {
        logger::tags::application,
        logger::tags::memory
    };

    s_level = level;
    spdlog::default_logger()->set_level(level);

    for(auto& tag: tags)
    {
        auto logger = spdlog::stdout_color_mt(tag);
        logger->set_level(level);
    }
}

void magnetar::Logger::add_tag(const std::string& name)
{
    auto logger = spdlog::stdout_color_mt(name);
    logger->set_level(s_level);
}


std::shared_ptr<spdlog::logger> magnetar::Logger::get(const std::string& name)
{
    if(!name.length())
        return spdlog::default_logger();
    return spdlog::get(name);
}