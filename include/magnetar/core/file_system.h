#pragma once
#include <vector>
#include "magnetar/core/base.h"

namespace magnetar
{
    enum class MAGNETAR_API FileMode
    {
        READ,
        WRITE,
        APPEND
    };

    class MAGNETAR_API File
    {
    public:
        File() = default;
        virtual ~File() = default;

        File(const File &) = delete;
        File &operator=(const File &) = delete;

        virtual bool is_open() = 0;
        virtual void close() = 0;

        virtual size_t read(void *buffer, size_t size) = 0;
        virtual std::vector<uint8_t> read_all() = 0;
        virtual size_t write(const void *buffer, size_t size) = 0;
        std::string to_string()
        {
            auto raw = read_all();
            raw.push_back(0);
            return std::string((const char*)&raw[0]);
        }

        virtual bool seek(size_t position) = 0;
        virtual size_t tell() const = 0;
        virtual size_t size() const = 0;
        virtual bool eof() const = 0;
    };

    class MAGNETAR_API FileSystem
    {
    public:
        virtual ~FileSystem() = default;

        virtual UniqueRef<File> open(const std::string &path, FileMode mode) = 0;
        virtual bool create_directory(const std::string &path) = 0;
        virtual bool remove(const std::string &path) = 0;

        virtual bool exists(const std::string &path) const = 0;
        virtual bool is_file(const std::string &path) const = 0;
        virtual bool is_directory(const std::string &path) const = 0;
        virtual size_t file_size(const std::string &path) const = 0;

        virtual const std::string &name() const = 0;
    };
}