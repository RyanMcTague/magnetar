#include <unordered_map>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "magnetar/core/logger.h"

magnetar::LogLevel magnetar::Logger::s_level = magnetar::LogLevel::debug;

namespace magnetar
{
    static std::vector<const char *> s_tag_list = {
        logger::tags::application,
        logger::tags::events,
        logger::tags::input,
        logger::tags::renderer,
        logger::tags::assets,
    };
}
void magnetar::Logger::initialize(LogLevel level)
{
    s_level = level;
    spdlog::default_logger()->set_level(level);

    for (auto &tag : s_tag_list)
    {
        auto logger = spdlog::stdout_color_mt(tag);
        logger->set_level(level);
    }
}

void magnetar::Logger::set_level(LogLevel level)
{
    spdlog::default_logger()->set_level(level);
    for (auto &tag : s_tag_list)
        spdlog::get(tag)->set_level(level);
}
void magnetar::Logger::add_tag(const std::string &name)
{
    auto logger = spdlog::stdout_color_mt(name);
    logger->set_level(s_level);
}

std::shared_ptr<spdlog::logger> magnetar::Logger::get(const char *name)
{
    if (!name)
        return spdlog::default_logger();
    return spdlog::get(name);
}