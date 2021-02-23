#pragma once


template <typename NodePointerType>
static inline auto LeftmostNode(NodePointerType current_node) {
    if (current_node)
        for (; current_node->left; current_node = current_node->left);
    return current_node;
}


template <typename NodePointerType>
static inline auto RightmostNode(NodePointerType current_node) {
    if (current_node)
        for (; current_node->right; current_node = current_node->right);
    return current_node;
}


/** Print path from root to a given node in a binary tree
 *
 * @reference   https://www.geeksforgeeks.org/print-path-root-given-node-binary-tree/
 *
 * @reference   Find distance from root to given node in a binary tree
 *              https://www.geeksforgeeks.org/find-distance-root-given-node-binary-tree/
 *
 * Given root of a binary tree and a key x in it, find distance of the given key from
 * root. Distance means number of edges between two nodes.
 *
 * @reference   Get Level of a node in a Binary Tree
 *              https://www.geeksforgeeks.org/get-level-of-a-node-in-a-binary-tree/
 */
static inline auto
BinaryTreeSearch_Preorder(const BinaryTree::Node::PointerType node,
                          const BinaryTree::Node::ValueType x,
                          std::vector<BinaryTree::Node::ValueType> *const path = nullptr) {
    if (not node) {
        return false;
    }

    if (path) {
        path->push_back(node->value);
    }

    if (node->value == x or
        BinaryTreeSearch_Preorder(node->left, x, path) or
        BinaryTreeSearch_Preorder(node->right, x, path)) {
        return true;
    }

    if (path) {
        path->pop_back();
    }

    return false;
}


/**
 * @reference   Print Ancestors of a given node in Binary Tree
 *              https://www.geeksforgeeks.org/print-ancestors-of-a-given-node-in-binary-tree/
 */
