#pragma once

#include "binary_tree_traversals.h"


/** Check whether a given Binary Tree is Complete or not | Set 1 (Iterative Solution)
 *
 * @reference   https://www.geeksforgeeks.org/check-if-a-given-binary-tree-is-complete-tree-or-not/
 *
 * A complete binary tree is a binary tree in which every level, except possibly the last,
 * is completely filled, and all nodes are as far left as possible. See the following examples.
 * A node is ‘Full Node’ if both left and right children are not empty (or not NULL).
 * The approach is to do a level order traversal starting from the root. In the traversal,
 * once a node is found which is NOT a Full Node, all the following nodes must be leaf nodes.
 */
static inline auto isCompleteBinaryTree(const BinaryTree::Node::PointerType root_node) {
    bool has_nonfull_node_found = false;
    return LevelOrderTraversal_LevelAware_Helper(root_node,
    [&has_nonfull_node_found](const auto & node) {
        const auto node_type = CheckType(node);

        if (has_nonfull_node_found) {
            if (node_type != BinaryTree::Node::Type::leaf) {
                return false;
            }
        } else {
            if (node_type != BinaryTree::Node::Type::full) {
                if (node_type == BinaryTree::Node::Type::right_sided) {
                    return false;
                }
                has_nonfull_node_found = true;
            }
        }

        return true;
    }, {});
}
