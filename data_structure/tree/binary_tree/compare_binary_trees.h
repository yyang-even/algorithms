#pragma once


static inline auto isSameTree(const BinaryTree::Node::PointerType lhs_node,
                              const BinaryTree::Node::PointerType rhs_node) {
    return lhs_node == rhs_node;
}

/** Write Code to Determine if Two Trees are Identical
 *
 * @reference   https://www.geeksforgeeks.org/write-c-code-to-determine-if-two-trees-are-identical/
 * @reference   Check whether the two Binary Search Trees are Identical or Not
 *              https://www.geeksforgeeks.org/check-whether-the-two-binary-search-trees-are-identical-or-not/
 * @reference   Same Tree
 *              https://leetcode.com/problems/same-tree/
 */
static inline auto areIdenticalTrees(const BinaryTree::Node::PointerType lhs_node,
                                     const BinaryTree::Node::PointerType rhs_node) {
    if (isSameTree(lhs_node, rhs_node)) {
        return true;
    }

    if (lhs_node and rhs_node) {
        return lhs_node->value == rhs_node->value and
               areIdenticalTrees(lhs_node->left, rhs_node->left) and
               areIdenticalTrees(lhs_node->right, rhs_node->right);
    }
    return false;
}
