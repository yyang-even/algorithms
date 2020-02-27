#pragma once


static inline auto LeftmostNode(BinaryTree::Node::PointerType current_node) {
    if (current_node)
        for (; current_node->left; current_node = current_node->left);
    return current_node;
}
