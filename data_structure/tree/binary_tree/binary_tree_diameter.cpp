#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_height.h"


namespace {

/** Diameter of Binary Tree
 *
 * @reference   https://leetcode.com/problems/diameter-of-binary-tree/
 * @reference   Diameter of a Binary Tree
 *              https://www.geeksforgeeks.org/diameter-of-a-binary-tree/
 *
 * Given the root of a binary tree, return the length of the diameter of the tree. The
 * diameter of a binary tree is the length of the longest path between any two nodes in
 * a tree. This path may or may not pass through the root. The length of a path between
 * two nodes is represented by the number of edges between them.
 */
auto Diameter(const BinaryTree::Node::PointerType node, int &height) {
    if (not node) {
        height = 0;
        return 0;
    }

    int left_height = 0;
    int right_height = 0;

    const auto sub_diameter = std::max(Diameter(node->left, left_height),
                                       Diameter(node->right, right_height));
    height = std::max(left_height, right_height) + 1;

    return std::max(left_height + right_height, sub_diameter);
}

inline auto Diameter(const BinaryTree::Node::PointerType root) {
    int height = 0;

    return Diameter(root, height);
}


/**
 * @reference   Diameter of a Binary Tree in O(n) [A new method]
 *              https://www.geeksforgeeks.org/diameter-of-a-binary-tree-in-on-a-new-method/
 */
auto Diameter_Height(const BinaryTree::Node::PointerType node, int &diameter) {
    if (not node) {
        return 0;
    }

    const auto left_height = Diameter_Height(node->left, diameter);
    const auto right_height = Diameter_Height(node->right, diameter);

    diameter = std::max(diameter, left_height + right_height);
    return std::max(left_height, right_height) + 1;
}

inline auto Diameter_Height(const BinaryTree::Node::PointerType root) {
    int result = 0;
    Diameter_Height(root, result);
    return result;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


THE_BENCHMARK(Diameter, SAMPLE1);

SIMPLE_TEST(Diameter, TestSAMPLE1, 3, SAMPLE1);


THE_BENCHMARK(Diameter_Height, SAMPLE1);

SIMPLE_TEST(Diameter_Height, TestSAMPLE1, 3, SAMPLE1);
