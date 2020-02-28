#pragma once


static inline auto LeftmostNode(BinaryTree::Node::PointerType current_node) {
    if (current_node)
        for (; current_node->left; current_node = current_node->left);
    return current_node;
}


static inline auto RightmostNode(BinaryTree::Node::PointerType current_node) {
    if (current_node)
        for (; current_node->right; current_node = current_node->right);
    return current_node;
}
