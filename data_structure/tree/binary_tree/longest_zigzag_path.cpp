#include "common_header.h"

#include "binary_tree.h"
#include "single_order_to_binary_tree.h"


namespace {

/** Longest ZigZag Path in a Binary Tree
 *
 * @reference   https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/
 *
 * You are given the root of a binary tree.
 * A ZigZag path for a binary tree is defined as follow:
 *  Choose any node in the binary tree and a direction (right or left).
 *  If the current direction is right, move to the right child of the current node; otherwise, move to
 *  the left child.
 *  Change the direction from right to left or from left to right.
 *  Repeat the second and third steps until you can't move in the tree.
 * Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).
 * Return the longest ZigZag path contained in that tree.
 */
void LongestZigZagPath(const BinaryTree::Node::PointerType node,
                       const int left,
                       const int right,
                       int &result) {
    if (not node) {
        return;
    }

    result = std::max(result, std::max(left, right));

    if (node->left) {
        LongestZigZagPath(node->left, right + 1, 0, result);
    }

    if (node->right) {
        LongestZigZagPath(node->right, 0, left + 1, result);
    }
}

auto LongestZigZagPath(const BinaryTree::Node::PointerType root) {
    int result = 0;
    LongestZigZagPath(root, 0, 0, result);

    return result;
}

} //namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
const auto SAMPLE2 = LevelOrderToBinaryTree({1});


THE_BENCHMARK(LongestZigZagPath, SAMPLE1);

SIMPLE_TEST(LongestZigZagPath, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(LongestZigZagPath, TestSAMPLE2, 0, SAMPLE2);
