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

        static Ref<IndexBuffer> create(size_t count, uint32_t *data = nullptr);

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void update(uint32_t *data, size_t offset, size_t count) = 0;
        virtual void copy(uint32_t *destination, size_t offset, size_t count) const = 0;

        virtual size_t size() const = 0;
        virtual size_t count() const = 0;
        virtual bool exists() const = 0;

        operator bool() const { return exists(); }
    };
}