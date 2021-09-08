#include "common_header.h"

#include "binary_search_tree.h"


namespace {

/**
 * @reference   Range Sum of BST
 *              https://leetcode.com/problems/range-sum-of-bst/
 *
 * Given the root node of a binary search tree and two integers low and high, return the
 * sum of values of all nodes with a value in the inclusive range [low, high].
 */
auto RangeSumBST(const BinaryTree::Node::PointerType node,
                 const int low, const int high) {
    if (not node) {
        return 0;
    }

    if (node->value < low) {
        return RangeSumBST(node->right, low, high);
    } else if (node->value > high) {
        return RangeSumBST(node->left, low, high);
    } else
        return node->value +
               RangeSumBST(node->left, low, high) +
               RangeSumBST(node->right, low, high);
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST();


THE_BENCHMARK(RangeSumBST, SAMPLE1, 0, 10);

SIMPLE_TEST(RangeSumBST, TestSAMPLE1, 15, SAMPLE1, 0, 10);
SIMPLE_TEST(RangeSumBST, TestSAMPLE2, 1, SAMPLE1, 1, 1);
SIMPLE_TEST(RangeSumBST, TestSAMPLE3, 5, SAMPLE1, 5, 5);
SIMPLE_TEST(RangeSumBST, TestSAMPLE4, 12, SAMPLE1, 3, 5);
