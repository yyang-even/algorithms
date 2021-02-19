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


/** Find the node with minimum value in a Binary Search Tree
 *
 * @reference   https://www.geeksforgeeks.org/find-the-minimum-element-in-a-binary-search-tree/
 * @reference   Find the node with minimum value in a Binary Search Tree using recursion
 *              https://www.geeksforgeeks.org/find-the-node-with-minimum-value-in-a-binary-search-tree-using-recursion/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 12.2-2.
 */
template <typename NodePointerType>
static inline auto MinimumNode(const NodePointerType root_node) {
    return LeftmostNode(root_node);
}


/** Find the node with maximum value in a Binary Search Tree
 *
 * @reference   https://www.geeksforgeeks.org/find-the-node-with-maximum-value-in-a-binary-search-tree/
 * @reference   Find the node with maximum value in a Binary Search Tree using recursion
 *              https://www.geeksforgeeks.org/find-the-node-with-maximum-value-in-a-binary-search-tree-using-recursion/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 12.2-2.
 */
template <typename NodePointerType>
static inline auto MaximumNode(const NodePointerType root_node) {
    return RightmostNode(root_node);
}
