#pragma once


template <typename Container>
static inline void EnqueueIfNotNull(Container &container,
                                    const BinaryTree::Node::PointerType node) {
    if (node) {
        container.push(node);
    }
}


static auto LevelOrderTraversal_LevelAware_Helper(const BinaryTree::Node::PointerType root_node,
        BinaryTree::ArrayType *const outputs = nullptr,
std::function<void(void)> on_level_change = {}) {
    std::queue<BinaryTree::Node::PointerType> remaining_nodes;
    EnqueueIfNotNull(remaining_nodes, root_node);

    while (not remaining_nodes.empty()) {
        if (on_level_change) {
            on_level_change();
        }

        for (auto number_nodes_at_current_level = remaining_nodes.size();
             number_nodes_at_current_level;
             --number_nodes_at_current_level) {
            const auto node = remaining_nodes.front();
            remaining_nodes.pop();
            if (outputs) {
                outputs->push_back(node->value);
            }

            EnqueueIfNotNull(remaining_nodes, node->left);
            EnqueueIfNotNull(remaining_nodes, node->right);
        }
    }
}
