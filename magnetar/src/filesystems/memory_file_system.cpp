#include <cstring>
#include <iostream>
#include <sstream>
#include "magnetar/filesystem/memory_file_system.h"

magnetar::MemoryFile::MemoryFile(MemoryFileSystem *fs, const std::string &path, FileMode mode)
{
    m_cursor = 0;
    m_fs = fs;
    m_mode = mode;
    m_path = path;
    m_is_open = m_fs->is_file(path);
}

magnetar::MemoryFile::~MemoryFile()
{
}

bool magnetar::MemoryFile::is_open()
{
    return m_is_open;
}
void magnetar::MemoryFile::close()
{
    m_is_open = false;
}
size_t magnetar::MemoryFile::read(void *buffer, size_t size)
{
    size_t bytes_read = m_fs->read(m_path, (uint8_t *)buffer, m_cursor, size);
    m_cursor += bytes_read;
    return bytes_read;
}
std::vector<uint8_t> magnetar::MemoryFile::read_all()
{
    std::vector<uint8_t> buffer;
    buffer.resize(size());
    read(&buffer[0], size());
    return buffer;
}

size_t magnetar::MemoryFile::write(const void *buffer, size_t size)
{
    size_t bytes_read = m_fs->write(m_path, buffer, m_cursor, size, m_mode);
    m_cursor += bytes_read;
    return bytes_read;
}
bool magnetar::MemoryFile::seek(size_t position)
{
    if (position > size())
        return false;

    m_cursor = position;
    return true;
}
size_t magnetar::MemoryFile::tell() const
{
    return m_cursor;
}
size_t magnetar::MemoryFile::size() const
{
    return m_fs->file_size(m_path);
}
bool magnetar::MemoryFile::eof() const
{
    return m_cursor == size();
}

magnetar::Timestamp magnetar::MemoryFile::last_changed_at() const
{
    return m_fs->last_changed_at(m_path);
}
const std::string &magnetar::MemoryFile::uri() const
{
    return m_path;
}

magnetar::UniqueRef<magnetar::File> magnetar::MemoryFileSystem::open(const std::string &path, FileMode mode)
{
    auto file = create_unique_reference<MemoryFile>(this, path, mode);
    if (!file->is_open() && mode == FileMode::READ)
    {
        return nullptr;
    }
    else if (!file->is_open())
    {
        create_node<memfs::FileNode>(path);
        file = create_unique_reference<MemoryFile>(this, path, mode);
    }
    return file;
}

magnetar::MemoryFileSystem::MemoryFileSystem()
{
    m_root = create_unique_reference<memfs::DirectoryNode>("/");
}
bool magnetar::MemoryFileSystem::exists(const std::string &path) const
{
    return resolve(path) != nullptr;
}
bool magnetar::MemoryFileSystem::create_directory(const std::string &path)
{
    return create_node<memfs::DirectoryNode>(path);
}
bool magnetar::MemoryFileSystem::remove(const std::string &path)
{
    auto node = resolve(path);
    if (!node || !node->parent)
        return false;

    return static_cast<memfs::DirectoryNode *>(node->parent)->remove(node);
}
bool magnetar::MemoryFileSystem::is_file(const std::string &path) const
{
    auto item = resolve(path);
    if (!item)
        return false;
    return item->type() == memfs::NodeType::FILE;
}
bool magnetar::MemoryFileSystem::is_directory(const std::string &path) const
{
    auto item = resolve(path);
    if (!item)
        return false;
    return item->type() == memfs::NodeType::DIRECTORY;
}

magnetar::memfs::Node *magnetar::MemoryFileSystem::resolve(const std::string &path) const
{
    auto parts = string_utils::split(path, '/');
    if (parts.empty())
        return m_root.get();

    memfs::DirectoryNode *current = m_root.get();

    for (size_t i = 0; i < parts.size(); ++i)
    {
        memfs::Node *node = current->find(parts[i]);

        if (!node)
            return nullptr;

        if (i == parts.size() - 1)
            return node;

        if (node->type() != memfs::NodeType::DIRECTORY)
            return nullptr;

        current = static_cast<memfs::DirectoryNode *>(node);
    }

    return nullptr;
}

size_t magnetar::MemoryFileSystem::read(const std::string &path, void *buffer, size_t offset, size_t size)
{
    auto node = resolve(path);
    if (node->type() != memfs::NodeType::FILE)
        return 0;

    auto file_node = static_cast<memfs::FileNode *>(node);

    if (offset >= file_node->size)
        return 0;

    bool count_does_overflow = (size + offset) > file_node->size;
    size_t bytes_to_read = (count_does_overflow ? file_node->size : size) - offset;

    uint8_t *start = (uint8_t *)file_node->data + offset;

    memcpy(buffer, start, bytes_to_read);

    return bytes_to_read;
}

size_t magnetar::MemoryFileSystem::file_size(const std::string &path) const
{
    auto node = resolve(path);
    if (node->type() != memfs::NodeType::FILE)
        return 0;

    return static_cast<memfs::FileNode *>(node)->size;
}

magnetar::Timestamp magnetar::MemoryFileSystem::last_changed_at(const std::string &path) const
{
    auto node = resolve(path);
    MT_ASSERT(node->type() == memfs::NodeType::FILE, "{} is not a file", path);
    return static_cast<memfs::FileNode *>(node)->last_changed_at;
}

size_t magnetar::MemoryFileSystem::write(const std::string &path, const void *buffer, size_t offset, size_t size, FileMode mode)
{
    if (mode == FileMode::READ)
        return 0;

    if (!exists(path) && !create_node<memfs::FileNode>(path))
        return 0;

    auto node = resolve(path);

    if (node->type() != memfs::NodeType::FILE)
        return 0;

    auto file_node = static_cast<memfs::FileNode *>(node);
    file_node->last_changed_at = Timestamp();
    if (mode == FileMode::APPEND)
    {
        long new_bytes_to_add = file_node->size - offset - size;
        if (new_bytes_to_add > 0)
        {
            file_node->size += (size_t)new_bytes_to_add;
            file_node->data = realloc(file_node->data, file_node->size);
        }
        uint8_t *ptr = static_cast<uint8_t *>(file_node->data);
        memmove(&ptr[offset + 1], &ptr[offset], file_node->size - offset);
        memcpy(&ptr[offset], buffer, size);
    }
    else if (mode == FileMode::WRITE)
    {
        file_node->size += size;
        file_node->data = realloc(file_node->data, file_node->size);
        memcpy(file_node->data, buffer, size);
    }

    return size;
}

void magnetar::MemoryFileSystem::print_node(const memfs::Node *node, int depth)
{
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";

    std::cout << node->name();

    if (node->type() == memfs::NodeType::DIRECTORY)
        std::cout << "/";

    std::cout << "\n";

    if (node->type() == memfs::NodeType::DIRECTORY)
    {
        const auto *dir = static_cast<const memfs::DirectoryNode *>(node);

        for (const auto &pair : dir->children())
        {
            const auto &child = pair.second;
            print_node(child.get(), depth + 1);
        }
    }
}

bool magnetar::MemoryFileSystem::set_file(const std::string &path, void *buffer, size_t size)
{
    create_node<memfs::FileNode>(path);
    return write(path, buffer, 0, size, FileMode::WRITE) != 0;
}

bool magnetar::MemoryFileSystem::set_file(const std::string &path, const std::string &text)
{
    create_node<memfs::FileNode>(path);
    return write(path, text.c_str(), 0, text.size(), FileMode::WRITE) != 0;
}