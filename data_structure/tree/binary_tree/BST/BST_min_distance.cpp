#include "common_header.h"

#include "binary_search_tree.h"

namespace {

/** Minimum Absolute Difference in BST
 *
 * @reference   https://leetcode.com/problems/minimum-absolute-difference-in-bst/
 * @reference   Minimum Distance Between BST Nodes
 *              https://leetcode.com/problems/minimum-distance-between-bst-nodes/
 *
 * Given the root of a Binary Search Tree (BST), return the minimum difference between
 * the values of any two different nodes in the tree.
 */
void MinDistance(const BinaryTree::Node::PointerType node, int &predecessor,
                 int &min_distance) {
    if (not node) {
        return;
    }

    MinDistance(node->left, predecessor, min_distance);

    min_distance = std::min(min_distance, node->value - predecessor);
    predecessor = node->value;

    MinDistance(node->right, predecessor, min_distance);
}

inline auto MinDistance(const BinaryTree::Node::PointerType root) {
    int predecessor = -1000000;
    int result = INT_MAX;
    MinDistance(root, predecessor, result);

    return result;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();


THE_BENCHMARK(MinDistance, SAMPLE1);

SIMPLE_TEST(MinDistance, TestSAMPLE1, 1, SAMPLE1);
