#include "common_header.h"

#include "binary_tree.h"
#include "clone_binary_tree.h"


namespace {

/** Maximum Product of Splitted Binary Tree
 *
 * @reference   https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/
 *
 * Given the root of a binary tree, split the binary tree into two subtrees by removing
 * one edge such that the product of the sums of the subtrees is maximized. Return the
 * maximum product of the sums of the two subtrees. Since the answer may be too large,
 * return it modulo 10^9 + 7. Note that you need to maximize the answer before taking the
 * mod and not after taking it.
 */
int sum(const BinaryTree::Node::PointerType node) {
    if (not node) {
        return 0;
    }

    return node->value += sum(node->left) + sum(node->right);
}

void MaxProductOfSplittedBinaryTree(const BinaryTree::Node::PointerType node,
                                    const long total, long &result) {
    if (node) {
        result = std::max(result, (total - node->value) * node->value);
        MaxProductOfSplittedBinaryTree(node->left, total, result);
        MaxProductOfSplittedBinaryTree(node->right, total, result);
    }

}

int MaxProductOfSplittedBinaryTree(const BinaryTree::Node::PointerType root) {
    assert(root);

    sum(root);
    long result = 0;
    MaxProductOfSplittedBinaryTree(root, root->value, result);
    return result % LARGE_PRIME;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


THE_BENCHMARK(MaxProductOfSplittedBinaryTree, CloneBinaryTree(SAMPLE1).GetRoot());

SIMPLE_TEST(MaxProductOfSplittedBinaryTree, TestSAMPLE1, 50,
            CloneBinaryTree(SAMPLE1).GetRoot());
