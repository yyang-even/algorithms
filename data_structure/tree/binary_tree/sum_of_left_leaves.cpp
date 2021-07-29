#include "common_header.h"

#include "binary_tree.h"


namespace {

/** Sum of Left Leaves
 *
 * @reference   https://leetcode.com/problems/sum-of-left-leaves/
 *
 * Given the root of a binary tree, return the sum of all left leaves.
 */
void SumOfLeftLeaves(const BinaryTree::Node::PointerType node, int &sum) {
    if (not node) {
        return;
    }

    if (node->left and (not node->left->right and not node->left->left)) {
        sum += node->left->value;
    }

    SumOfLeftLeaves(node->left, sum);
    SumOfLeftLeaves(node->right, sum);
}

inline auto SumOfLeftLeaves(const BinaryTree::Node::PointerType root) {
    int sum = 0;
    SumOfLeftLeaves(root, sum);
    return sum;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


THE_BENCHMARK(SumOfLeftLeaves, SAMPLE1);

SIMPLE_TEST(SumOfLeftLeaves, TestSAMPLE1, 4, SAMPLE1);
