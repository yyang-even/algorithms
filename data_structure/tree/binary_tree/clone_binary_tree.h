#pragma once

#include "binary_tree.h"


template<typename NodeType>
static inline constexpr void CopyBinaryTree(const BinaryTree::Node::PointerType source_node,
                                            NodeType &new_node) {
    assert(source_node);

    if (source_node->left) {
        SetLeftChild(new_node, source_node->left->value);
        CopyBinaryTree(source_node->left, *(new_node.left));
    }

    if (source_node->right) {
        SetRightChild(new_node, source_node->right->value);
        CopyBinaryTree(source_node->right, *(new_node.right));
    }
}

template<typename NodeType>
static inline constexpr auto CopyBinaryTree(const BinaryTree::Node::PointerType source_root) {
    assert(source_root);

    const auto destination_root = std::make_shared<NodeType>(source_root->value);
    CopyBinaryTree(source_root, *destination_root);

    return destination_root;
}

static inline auto CloneBinaryTree(const BinaryTree::Node::PointerType source_root) {
    if (source_root) {
        BinaryTree new_tree {source_root->value};
        CopyBinaryTree(source_root, *new_tree.GetRoot());
        return new_tree;
    }

    return BinaryTree {};
}

static inline auto CloneBinaryTree(const BinaryTree &source_tree) {
    return CloneBinaryTree(source_tree.GetRoot());
}


static inline void LinkParents(const BinaryTreeNodeWithParent::PointerType node) {
    if (node) {
        if (node->left) {
            node->left->parent = node;
            LinkParents(node->left);
        }

        if (node->right) {
            node->right->parent = node;
            LinkParents(node->right);
        }
    }
}

static inline auto ToBinaryTreeWithParents(const BinaryTree::Node::PointerType root) {
    const auto new_root = CopyBinaryTree<BinaryTreeNodeWithParent>(root);
    LinkParents(new_root);
    return new_root;
}


/**
 * @reference   Find a Corresponding Node of a Binary Tree in a Clone of That Tree
 *              https://leetcode.com/problems/find-a-corresponding-node-of-a-binary-tree-in-a-clone-of-that-tree/
 *
 * Given two binary trees original and cloned and given a reference to a node target in the
 * original tree.
 * The cloned tree is a copy of the original tree.
 * Return a reference to the same node in the cloned tree.
 * Note that you are not allowed to change any of the two trees or the target node and the
 * answer must be a reference to a node in the cloned tree.
 * Follow up: Could you solve the problem if repeated values on the tree are allowed?
 */
