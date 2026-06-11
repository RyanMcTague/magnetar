#pragma once
#include "magnetar/core/base.h"
#include "magnetar/importer/enums.h"

namespace magnetar
{
    template<typename T>
    struct MAGNETAR_API ImportResult
    {
        ImportStatus status = ImportStatus::FAILURE;
        std::string message;
        T data;
    };

    class MAGNETAR_API IAssetImporter
    {
    public:
        virtual ~IAssetImporter() = default;

    };

    template<typename T>
    class AssetImporter: public IAssetImporter
    {
    public:
        virtual ImportResult<T> import(const std::string &path) = 0;
    };
}