#pragma once

/** Binary Tree
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.4.
 * @reference   Binary Tree | Set 1 (Introduction)
 *              https://www.geeksforgeeks.org/binary-tree-set-1-introduction/
 * @reference   Binary Tree | Set 2 (Properties)
 *              https://www.geeksforgeeks.org/binary-tree-set-2-properties/
 * @reference   Binary Tree | Set 3 (Types of Binary Tree)
 *              https://www.geeksforgeeks.org/binary-tree-set-3-types-of-binary-tree/
 */
class BinaryTree {
public:
    struct Node {
        using ValueType = int;
        using PointerType = std::shared_ptr<Node>;

        enum class Type {
            leaf,
            left_sided,
            right_sided,
            full,
            unknown,
        };

        PointerType left;
        PointerType right;
        ValueType value = 0;

        explicit Node(const ValueType v) : value(v) {}
    };
    using ArrayType = std::vector<Node::ValueType>;

    const auto &GetRoot() const {
        return root;
    }

    explicit BinaryTree(const Node::ValueType v): root(new Node(v)) {}

private:
    Node::PointerType root;
};

static inline auto SetLeftChild(BinaryTree::Node &node, const BinaryTree::Node::ValueType v) {
    node.left = std::make_shared<BinaryTree::Node>(v);
    return node.left;
}

static inline auto SetRightChild(BinaryTree::Node &node, const BinaryTree::Node::ValueType v) {
    node.right = std::make_shared<BinaryTree::Node>(v);
    return node.right;
}


/**
 *     1
 *    / \
 *   2   3
 *  / \
 * 4   5
 */
static inline auto MakeTheSampleCompleteTree() {
    BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 2);
    SetRightChild(root, 3);
    SetLeftChild(left_child, 4);
    SetRightChild(left_child, 5);

    return binary_tree;
}


template <typename Container>
static inline void EnqueueIfNotNull(Container &container,
                                    const BinaryTree::Node::PointerType node) {
    if (node) {
        container.push(node);
    }
}


static inline auto CheckType(const BinaryTree::Node &node) {
    const auto type_num = static_cast<bool>(node.left) + static_cast<bool>(node.right);
    switch (type_num) {
        case 0:
            return BinaryTree::Node::Type::leaf;
        case 1:
            return node.left ? BinaryTree::Node::Type::left_sided : BinaryTree::Node::Type::right_sided;
        case 2:
            return BinaryTree::Node::Type::full;
    }
    return BinaryTree::Node::Type::unknown;
}
