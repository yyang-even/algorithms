#pragma once


/**
 * @reference   Deleting a binary tree using the delete keyword
 *              https://www.geeksforgeeks.org/deleting-a-binary-tree-using-the-delete-keyword/
 */
static inline void
BinaryTreeDeletion_Subtree(BinaryTree::Node::PointerType &current_node,
                           const BinaryTree::Node::ValueType x) {
    if (current_node) {
        if (current_node->value == x) {
            current_node = nullptr;
        } else {
            BinaryTreeDeletion_Subtree(current_node->left, x);
            BinaryTreeDeletion_Subtree(current_node->right, x);
        }
    }
}

static inline auto
BinaryTreeDeletion_Subtree(BinaryTree binary_tree,
                           const BinaryTree::Node::ValueType x) {
    BinaryTreeDeletion_Subtree(binary_tree.GetMutableRoot(), x);

    return binary_tree;
}
