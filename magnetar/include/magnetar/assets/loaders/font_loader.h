#pragma once
#include "magnetar/core/base.h"
#include "magnetar/assets/resouce_loader.h"
#include "magnetar/renderer/font.h"

namespace magnetar
{
    class MAGNETAR_API FontLoader : public ResourceLoader
    {
    public:
        const std::string resource_name() const override { return m_resource_name; }

        Ref<Asset> load(const YAML::Node &node) const override;

        std::type_index type_index() const override { return typeid(Font); }

    private:
        std::string m_resource_name = "font";
    };
}