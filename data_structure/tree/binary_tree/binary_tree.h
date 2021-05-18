#pragma once

#include "data_structure/tree/tree.h"


/** Binary Tree
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.4.
 * @reference   Binary Tree | Set 1 (Introduction)
 *              https://www.geeksforgeeks.org/binary-tree-set-1-introduction/
 * @reference   Binary Tree | Set 2 (Properties)
 *              https://www.geeksforgeeks.org/binary-tree-set-2-properties/
 * @reference   Binary Tree | Set 3 (Types of Binary Tree)
 *              https://www.geeksforgeeks.org/binary-tree-set-3-types-of-binary-tree/
 * @reference   Handshaking Lemma and Interesting Tree Properties
 *              https://www.geeksforgeeks.org/handshaking-lemma-and-interesting-tree-properties/
 * @reference   Applications of tree data structure
 *              https://www.geeksforgeeks.org/applications-of-tree-data-structure/
 */
template <typename T>
struct BinaryTreeNode {
    using ValueType = T;
    using PointerType = std::shared_ptr<BinaryTreeNode>;

    enum class Type {
        leaf,
        left_sided,
        right_sided,
        full,
        unknown,
    };

    PointerType left;
    PointerType right;
    ValueType value{};

    constexpr explicit BinaryTreeNode(ValueType v) : value(std::move(v)) {}
};


class BinaryTree {
public:
    using Node = BinaryTreeNode<int>;
    using ArrayType = std::vector<Node::ValueType>;

    const auto &GetRoot() const {
        return root;
    }

    auto &GetMutableRoot() {
        return root;
    }

    BinaryTree() = default;
    explicit BinaryTree(const Node::ValueType v): root(new Node(v)) {}
    explicit BinaryTree(const BinaryTree::Node::PointerType source_root):
        root(source_root) {}

private:
    Node::PointerType root;
};

template <typename NodeType>
static constexpr inline auto
SetLeftChild(NodeType &node, const typename NodeType::ValueType v) {
    node.left = std::make_shared<NodeType>(v);
    return node.left;
}

template <typename NodeType>
static constexpr inline auto
SetRightChild(NodeType &node, const typename NodeType::ValueType v) {
    node.right = std::make_shared<NodeType>(v);
    return node.right;
}

static inline auto SetNode(const BinaryTree::Node::PointerType node,
                           const BinaryTree::Node::ValueType x) {
    assert(node);
    node->value = x;
    return node;
}


/**
 *     1
 *    / \
 *   2   3
 *  / \
 * 4   5
 */
static inline auto MakeTheSampleCompleteTree() {
    const BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 2);
    SetRightChild(root, 3);
    SetLeftChild(left_child, 4);
    SetRightChild(left_child, 5);

    return binary_tree;
}


static inline auto CheckType(const BinaryTree::Node &node) {
    const auto type_num = static_cast<bool>(node.left) + static_cast<bool>(node.right);
    switch (type_num) {
        case 0:
            return BinaryTree::Node::Type::leaf;
        case 1:
            return node.left ?
                   BinaryTree::Node::Type::left_sided :
                   BinaryTree::Node::Type::right_sided;
        case 2:
            return BinaryTree::Node::Type::full;
    }
    return BinaryTree::Node::Type::unknown;
}


struct BinaryTreeNodeWithParent {
    using ValueType = int;
    using PointerType = std::shared_ptr<BinaryTreeNodeWithParent>;

    PointerType left;
    PointerType right;
    PointerType::weak_type parent;
    ValueType value{};

    constexpr explicit BinaryTreeNodeWithParent(const ValueType v) : value(v) {}
};
