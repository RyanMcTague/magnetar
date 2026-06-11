#include "magnetar/core/layer_stack.h"

void magnetar::LayerStack::push_layer(Ref<Layer> layer)
{
    m_layers.push_back(layer);
}