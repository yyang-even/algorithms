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
 * Given the root of a binary tree, return the length of the diameter of the tree.
 * The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This
 * path may or may not pass through the root.
 * The length of a path between two nodes is represented by the number of edges between them.
 */
auto Diameter(const BinaryTree::Node::PointerType node, int &height) {
    if (not node) {
        height = 0;
        return 0;
    }

    int left_height = 0;
    int right_height = 0;

    const auto sub_diameter =
        std::max(Diameter(node->left, left_height), Diameter(node->right, right_height));
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


/**
 * @reference   Binary Tree Tilt
 *              https://leetcode.com/problems/binary-tree-tilt/
 *
 * Given the root of a binary tree, return the sum of every tree node's tilt.
 * The tilt of a tree node is the absolute difference between the sum of all left subtree node values
 * and all right subtree node values. If a node does not have a left child, then the sum of the left
 * subtree node values is treated as 0. The rule is similar if the node does not have a right child.
 */
auto Tilt(const BinaryTree::Node::PointerType node, int &tilt) {
    if (not node) {
        return 0;
    }

    const auto left_sum = Tilt(node->left, tilt);
    const auto right_sum = Tilt(node->right, tilt);

    tilt += std::abs(left_sum - right_sum);

    return left_sum + right_sum + node->value;
}

inline auto Tilt(const BinaryTree::Node::PointerType root) {
    int result = 0;
    Tilt(root, result);
    return result;
}


/**
 * @reference   Count Nodes Equal to Average of Subtree
 *              https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/
 *
 * Given the root of a binary tree, return the number of nodes where the value of the node is equal to
 * the average of the values in its subtree.
 * Note:
 *  The average of n elements is the sum of the n elements divided by n and rounded down to the nearest
 *  integer.
 *  A subtree of root is a tree consisting of root and all of its descendants.
 */


/**
 * @reference   Amount of Time for Binary Tree to Be Infected
 *              https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/
 *
 * You are given the root of a binary tree with unique values, and an integer start. At minute 0, an
 * infection starts from the node with value start.
 * Each minute, a node becomes infected if:
 *  The node is currently uninfected.
 *  The node is adjacent to an infected node.
 * Return the number of minutes needed for the entire tree to be infected.
 */
auto AmountOfTimeToInfect(const BinaryTree::Node::PointerType node,
                          const int start,
                          int &result) {
    if (not node) {
        return 0;
    }

    const int left_depth = AmountOfTimeToInfect(node->left, start, result);
    const int right_depth = AmountOfTimeToInfect(node->right, start, result);

    if (node->value == start) {
        result = std::max(left_depth, right_depth);
        return -1;
    } else if (left_depth >= 0 and right_depth >= 0) {
        return std::max(left_depth, right_depth) + 1;
    } else {
        const int depth = std::abs(left_depth) + std::abs(right_depth);
        result = std::max(result, depth);
        return std::min(left_depth, right_depth) - 1;
    }
}

auto AmountOfTimeToInfect(const BinaryTree::Node::PointerType node, const int start) {
    int result = 0;
    AmountOfTimeToInfect(node, start, result);
    return result;
}

} //namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


THE_BENCHMARK(Diameter, SAMPLE1);

SIMPLE_TEST(Diameter, TestSAMPLE1, 3, SAMPLE1);


THE_BENCHMARK(Diameter_Height, SAMPLE1);

SIMPLE_TEST(Diameter_Height, TestSAMPLE1, 3, SAMPLE1);


THE_BENCHMARK(Tilt, SAMPLE1);

SIMPLE_TEST(Tilt, TestSAMPLE1, 9, SAMPLE1);


THE_BENCHMARK(AmountOfTimeToInfect, SAMPLE1, 3);

SIMPLE_TEST(AmountOfTimeToInfect, TestSAMPLE1, 2, SAMPLE1, 1);
SIMPLE_TEST(AmountOfTimeToInfect, TestSAMPLE2, 2, SAMPLE1, 2);
SIMPLE_TEST(AmountOfTimeToInfect, TestSAMPLE3, 3, SAMPLE1, 3);
SIMPLE_TEST(AmountOfTimeToInfect, TestSAMPLE4, 3, SAMPLE1, 4);
SIMPLE_TEST(AmountOfTimeToInfect, TestSAMPLE5, 3, SAMPLE1, 5);
