#pragma once


static auto LevelOrderTraversal_LevelAware_Helper(const BinaryTree::Node::PointerType root_node,
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
             number_nodes_at_current_level;
             --number_nodes_at_current_level) {
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
