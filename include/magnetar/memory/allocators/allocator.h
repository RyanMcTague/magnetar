#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    class MAGNETAR_API Allocator
    {
    public:
        virtual ~Allocator() = default;

        virtual void *allocate(size_t size, size_t alignment) = 0;

        virtual void free(void *ptr) = 0;
    };
}