#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    class UUID
    {
    public:
        UUID();

        explicit UUID(uint64_t val);

        uint64_t value() const;
        std::string to_hex() const;
        static UUID from_hex(const std::string &hex_str);

        bool operator<(const UUID &other) const { return m_value < other.m_value; }
        bool operator==(const UUID &other) const { return m_value == other.m_value; }

    private:
        uint64_t m_value;
    };
}