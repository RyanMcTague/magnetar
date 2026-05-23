#include <filesystem>
#include <chrono>
#include "magnetar/filesystem/native_file_system.h"

magnetar::DiskFile::DiskFile(const std::string &path, FileMode mode)
    : m_handle(nullptr), m_path(path), m_mode(mode), m_size(0)
{
    m_handle = fopen(path.c_str(), file_mode_ios());

    if (m_handle)
    {
        fseek(m_handle, 0, SEEK_END);
        m_size = ftell(m_handle);
        fseek(m_handle, 0, SEEK_SET);
    }
}
magnetar::DiskFile::~DiskFile()
{
    close();
}
bool magnetar::DiskFile::is_open()
{
    return m_handle != nullptr;
}
void magnetar::DiskFile::close()
{
    if (m_handle)
        fclose(m_handle);
}
size_t magnetar::DiskFile::read(void *buffer, size_t size)
{
    return fread(buffer, 1, size, m_handle);
}
std::vector<uint8_t> magnetar::DiskFile::read_all()
{
    std::vector<uint8_t> data;
    data.resize(size());
    read(&data[0], size());
    return data;
}
size_t magnetar::DiskFile::write(const void *buffer, size_t size)
{
    return fwrite(buffer, 1, size, m_handle);
}
bool magnetar::DiskFile::seek(size_t position)
{
    return fseek(m_handle, position, SEEK_SET) == 0;
}
size_t magnetar::DiskFile::tell() const
{
    return ftell(m_handle);
}
size_t magnetar::DiskFile::size() const
{
    return m_size;
}
bool magnetar::DiskFile::eof() const
{
    return tell() == (size_t)fseek(m_handle, 0, SEEK_END);
}
magnetar::Timestamp magnetar::DiskFile::last_changed_at() const
{
    return std::filesystem::last_write_time(m_path);
}
const char *magnetar::DiskFile::file_mode_ios() const
{
    switch (m_mode)
    {
    case FileMode::READ:
        return "rb";
    case FileMode::WRITE:
        return "wb";
    case FileMode::APPEND:
        return "ab";
    default:
        break;
    }
}

magnetar::UniqueRef<magnetar::File> magnetar::NativeFileSystem::open(const std::string &path, FileMode mode)
{
    auto file = create_unique_reference<DiskFile>(path, mode);
    if (!file->is_open())
        return nullptr;

    return file;
}

bool magnetar::NativeFileSystem::exists(const std::string &path) const
{
    return std::filesystem::exists(path);
}

bool magnetar::NativeFileSystem::create_directory(const std::string &path)
{
    return std::filesystem::create_directory(path);
}

bool magnetar::NativeFileSystem::remove(const std::string &path)
{
    return std::filesystem::remove(path);
}

bool magnetar::NativeFileSystem::is_file(const std::string &path) const
{
    return exists(path) && !is_directory(path);
}

bool magnetar::NativeFileSystem::is_directory(const std::string &path) const
{
    return std::filesystem::is_directory(path);
}

size_t magnetar::NativeFileSystem::file_size(const std::string &path) const
{
    return std::filesystem::file_size(path);
}

const std::string &magnetar::NativeFileSystem::name() const
{
    return m_name;
}

magnetar::Timestamp magnetar::NativeFileSystem::last_changed_at(const std::string &path) const
{
   return std::filesystem::last_write_time(path);
}