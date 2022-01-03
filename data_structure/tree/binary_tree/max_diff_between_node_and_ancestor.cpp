#include "common_header.h"

#include "binary_tree.h"


namespace {

/** Maximum Difference Between Node and Ancestor
 *
 * @reference   https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/
 *
 * Given the root of a binary tree, find the maximum value v for which there exist
 * different nodes a and b where v = |a.val - b.val| and a is an ancestor of b. A node
 * a is an ancestor of b if either: any child of a is equal to b or any child of a is
 * an ancestor of b.
 */
auto MaxAncestorDiff(const BinaryTree::Node::PointerType node,
                     int maximum, int minimum) {
    if (not node) {
        return maximum - minimum;
    }

    maximum = std::max(maximum, node->value);
    minimum = std::min(minimum, node->value);

    const auto left = MaxAncestorDiff(node->left, maximum, minimum);
    const auto right = MaxAncestorDiff(node->right, maximum, minimum);

    return std::max(left, right);
}

inline auto MaxAncestorDiff(const BinaryTree::Node::PointerType root) {
    if (not root) {
        return 0;
    }
    return MaxAncestorDiff(root, root->value, root->value);
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


THE_BENCHMARK(MaxAncestorDiff, SAMPLE1);

SIMPLE_TEST(MaxAncestorDiff, TestSAMPLE1, 4, SAMPLE1);
