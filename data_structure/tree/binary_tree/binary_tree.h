#pragma once

/** Binary Tree
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.4.
 */
class BinaryTree {
public:
    struct Node {
        using ValueType = int;
        using PointerType = std::shared_ptr<Node>;

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

static auto SetLeftChild(BinaryTree::Node &node, const BinaryTree::Node::ValueType v) {
    node.left = std::make_shared<BinaryTree::Node>(v);
    return node.left;
}

static auto SetRightChild(BinaryTree::Node &node, const BinaryTree::Node::ValueType v) {
    node.right = std::make_shared<BinaryTree::Node>(v);
    return node.right;
}
