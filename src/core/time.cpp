#include <iomanip>
#include <sstream>
#include <ctime>
#include "magnetar/core/time.h"

magnetar::Timestamp::Timestamp()
    : m_time_point(std::chrono::system_clock::now()) {}

magnetar::Timestamp::Timestamp(long long milliseconds)
{
    std::chrono::system_clock::time_point tp{std::chrono::system_clock::duration{std::chrono::milliseconds(milliseconds)}};
    m_time_point = tp;
}
magnetar::Timestamp::Timestamp(const std::__1::chrono::system_clock::time_point &tp)
    : m_time_point(tp) {}

magnetar::Timestamp::Timestamp(const std::chrono::system_clock::duration &duration)
    : m_time_point(duration) {}

magnetar::Timestamp magnetar::Timestamp::operator+(long long rhs) const
{
    return Timestamp(milliseconds_since_epoch() + rhs);
}
magnetar::Timestamp magnetar::Timestamp::operator-(long long rhs) const
{
    return Timestamp(milliseconds_since_epoch() - rhs);
}
bool magnetar::Timestamp::operator==(const Timestamp &rhs) const
{
    return m_time_point == rhs.m_time_point;
}
bool magnetar::Timestamp::operator!=(const Timestamp &rhs) const
{
    return !(*this == rhs);
}
bool magnetar::Timestamp::operator<(const Timestamp &rhs) const
{
    return m_time_point < rhs.m_time_point;
}
bool magnetar::Timestamp::operator>(const Timestamp &rhs) const
{
    return m_time_point > rhs.m_time_point;
}
bool magnetar::Timestamp::operator<=(const Timestamp &rhs) const
{
    return m_time_point <= rhs.m_time_point;
}
bool magnetar::Timestamp::operator>=(const Timestamp &rhs) const
{
    return m_time_point >= rhs.m_time_point;
}

long long magnetar::Timestamp::milliseconds_since_epoch() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(m_time_point.time_since_epoch()).count();
}

std::string magnetar::Timestamp::to_string(const std::string &format) const
{
    std::time_t t = std::chrono::system_clock::to_time_t(m_time_point);
    std::tm tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, format.c_str());
    return ss.str();
}

void magnetar::Timer::reset()
{
    m_timestamp = Timestamp();
}

long long magnetar::Timer::elapsed() const
{
    return Timestamp().milliseconds_since_epoch() - m_timestamp.milliseconds_since_epoch();
}