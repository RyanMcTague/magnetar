#pragma once
#include <vector>
#include <algorithm>
#include "magnetar/core/base.h"
#include "magnetar/core/layer.h"

namespace magnetar
{
    class MAGNETAR_API LayerStack
    {
    public:
        void push_layer(Ref<Layer> layer);

        std::vector<Ref<Layer>>::iterator begin() { return m_layers.begin(); }
        std::vector<Ref<Layer>>::iterator end() { return m_layers.end(); }

        std::vector<Ref<Layer>>::const_iterator begin() const { return m_layers.begin(); }
        std::vector<Ref<Layer>>::const_iterator end() const { return m_layers.end(); }

        void clear() { m_layers.clear(); }

        template<typename T>
        Ref<T> get_layer();
    private:
        std::vector<Ref<Layer>> m_layers;
    };
}

template<typename T>
magnetar::Ref<T> magnetar::LayerStack::get_layer()
{
    auto it = std::find_if(m_layers.begin(), m_layers.end(), [](const Ref<Layer>& layer){
        return layer->class_name() == MT_STATIC_CLASS_NAME(T);
    });

    return it == m_layers.end() ? nullptr : std::static_pointer_cast<T>(it);
}