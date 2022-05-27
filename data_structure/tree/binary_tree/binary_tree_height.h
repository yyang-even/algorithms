#pragma once

#include "binary_tree.h"


/** Write a Program to Find the Maximum Depth or Height of a Tree
 *
 * @reference   https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 5.
 * @reference   Maximum Depth of Binary Tree
 *              https://leetcode.com/problems/maximum-depth-of-binary-tree/
 */
static inline unsigned Height_Recursive(const BinaryTree::Node::PointerType node) {
    if (not node) {
        return 0;
    }

    return 1 + std::max(Height_Recursive(node->left), Height_Recursive(node->right));
}


static inline auto HeightOfLeftmostLeaf(BinaryTree::Node::PointerType node) {
    unsigned height = 0;
    for (; node; ++height, node = node->left)
        ;
    return height;
}
