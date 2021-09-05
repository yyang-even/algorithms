#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_traversals.h"
#include "single_order_to_binary_tree.h"


namespace {

/** Find Minimum Depth of a Binary Tree
 *
 * @reference   https://www.geeksforgeeks.org/find-minimum-depth-of-a-binary-tree/
 * @reference   Minimum Depth of Binary Tree
 *              https://leetcode.com/problems/minimum-depth-of-binary-tree/
 *
 * Given a binary tree, find its minimum depth. The minimum depth is the number of nodes
 * along the shortest path from the root node down to the nearest leaf node.
 */
auto MinDepth_Recursive(const BinaryTree::Node::PointerType node) {
    if (not node) {
        return 0;
    }

    if (not node->left and not node->right) {
        return 1;
    }

    const auto left_min = node->left ? MinDepth_Recursive(node->left) : INT_MAX;
    const auto right_min = node->right ? MinDepth_Recursive(node->right) : INT_MAX;

    return std::min(left_min, right_min) + 1;
}


inline auto
MinDepth_LevelOrder(const BinaryTree::Node::PointerType root) {
    int result = 0;
    LevelOrderTraversal_LevelAware_Helper(root,
    [](const auto & node) {
        return node.left or node.right;
    },
    [&result]() {
        return ++result;
    });

    return result;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();

/**
 *     1
 *    /
 *   2
 *  /
 * 4
 */
const auto SAMPLE2 = LevelOrderToBinaryTree( {
    1, 2, SENTINEL, 4
});


THE_BENCHMARK(MinDepth_Recursive, SAMPLE1);

SIMPLE_TEST(MinDepth_Recursive, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(MinDepth_Recursive, TestSAMPLE2, 3, SAMPLE2);


THE_BENCHMARK(MinDepth_LevelOrder, SAMPLE1);

SIMPLE_TEST(MinDepth_LevelOrder, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(MinDepth_LevelOrder, TestSAMPLE2, 3, SAMPLE2);
