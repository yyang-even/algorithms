#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_deletion.h"
#include "clone_binary_tree.h"
#include "complete_binary_tree.h"
#include "single_order_to_binary_tree.h"


namespace {

/** Check whether a binary tree is a complete tree or not | Set 2 (Recursive Solution)
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-binary-tree-complete-not-set-2-recursive-solution/
 */


/**
 * @reference   Count Complete Tree Nodes
 *              https://leetcode.com/problems/count-complete-tree-nodes/
 *
 * Given the root of a complete binary tree, return the number of the nodes in the tree.
 * According to Wikipedia, every level, except possibly the last, is completely filled in
 * a complete binary tree, and all nodes in the last level are as far left as possible.
 * It can have between 1 and 2h nodes inclusive at the last level h. Design an algorithm
 * that runs in less than O(n) time complexity.
 * The tree is guaranteed to be complete.
 */
auto CountCompleteTreeNodes(const BinaryTree::Node::PointerType node) {
    if (not node) {
        return 0;
    }

    int left_height = 0;
    for (auto current = node; current; current = current->left) {
        ++left_height;
    }

    int right_height = 0;
    for (auto current = node; current; current = current->right) {
        ++right_height;
    }

    if (left_height == right_height) {
        return (1 << left_height) - 1;
    }

    return 1 + CountCompleteTreeNodes(node->left) + CountCompleteTreeNodes(node->right);
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
/**
 *      1
 *    /   \
 *   2     3
 *  / \   /
 * 4   5 6
 */
const auto SAMPLE4 = LevelOrderToBinaryTree( {
    1, 2, 3, 4, 5, 6
});
/**
 *     1
 *    / \
 *   2   3
 *    \
 *     5
 */
const auto SAMPLE5 = BinaryTreeDeletion_Subtree(CloneBinaryTree(SAMPLE1), 4).GetRoot();
/**
 *      1
 *    /   \
 *   2     3
 *        / \
 *       6   7
 */
const auto SAMPLE6 = LevelOrderToBinaryTree( {
    1, 2, 3, SENTINEL, SENTINEL, 6, 7
});


SIMPLE_BENCHMARK(isCompleteBinaryTree, Sample1, SAMPLE1);
SIMPLE_BENCHMARK(isCompleteBinaryTree, Sample6, SAMPLE6);

SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE4, true, SAMPLE4);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE5, false, SAMPLE5);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE6, false, SAMPLE6);


THE_BENCHMARK(CountCompleteTreeNodes, SAMPLE3);

SIMPLE_TEST(CountCompleteTreeNodes, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(CountCompleteTreeNodes, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(CountCompleteTreeNodes, TestSAMPLE3, 3, SAMPLE3);
SIMPLE_TEST(CountCompleteTreeNodes, TestSAMPLE4, 6, SAMPLE4);
