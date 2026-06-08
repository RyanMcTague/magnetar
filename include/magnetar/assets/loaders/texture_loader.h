#pragma once
#include "magnetar/core/base.h"
#include "magnetar/assets/resouce_loader.h"
#include "magnetar/renderer/texture.h"

namespace magnetar
{
    class MAGNETAR_API Texture2DLoader : public ResourceLoader
    {
    public:
        const std::string resource_name() const override { return m_resource_name; }

        Ref<Asset> load(const YAML::Node &node) const override;

        std::type_index type_index() const override { return typeid(Texture2D); }

    private:
        std::string m_resource_name = "texture2D";
    };
}