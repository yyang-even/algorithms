#pragma once

#include "data_structure/tree/binary_tree/binary_tree.h"


/** Binary Search Tree
 *
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 5.
 *
 * @reference   How to handle duplicates in Binary Search Tree?
 *              https://www.geeksforgeeks.org/how-to-handle-duplicates-in-binary-search-tree/
 * @reference   Applications of BST
 *              https://www.geeksforgeeks.org/applications-of-bst/
 * @reference   Difference between Binary Tree and Binary Search Tree
 *              https://www.geeksforgeeks.org/difference-between-binary-tree-and-binary-search-tree/
 *
 * Binary Search Tree, is a node-based binary tree data structure which has the following
 * properties:
 *  The left subtree of a node contains only nodes with keys lesser than the node's key.
 *  The right subtree of a node contains only nodes with keys greater than the node's key.
 *  The left and right subtree each must also be a binary search tree.
 *  There must be no duplicate nodes.
 */


/**
 *     4
 *    / \
 *   2   5
 *  / \
 * 1   3
 */
static inline auto MakeTheSampleBST() {
    const BinaryTree binary_tree{4};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 2);
    SetRightChild(root, 5);
    SetLeftChild(left_child, 1);
    SetRightChild(left_child, 3);

    return binary_tree;
}
