#include "common_header.h"

#include "binary_tree.h"


namespace {

/** Count Good Nodes in Binary Tree
 *
 * @reference   https://leetcode.com/problems/count-good-nodes-in-binary-tree/
 *
 * Given a binary tree root, a node X in the tree is named good if in the path from root
 * to X there are no nodes with a value greater than X. Return the number of good nodes
 * in the binary tree.
 */
int GoodNodes(const BinaryTree::Node::PointerType node, int max) {
    if (not node) {
        return 0;
    }

    bool is_good = false;
    if (node->value >= max) {
        is_good = true;
        max = node->value;
    }

    return is_good + GoodNodes(node->left, max) + GoodNodes(node->right, max);
}

inline auto GoodNodes(const BinaryTree::Node::PointerType root) {
    return GoodNodes(root, INT_MIN);
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


THE_BENCHMARK(GoodNodes, SAMPLE1);

SIMPLE_TEST(GoodNodes, TestSAMPLE1, 5, SAMPLE1);
