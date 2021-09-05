#include "common_header.h"

#include "binary_tree.h"
#include "single_order_to_binary_tree.h"


namespace {

/** Distribute Coins in Binary Tree
 *
 * @reference   https://leetcode.com/problems/distribute-coins-in-binary-tree/
 *
 * You are given the root of a binary tree with n nodes where each node in the tree has
 * node.val coins. There are n coins in total throughout the whole tree. In one move, we
 * may choose two adjacent nodes and move one coin from one node to another. A move may
 * be from parent to child, or from child to parent. Return the minimum number of moves
 * required to make every node have exactly one coin.
 */
auto DistributeCoins(const BinaryTree::Node::PointerType node, int &result) {
    if (not node) {
        return 0;
    }

    const auto left = DistributeCoins(node->left, result);
    const auto right = DistributeCoins(node->right, result);

    result += std::abs(left) + std::abs(right);
    return node->value + left + right - 1;
}

auto DistributeCoins(const BinaryTree::Node::PointerType root) {
    int result = 0;
    DistributeCoins(root, result);

    return result;
}

}//namespace


/**
 *   3
 *  / \
 * 0   0
 */
const auto SAMPLE1 = LevelOrderToBinaryTree( {
    3, 0, 0
});

/**
 *   0
 *  / \
 * 3   0
 */
const auto SAMPLE2 = LevelOrderToBinaryTree( {
    0, 3, 0
});

/**
 *   1
 *  / \
 * 0   2
 */
const auto SAMPLE3 = LevelOrderToBinaryTree( {
    1, 0, 2
});

/**
 *   1
 *  / \
 * 0   0
 *  \
 *   3
 */
const auto SAMPLE4 = LevelOrderToBinaryTree( {
    1, 0, 0, SENTINEL, 3
});


THE_BENCHMARK(DistributeCoins, SAMPLE1);

SIMPLE_TEST(DistributeCoins, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(DistributeCoins, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(DistributeCoins, TestSAMPLE3, 2, SAMPLE3);
SIMPLE_TEST(DistributeCoins, TestSAMPLE4, 4, SAMPLE4);
