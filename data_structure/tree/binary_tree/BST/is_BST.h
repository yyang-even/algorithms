#pragma once


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 12.1.
 * @reference   Check if a Binary Tree is BST : Simple and Efficient Approach
 *              https://www.geeksforgeeks.org/check-if-a-binary-tree-is-bst-simple-and-efficient-approach/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.5.
 *
 * @reference   Validate Binary Search Tree
 *              https://leetcode.com/problems/validate-binary-search-tree/
 *
 * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
 * A valid BST is defined as follows:
 *  The left subtree of a node contains only nodes with keys less than the node's key.
 *  The right subtree of a node contains only nodes with keys greater than the node's key.
 *  Both the left and right subtrees must also be binary search trees.
 */
static inline bool isBST_Recursive_Inorder(const BinaryTree::Node::PointerType node,
                                           BinaryTree::Node::PointerType &previous_node) {
    if (node) {
        if (not isBST_Recursive_Inorder(node->left, previous_node)) {
            return false;
        }

        if (previous_node and node->value <= previous_node->value) {
            return false;
        }
        previous_node = node;

        if (not isBST_Recursive_Inorder(node->right, previous_node)) {
            return false;
        }
    }

    return true;
}

static inline auto isBST_Recursive_Inorder(const BinaryTree::Node::PointerType node) {
    BinaryTree::Node::PointerType previous_node;
    return isBST_Recursive_Inorder(node, previous_node);
}
