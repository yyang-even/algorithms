#pragma once

#include "n-ary_tree.h"


/** General Tree (Each node can have arbitrary number of children) Level Order Traversal
 *
 * @reference   https://www.geeksforgeeks.org/generic-tree-level-order-traversal/
 * @reference   N-ary Tree Level Order Traversal
 *              https://leetcode.com/problems/n-ary-tree-level-order-traversal/
 */
static inline auto LevelOrderTraversal_Iterative_Helper(
    const n_ary_tree::array_representation::Node::PointerType root,
    const std::function<bool(const n_ary_tree::array_representation::Node::PointerType)>
on_each_node = {}) {
    std::queue<std::remove_const_t<decltype(root)>> remaining_nodes;
    PushIfNotNull(remaining_nodes, root);

    while (not remaining_nodes.empty()) {
        for (auto current_level_nodes_number = remaining_nodes.size();
             current_level_nodes_number--;) {

            const auto current_node = remaining_nodes.front();
            if (on_each_node and not on_each_node(current_node)) {
                return false;
            }
            remaining_nodes.pop();

            for (const auto child : current_node->children) {
                PushIfNotNull(remaining_nodes, child);
            }
        }
    }

    return true;
}


static inline auto LevelOrderTraversal_Iterative_Helper(
    const n_ary_tree::child_sibling_representation::Node::PointerType root,
    const std::function<bool(const n_ary_tree::child_sibling_representation::Node::PointerType)>
on_each_node = {}) {
    std::queue<std::remove_const_t<decltype(root)>> remaining_nodes;
    PushIfNotNull(remaining_nodes, root);

    while (not remaining_nodes.empty()) {
        for (auto current_level_nodes_number = remaining_nodes.size();
             current_level_nodes_number--;) {

            auto current_node = remaining_nodes.front();
            if (on_each_node and not on_each_node(current_node)) {
                return false;
            }
            remaining_nodes.pop();

            for (current_node = current_node->left_child; current_node;
                 current_node = current_node->right_sibling) {
                remaining_nodes.push(current_node);
            }
        }
    }

    return true;
}
