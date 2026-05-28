#include "magnetar/renderer/buffer_layout.h"

magnetar::BufferLayout::BufferLayout()
    : m_stride() {}

void magnetar::BufferLayout::push(const std::string &name, RendererDataType type, bool normalized)
{
    Element element;
    element.location = m_elements.size() + 1;
    element.name = name;
    element.type = type;
    element.normalized = normalized;
    element.offset = m_stride;
    m_stride += renderer_data_type_size(type);
}