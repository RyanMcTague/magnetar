#pragma once
#include <vector>
#include "magnetar/core/base.h"
#include "magnetar/core/layer.h"

namespace magnetar
{
    class MAGNETAR_API LayerStack
    {
    public:
        void push_layer(std::unique_ptr<Layer> layer);

        std::vector<UniqueRef<Layer>>::iterator begin() { return m_layers.begin(); }
        std::vector<UniqueRef<Layer>>::iterator end() { return m_layers.end(); }

        std::vector<UniqueRef<Layer>>::const_iterator begin() const { return m_layers.begin(); }
        std::vector<UniqueRef<Layer>>::const_iterator end() const { return m_layers.end(); }

        void clear() { m_layers.clear(); }

    private:
        std::vector<UniqueRef<Layer>> m_layers;
    };
}