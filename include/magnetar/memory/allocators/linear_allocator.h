#pragma once
#include "magnetar/core/base.h"
#include "magnetar/memory/allocators/allocator.h"

namespace magnetar
{
    class MAGNETAR_API LinearAllocator : public Allocator
    {
    public:
        explicit LinearAllocator(size_t size);
        ~LinearAllocator();

        void *allocate(size_t size, size_t alignment = alignof(std::max_align_t)) override;
        void reset();
        void free(void *ptr) override;

    private:
        std::byte *m_memory;
        size_t m_size;
        size_t m_offset;

        uintptr_t align_forward(uintptr_t ptr, size_t alignment);
    };
}