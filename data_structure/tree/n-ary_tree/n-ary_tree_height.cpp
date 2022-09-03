#include "common_header.h"

#include "n-ary_tree_traversal.h"


namespace {

/** Maximum Depth of N-ary Tree
 *
 * @reference   https://leetcode.com/problems/maximum-depth-of-n-ary-tree/
 *
 * Given a n-ary tree, find its maximum depth. The maximum depth is the number of nodes
 * along the longest path from the root node down to the farthest leaf node. Nary-Tree
 * input serialization is represented in their level order traversal, each group of
 * children is separated by the null value (See examples).
 */
auto Height(const n_ary_tree::array_representation::Node::PointerType root) {
    if (not root) {
        return 0;
    }

    int height = 0;
    for (const auto &node : root->children) {
        height = std::max(height, Height(node));
    }

    return height + 1;
}

} //namespace


const auto SAMPLE1 = MakeTheSampleTree<n_ary_tree::array_representation::Node>();


THE_BENCHMARK(Height, SAMPLE1);

SIMPLE_TEST(Height, TestSAMPLE1, 3, SAMPLE1);
