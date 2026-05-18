#pragma once
#include <unordered_map>
#include "magnetar/core/base.h"
#include "magnetar/core/file_system.h"
#include "magnetar/utils/string_utils.h"

namespace magnetar
{
    namespace memfs
    {
        enum class MAGNETAR_API NodeType
        {
            FILE = 0,
            DIRECTORY
        };

        class MAGNETAR_API Node
        {
        public:
            Node(const std::string &name, NodeType type) : m_name{name}, m_type{type} {}

            virtual ~Node() = default;

            const std::string &name() const { return m_name; }
            NodeType type() const { return m_type; }

        private:
            std::string m_name;
            NodeType m_type;
        };

        class MAGNETAR_API FileNode : public Node
        {
        public:
            FileNode(const std::string &name) : Node(name, NodeType::FILE) {}
            ~FileNode()
            {
                if (data)
                    free(data);
            }
            void *data = nullptr;
            size_t size = 0;
        };

        class MAGNETAR_API DirectoryNode : public Node
        {
        public:
            DirectoryNode(const std::string &name) : Node(name, NodeType::DIRECTORY) {}

            template <typename T>
            T *add(UniqueRef<T> node)
            {
                T *ptr = node.get();
                m_children[ptr->name()] = std::move(node);
                return ptr;
            }

            Node *find(const std::string &name)
            {
                auto it = m_children.find(name);
                if (it == m_children.end())
                    return nullptr;
                return it->second.get();
            }

            const auto &children() const { return m_children; }

        private:
            std::unordered_map<std::string, UniqueRef<Node>> m_children;
        };
    }

    class MemoryFileSystem;

    class MAGNETAR_API MemoryFile : public File
    {
    public:
        MemoryFile(MemoryFileSystem *fs, const std::string &path, FileMode mode);
        ~MemoryFile() override;

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
        FileMode m_mode;
        uint64_t m_cursor;
        std::string m_path;
        MemoryFileSystem *m_fs;
        bool m_is_open;
    };

    class MAGNETAR_API MemoryFileSystem : public FileSystem
    {
    public:
        MemoryFileSystem();
        ~MemoryFileSystem() override = default;

        UniqueRef<File> open(const std::string &path, FileMode mode) override;

        const std::string& name() const override { return m_name; }

        bool exists(const std::string &path) const override;
        bool create_directory(const std::string &path) override;
        bool remove(const std::string &path) override;
        bool is_file(const std::string &path) const override;
        bool is_directory(const std::string &path) const override;

        size_t read(const std::string &path, void *buffer, size_t offset, size_t size);
        size_t write(const std::string &path, const void *buffer, size_t offset, size_t size, FileMode mode);
        size_t file_size(const std::string &path) const override;

        bool set_file(const std::string& path, void* buffer, size_t size);
        bool set_file(const std::string& path, const std::string& text);

        void print() const { print_node(m_root.get(), 0); }

    private:
        UniqueRef<memfs::DirectoryNode> m_root;

        template <typename T>
        bool create_node(const std::string &path);

        memfs::Node *resolve(const std::string &path) const;

        static void print_node(const memfs::Node *node, int depth);

        std::string m_name = "memory-file-system";
    };

    template <typename T>
    bool MemoryFileSystem::create_node(const std::string &path)
    {
        auto parts = string_utils::split(path, '/');
        if (parts.empty())
            return false;

        memfs::DirectoryNode *current = m_root.get();

        for (size_t i = 0; i < parts.size() - 1; i++)
        {
            memfs::Node *node = current->find(parts[i]);
            if (!node)
            {
                auto dir = create_unqiue_reference<memfs::DirectoryNode>(parts[i]);
                node = current->add(std::move(dir));
            }

            if (node->type() != memfs::NodeType::DIRECTORY)
                return false;

            current = static_cast<memfs::DirectoryNode *>(node);
        }

        const std::string &final_name = parts.back();

        if (current->find(final_name))
            return false;

        current->add(create_unqiue_reference<T>(final_name));

        return true;
    }
}