#pragma once

#include "data_structure/tree/binary_tree/binary_tree_search.h"


/**
 * @reference   Iterative searching in Binary Search Tree
 *              https://www.geeksforgeeks.org/iterative-searching-binary-search-tree/
 */
static inline auto BSTSearch_Iterative(BinaryTree::Node::PointerType current_node,
                                       const BinaryTree::Node::ValueType x) {
    while (current_node) {
        if (x < current_node->value) {
            current_node = current_node->left;
        } else if (x > current_node->value) {
            current_node = current_node->right;
        } else {
            return current_node;
        }
    }

    return BinaryTree::Node::PointerType{};
}


static inline auto MinimumNode(const BinaryTree::Node::PointerType root_node) {
    return LeftmostNode(root_node);
}
