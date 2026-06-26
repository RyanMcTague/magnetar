#pragma once
#include "magnetar/core/base.h"
#include "magnetar/assets/asset_handle.h"
#include "magnetar/assets/asset.h"
#include <yaml-cpp/yaml.h>
#include <typeindex>
namespace magnetar
{
    class MAGNETAR_API ResourceLoader
    {
    public:
        virtual ~ResourceLoader() = default;

        virtual const std::string resource_name() const = 0;
        virtual Ref<Asset> load(const YAML::Node &node) const  = 0;
        virtual std::type_index type_index() const = 0;
    };
}