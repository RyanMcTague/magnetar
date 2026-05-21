#pragma once
#include <memory>
#include <algorithm>
#include <vector>
#include "magnetar/core/base.h"

namespace magnetar
{
    template <typename T>
    class MAGNETAR_API TreeNode
    {
    public:
        using NodeType = TreeNode<T>;

    public:
        explicit TreeNode(const T &value)
            : m_value(value) {}

        explicit TreeNode(const T &&value)
            : m_value(std::move(value)) {}

        NodeType* parent()
        {
            return m_parent;
        }

        const T &value() const
        {
            return m_value;
        }

        T &value()
        {
            return m_value;
        }

        const std::vector<std::unique_ptr<NodeType>> &children() const
        {
            return m_children;
        }

        template <typename... TArgs>
        NodeType *emplace_child(TArgs &&...args)
        {
            auto child = std::make_unique<NodeType>(std::forward<TArgs>(args)...);
            child->m_parent = this;
            NodeType *ptr = child.get();
            m_children.push_back(std::move(child));
            return ptr;
        }

        void add_child(std::unique_ptr<NodeType> child)
        {
            child->m_parent = this;
            m_children.push_back(std::move(child));
        }

        bool remove_child(NodeType *node)
        {
            auto it = std::find_if(
                m_children.begin(),
                m_children.end(),
                [node](const auto &child)
                { return child.get() == node; });

            if (it == m_children.end())
                return false;

            m_children.erase(it);
            return true;
        }

        void traverse_depth_first(auto &&fn)
        {
            fn(*this);
            for (auto &child : m_children)
                child->traverse_depth_first(fn);
        }

    private:
        T m_value;
        NodeType *m_parent = nullptr;
        std::vector<std::unique_ptr<NodeType>> m_children;
    };

    template <typename T>
    using Tree = TreeNode<T>;
}