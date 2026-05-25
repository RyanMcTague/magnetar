#pragma once
#include <vector>
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/core/time.h"
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
            return std::string((const char *)&raw[0]);
        }

        virtual bool seek(size_t position) = 0;
        virtual size_t tell() const = 0;
        virtual size_t size() const = 0;
        virtual bool eof() const = 0;
        virtual Timestamp last_changed_at() const = 0;
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
        virtual Timestamp last_changed_at(const std::string &path) const = 0;

        virtual const std::string &name() const = 0;

        template<typename T>
        static FileSystem* register_filesystem();

        template<typename T>
        static FileSystem* get();

    private:
        static std::unordered_map<std::type_index, UniqueRef<FileSystem>> s_filesystems;
    };

    template<typename T>
    FileSystem* FileSystem::register_filesystem()
    {
        UniqueRef<T> fs = create_unique_reference<T>();
        s_filesystems.emplace(typeid(T), std::move(fs));
        return s_filesystems[typeid(T)].get();
    }

    template<typename T>
    FileSystem* FileSystem::get()
    {
        auto it = s_filesystems.find(typeid(T));
        MT_ASSERT(it != s_filesystems.end(), "Filesystem not found");
        return it->second.get();
    }
}