#include <random>
#include <iomanip>
#include <sstream>
#include "magnetar/core/uuid.h"

magnetar::UUID::UUID()
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> distrib;
    m_value = distrib(gen);
}

magnetar::UUID::UUID(uint64_t val)
    : m_value(val) {}

uint64_t magnetar::UUID::value() const
{
    return m_value;
}

std::string magnetar::UUID::to_hex() const
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(16) << std::hex << m_value;
    return ss.str();
}

magnetar::UUID magnetar::UUID::from_hex(const std::string &hex_str)
{
    if (hex_str.length() != 16)
    {
        throw std::invalid_argument("Hex string must be exactly 16 characters long.");
    }
    uint64_t val = std::stoull(hex_str, nullptr, 16);
    return UUID(val);
}
