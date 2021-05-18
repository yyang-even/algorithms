#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_deletion.h"
#include "clone_binary_tree.h"
#include "complete_binary_tree.h"


namespace {

/** Check whether a binary tree is a complete tree or not | Set 2 (Recursive Solution)
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-binary-tree-complete-not-set-2-recursive-solution/
 */

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
static inline auto MakeCompleteTree4() {
    const auto binary_tree = CloneBinaryTree(SAMPLE1);
    auto &right_child_of_root = *(binary_tree.GetRoot()->right);
    SetLeftChild(right_child_of_root, 6);

    return binary_tree;
}
const auto SAMPLE4 = MakeCompleteTree4().GetRoot();
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
static inline auto MakeIncompleteTree6() {
    const auto binary_tree = CloneBinaryTree(SAMPLE3);
    auto &right_child_of_root = *(binary_tree.GetRoot()->right);
    SetLeftChild(right_child_of_root, 6);
    SetRightChild(right_child_of_root, 7);

    return binary_tree;
}
const auto SAMPLE6 = MakeIncompleteTree6().GetRoot();


SIMPLE_BENCHMARK(isCompleteBinaryTree, Sample1, SAMPLE1);
SIMPLE_BENCHMARK(isCompleteBinaryTree, Sample6, SAMPLE6);

SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE4, true, SAMPLE4);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE5, false, SAMPLE5);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE6, false, SAMPLE6);
