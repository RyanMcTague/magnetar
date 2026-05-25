#include "magnetar/memory/allocators/linear_allocator.h"

magnetar::LinearAllocator::LinearAllocator(size_t size)
    : m_memory(nullptr), m_size(size), m_offset(0)
{
    m_memory = static_cast<std::byte *>(::operator new(size));
    m_offset = 0;
}

magnetar::LinearAllocator::~LinearAllocator()
{
    ::operator delete(m_memory);
}

void *magnetar::LinearAllocator::allocate(size_t size, size_t alignment)
{
    uintptr_t current = reinterpret_cast<uintptr_t>(m_memory + m_offset);
    uintptr_t aligned = align_forward(current, alignment);
    size_t padding = aligned - current;
    
    if (m_offset + padding + size > m_size)
    {
        LOG_ERROR(logger::tags::memory, "memory overfill");
        return nullptr;
    }

    m_offset += padding;

    void *result = m_memory + m_offset;

    m_offset += size;

    LOG_TRACE(logger::tags::memory, "allocated {} bytes of memory", padding + size);

    return result;
}

void magnetar::LinearAllocator::reset()
{
    m_offset = 0;
}

void magnetar::LinearAllocator::free(void *)
{
    MT_ASSERT(false, "Cannot call free on LinearAllocator");
}

uintptr_t magnetar::LinearAllocator::align_forward(uintptr_t ptr, size_t alignment)
{
    uintptr_t p = ptr;
    uintptr_t modulo = p % alignment;
    if (modulo != 0)
        p += alignment - modulo;

    return p;
}