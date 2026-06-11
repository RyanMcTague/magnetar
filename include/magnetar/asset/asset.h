#pragma once
#include "magnetar/core/base.h"
#include "magnetar/asset/asset_handle.h"
namespace magnetar
{
    class MAGNETAR_API IAsset
    {
    public:
        virtual ~IAsset() = default;
        virtual AssetHandle handle() const = 0;
        virtual void* resource() = 0;
    };

    template<typename T>
    class MAGNETAR_API Asset
    {
    public:
        Asset(AssetHandle handle):
            m_handle(handle) {}

        AssetHandle handle() const override { return m_handle; }
        void* resource() const override { return m_resource.get(); }
    private:
        AssetHandle m_handle;
        UniqueRef<T> m_resource;
    };
}