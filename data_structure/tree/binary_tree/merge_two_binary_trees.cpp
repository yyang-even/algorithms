#include "common_header.h"

#include "binary_tree.h"
#include "clone_binary_tree.h"
#include "compare_binary_trees.h"


namespace {

/** Merge Two Binary Trees
 *
 * @reference   https://leetcode.com/problems/merge-two-binary-trees/
 *
 * You are given two binary trees root1 and root2. Imagine that when you put one of them
 * to cover the other, some nodes of the two trees are overlapped while the others are
 * not. You need to merge the two trees into a new binary tree. The merge rule is that if
 * two nodes overlap, then sum node values up as the new value of the merged node.
 * Otherwise, the NOT null node will be used as the node of the new tree. Return the
 * merged tree. Note: The merging process must start from the root nodes of both trees.
 */
auto MergeTrees(const BinaryTree::Node::PointerType one,
                const BinaryTree::Node::PointerType another) {
    if (not one) {
        return another;
    }

    if (not another) {
        return one;
    }

    one->value += another->value;
    one->left = MergeTrees(one->left, another->left);
    one->right = MergeTrees(one->right, another->right);

    return one;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();

/**
 *     1
 *    / \
 *   2   3
 *      /
 *     6
 */
static inline auto MakeTheSample2() {
    const BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    SetLeftChild(root, 2);
    auto &right_child = *SetRightChild(root, 3);
    SetLeftChild(right_child, 6);

    return binary_tree;
}

const auto SAMPLE2 = MakeTheSample2().GetRoot();

/**
 *      2
 *    /   \
 *   4     6
 *  / \   /
 * 4   5 6
 */
static inline auto MakeTheExpected() {
    const BinaryTree binary_tree{2};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 4);
    auto &right_child = *SetRightChild(root, 6);
    SetLeftChild(left_child, 4);
    SetRightChild(left_child, 5);
    SetLeftChild(right_child, 6);

    return binary_tree;
}

const auto EXPECTED1 = MakeTheExpected().GetRoot();


THE_BENCHMARK(MergeTrees, CloneBinaryTree(SAMPLE1).GetRoot(),
              CloneBinaryTree(SAMPLE2).GetRoot());

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true, EXPECTED1,
            MergeTrees(CloneBinaryTree(SAMPLE1).GetRoot(),
                       CloneBinaryTree(SAMPLE2).GetRoot()));
