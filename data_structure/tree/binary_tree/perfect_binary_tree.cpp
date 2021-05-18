#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_deletion.h"
#include "binary_tree_height.h"
#include "binary_tree_traversals.h"
#include "clone_binary_tree.h"


namespace {

/** Check whether a given binary tree is perfect or not
 *
 * @reference   https://www.geeksforgeeks.org/check-weather-given-binary-tree-perfect-not/
 *
 * A Binary tree is Perfect Binary Tree in which all internal nodes have two children
 * and all leaves are at same level.
 */
inline auto isPerfect_Recursive(const BinaryTree::Node::PointerType node,
                                const unsigned expected_height, const unsigned current_level) {
    const auto node_type = CheckType(*node);
    if (node_type == BinaryTree::Node::Type::leaf) {
        return expected_height == current_level;
    }

    if (node_type == BinaryTree::Node::Type::full)
        return isPerfect_Recursive(node->left, expected_height, current_level + 1) and
               isPerfect_Recursive(node->right, expected_height, current_level + 1);

    return false;
}

inline auto isPerfect_Recursive(const BinaryTree::Node::PointerType root_node) {
    if (not root_node) {
        return true;
    }

    const auto height_of_leftmost_leaf = HeightOfLeftmostLeaf(root_node);
    return isPerfect_Recursive(root_node, height_of_leftmost_leaf, 1);
}


/**
 * @reference   Iterative approach to check if a Binary Tree is Perfect
 *              https://www.geeksforgeeks.org/iterative-approach-to-check-if-a-binary-tree-is-perfect/
 */
inline auto isPerfect_Iterative(const BinaryTree::Node::PointerType root_node) {
    bool has_leaf_node_found = false;
    return LevelOrderTraversal_LevelAware_Helper(root_node,
    [&has_leaf_node_found](const auto & node) {
        const auto node_type = CheckType(node);

        if (node_type == BinaryTree::Node::Type::leaf) {
            has_leaf_node_found = true;
        } else if (node_type == BinaryTree::Node::Type::full) {
            if (has_leaf_node_found) {
                return false;
            }
        } else {
            return false;
        }

        return true;
    },
    [&has_leaf_node_found]() {
        return not has_leaf_node_found;
    });
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
/**
 *     1
 *    / \
 *   2   3
 *  /
 * 4
 */
const auto SAMPLE2 = BinaryTreeDeletion_Subtree(CloneBinaryTree(SAMPLE1), 5).GetRoot();
/**
 *     1
 *    / \
 *   2   3
 */
const auto SAMPLE3 = BinaryTreeDeletion_Subtree(CloneBinaryTree(SAMPLE2), 4).GetRoot();


THE_BENCHMARK(isPerfect_Recursive, SAMPLE1);

SIMPLE_TEST(isPerfect_Recursive, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isPerfect_Recursive, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(isPerfect_Recursive, TestSAMPLE3, true, SAMPLE3);


THE_BENCHMARK(isPerfect_Iterative, SAMPLE1);

SIMPLE_TEST(isPerfect_Iterative, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isPerfect_Iterative, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(isPerfect_Iterative, TestSAMPLE3, true, SAMPLE3);
