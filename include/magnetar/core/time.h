#pragma once
#include <chrono>
#include "magnetar/core/base.h"
namespace magnetar
{
    class Timestamp
    {
    public:
        Timestamp();
        Timestamp(long long milliseconds);
        Timestamp(const std::chrono::system_clock::duration& duration);
        Timestamp(const std::__1::chrono::system_clock::time_point& tp);
        Timestamp operator+(long long rhs) const;
        Timestamp operator-(long long rhs) const;

        bool operator==(const Timestamp &rhs) const;
        bool operator!=(const Timestamp &rhs) const;

        bool operator<(const Timestamp &rhs) const;
        bool operator>(const Timestamp &rhs) const;

        bool operator<=(const Timestamp &rhs) const;
        bool operator>=(const Timestamp &rhs) const;
        
        long long milliseconds_since_epoch() const;

        std::string to_string(const std::string& format = "%Y-%m-%d %H:%M:%S") const;
    private:
        std::chrono::system_clock::time_point m_time_point;
    };

    class Timer
    {
    public:
        void reset();

        long long elapsed() const;
    private:
        Timestamp m_timestamp;
    };
}
