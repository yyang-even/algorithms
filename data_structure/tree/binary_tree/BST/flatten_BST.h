#pragma once


/** Flatten BST to sorted list | Increasing order
 *
 * @reference   https://www.geeksforgeeks.org/flatten-bst-to-sorted-list-increasing-order/
 *
 * Given a binary search tree, the task is to flatten it to a sorted list. Precisely, the
 * value of each node must be lesser than the values of all the nodes at its right, and
 * its left node must be NULL after flattening. We must do it in O(H) extra space where
 * 'H' is the height of BST.
 */
static inline void FlattenBSTtoSortedList_Increasing(
    const BinaryTree::Node::PointerType node,
    BinaryTree::Node::PointerType &previous) {
    if (node) {
        FlattenBSTtoSortedList_Increasing(node->left, previous);

        previous->left = nullptr;
        previous->right = node;
        previous = node;

        FlattenBSTtoSortedList_Increasing(node->right, previous);
    }
}


template <typename Flatten_BST_Func>
static inline auto FlattenBSTtoSortedList(
    const BinaryTree::Node::PointerType root,
    const Flatten_BST_Func flatten_bst) {
    const auto dummy_node = std::make_shared<BinaryTree::Node>(-1);

    auto previous = dummy_node;
    flatten_bst(root, previous);

    previous->left = previous->right = nullptr;

    return dummy_node->right;
}
