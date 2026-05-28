#pragma once
#include <vector>
#include "magnetar/core/base.h"
#include "magnetar/renderer/enums.h"
namespace magnetar
{
    class MAGNETAR_API BufferLayout
    {
    public:
        struct Element
        {
            std::string name;
            RendererDataType type;
            int location = -1;
            bool normalized = false;
            size_t offset = 0;
        };

    public:
        BufferLayout();
        std::vector<Element>::iterator begin() { return m_elements.begin(); }
        std::vector<Element>::iterator end() { return m_elements.end(); }
        std::vector<Element>::const_iterator begin() const { return m_elements.begin(); }
        std::vector<Element>::const_iterator end() const { return m_elements.end(); }

        size_t stride() const { return m_stride; }

        void push(const std::string& name, RendererDataType type, bool normalized);
    private:
        std::vector<Element> m_elements;
        size_t m_stride;
    };
}