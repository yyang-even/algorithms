#include "common_header.h"

#include "single_order_to_binary_tree.h"


namespace {

using ArrayType = std::vector<int>;

/** Find Duplicate Subtrees
 *
 * @reference   https://leetcode.com/problems/find-duplicate-subtrees/
 *
 * Given the root of a binary tree, return all duplicate subtrees.
 * For each kind of duplicate subtrees, you only need to return the root node of any one of them.
 * Two trees are duplicate if they have the same structure with the same node values.
 */
std::size_t
FindDuplicateSubtrees(const BinaryTree::Node::PointerType node,
                      std::unordered_map<std::string, std::pair<std::size_t, int>> &hash,
                      ArrayType &result) {
    if (not node) {
        return 0;
    }

    const auto triplet = std::to_string(FindDuplicateSubtrees(node->left, hash, result)) + ',' +
                         std::to_string(node->value) + ',' +
                         std::to_string(FindDuplicateSubtrees(node->right, hash, result));

    const auto [iter, inserted] = hash.emplace(triplet, std::pair(hash.size() + 1, 1));
    if (not inserted and (iter->second.second)++ == 1) {
        result.push_back(node->value);
    }

    return iter->second.first;
}

auto FindDuplicateSubtrees(const BinaryTree::Node::PointerType root) {
    std::unordered_map<std::string, std::pair<std::size_t, int>> hash;
    ArrayType result;
    FindDuplicateSubtrees(root, hash, result);

    return result;
}

} //namespace


/**
 *     1
 *    / \
 *   2   3
 *  /   / \
 * 4   2   4
 *    /
 *   4
 */
const auto SAMPLE1 = LevelOrderToBinaryTree(
    {1, 2, 3, 4, SENTINEL, 2, 4, SENTINEL, SENTINEL, SENTINEL, SENTINEL, 4});
const ArrayType EXPECTED1 = {4, 2};

const auto SAMPLE2 = LevelOrderToBinaryTree({2, 1, 1});
const ArrayType EXPECTED2 = {1};

/**
 *     2
 *    / \
 *   2   2
 *  /   /
 * 3   3
 */
const auto SAMPLE3 = LevelOrderToBinaryTree({2, 2, 2, 3, SENTINEL, 3, SENTINEL});
const ArrayType EXPECTED3 = {3, 2};

/**
 *      0
 *     / \
 *    0   0
 *   /     \
 *  0       0
 *           \
 *            0
 */
const auto SAMPLE4 = LevelOrderToBinaryTree({0,
                                             0,
                                             0,
                                             0,
                                             SENTINEL,
                                             SENTINEL,
                                             0,
                                             SENTINEL,
                                             SENTINEL,
                                             SENTINEL,
                                             SENTINEL,
                                             SENTINEL,
                                             SENTINEL,
                                             SENTINEL,
                                             0});
const ArrayType EXPECTED4 = {0};


THE_BENCHMARK(FindDuplicateSubtrees, SAMPLE1);

SIMPLE_TEST(FindDuplicateSubtrees, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(FindDuplicateSubtrees, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(FindDuplicateSubtrees, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(FindDuplicateSubtrees, TestSAMPLE4, EXPECTED4, SAMPLE4);
