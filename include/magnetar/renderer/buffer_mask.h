#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    class MAGNETAR_API BufferMask
    {
    public:
        enum : uint32_t
        {
            COLOR_BUFFER = (1 << 0),
            DEPTH_BUFFER = (1 << 1)
        };

        BufferMask()
            : m_value(0) {}

        BufferMask& set(uint32_t buffer)
        {
            m_value |= (buffer);
            return *this;
        }

        bool test(uint32_t buffer) const
        {
            return m_value & buffer;
        }

        uint32_t value() const { return m_value; }

    private:
        uint32_t m_value;
    };
}