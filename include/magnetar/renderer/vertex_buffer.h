#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    class MAGNETAR_API VertexBuffer
    {
    public:
        VertexBuffer() = default;
        virtual ~VertexBuffer() = default;

        VertexBuffer(const VertexBuffer &) = delete;
        VertexBuffer &operator=(const VertexBuffer &) = delete;

        static Ref<VertexBuffer> create(size_t size, const void *data = nullptr);

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void update(const void *data, size_t offset, size_t size) = 0;
        virtual void copy(const void *destination, size_t offset, size_t size) const = 0;

        virtual size_t size() const = 0;
        virtual bool exists() const = 0;

        operator bool() const { return exists(); }
    };
}