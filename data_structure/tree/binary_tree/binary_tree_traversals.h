#pragma once

#include "binary_tree.h"


static inline auto
InorderTraversal_Recursive(const BinaryTree::Node::PointerType node,
                           BinaryTree::ArrayType &outputs) {
    if (not node) {
        return;
    }

    InorderTraversal_Recursive(node->left, outputs);
    outputs.push_back(node->value);
    InorderTraversal_Recursive(node->right, outputs);
}


static inline auto
LevelOrderTraversal_LevelAware_Helper(
    const BinaryTree::Node::PointerType root_node,
const std::function<bool(BinaryTree::Node &)> on_each_node = {},
const std::function<bool(void)> on_level_change = {}) {
    std::queue<BinaryTree::Node::PointerType> remaining_nodes;
    PushIfNotNull(remaining_nodes, root_node);

    while (not remaining_nodes.empty()) {
        if (on_level_change) {
            if (not on_level_change()) {
                return false;
            }
        }

        for (auto number_nodes_at_current_level = remaining_nodes.size();
             number_nodes_at_current_level--;) {
            const auto node = remaining_nodes.front();
            remaining_nodes.pop();

            if (on_each_node) {
                if (not on_each_node(*node)) {
                    return false;
                }
            }

            PushIfNotNull(remaining_nodes, node->left);
            PushIfNotNull(remaining_nodes, node->right);
        }
    }

    return true;
}
