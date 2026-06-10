#include "magnetar/core/layer_stack.h"

void magnetar::LayerStack::push_layer(std::unique_ptr<Layer> layer)
{
    m_layers.push_back(std::move(layer));
}