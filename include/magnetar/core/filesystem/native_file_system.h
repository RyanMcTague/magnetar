#pragma once
#include <cstdio>
#include "magnetar/core/base.h"
#include "magnetar/core/filesystem/file_system.h"
namespace magnetar
{
    class MAGNETAR_API DiskFile : public File
    {
    public:
        DiskFile(const std::string &path, FileMode mode);
        ~DiskFile() override;
        bool is_open() override;
        void close() override;

        size_t read(void *buffer, size_t size) override;
        std::vector<uint8_t> read_all() override;
        size_t write(const void *buffer, size_t size) override;

        bool seek(size_t position) override;
        size_t tell() const override;
        size_t size() const override;
        bool eof() const override;

    private:
        FILE *m_handle;
        std::string m_path;
        FileMode m_mode;
        size_t m_size;

        const char* file_mode_ios() const;
    };

    class MAGNETAR_API NativeFileSystem : public FileSystem
    {
    public:
        const std::string &name() const override;

        UniqueRef<File> open(const std::string &path, FileMode mode) override;
        bool create_directory(const std::string &path) override;
        bool remove(const std::string &path) override;

        bool exists(const std::string &path) const override;
        bool is_file(const std::string &path) const override;
        bool is_directory(const std::string &path) const override;
        size_t file_size(const std::string &path) const override;

    private:
        std::string m_name = "disk";
    };
}