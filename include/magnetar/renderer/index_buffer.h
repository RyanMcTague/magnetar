#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    class MAGNETAR_API IndexBuffer
    {
    public:
        IndexBuffer() = default;
        virtual ~IndexBuffer() = default;

        IndexBuffer(const IndexBuffer &) = delete;
        IndexBuffer &operator=(const IndexBuffer &) = delete;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void update(const void *data, size_t offset, size_t count) = 0;
        virtual void copy(const void *destination, size_t offset, size_t count) const = 0;

        virtual size_t size() const = 0;
        virtual size_t count() const = 0;
        virtual bool exists() const = 0;

        operator bool() const { return exists(); }
    };
}