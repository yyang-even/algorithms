#include "common_header.h"

#include "binary_tree.h"
#include "single_order_to_binary_tree.h"


namespace {

using ArrayType = std::vector<std::vector<int>>;
using MapType = std::map<int, std::map<int, std::multiset<int>>>;

/** Vertical Order Traversal of a Binary Tree
 *
 * @reference   https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/
 *
 * Given the root of a binary tree, calculate the vertical order traversal of the binary tree.
 * For each node at position (row, col), its left and right children will be at positions (row + 1, col
 * - 1) and (row + 1, col + 1) respectively. The root of the tree is at (0, 0).
 * The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column
 * index starting from the leftmost column and ending on the rightmost column. There may be multiple
 * nodes in the same row and same column. In such a case, sort these nodes by their values.
 * Return the vertical order traversal of the binary tree.
 */
void VerticalTraversal(const BinaryTree::Node::PointerType node,
                       const int x,
                       const int y,
                       MapType &row_col_val_map) {
    if (node) {
        row_col_val_map[x][y].insert(node->value);
        VerticalTraversal(node->left, x - 1, y + 1, row_col_val_map);
        VerticalTraversal(node->right, x + 1, y + 1, row_col_val_map);
    }
}

auto VerticalTraversal(const BinaryTree::Node::PointerType root) {
    MapType row_col_val_map;
    VerticalTraversal(root, 0, 0, row_col_val_map);

    ArrayType result;
    for (const auto &[x, col_val_map] : row_col_val_map) {
        result.emplace_back();
        for (const auto &[y, sorted_values] : col_val_map) {
            result.back().insert(
                result.back().cend(), sorted_values.cbegin(), sorted_values.cend());
        }
    }

    return result;
}

} //namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
const ArrayType EXPECTED1 = {{4}, {2}, {1, 5}, {3}};

/**
 *     3
 *    / \
 *   9   20
 *      /  \
 *     15   7
 */
const auto SAMPLE2 = LevelOrderToBinaryTree({3, 9, 20, SENTINEL, SENTINEL, 15, 7});
const ArrayType EXPECTED2 = {{9}, {3, 15}, {20}, {7}};

/**
 *       1
 *    /    \
 *   2      3
 *  / \    / \
 * 4   5  6   7
 */
const auto SAMPLE3 = LevelOrderToBinaryTree({1, 2, 3, 4, 5, 6, 7});
const ArrayType EXPECTED3 = {{4}, {2}, {1, 5, 6}, {3}, {7}};

/**
 *       1
 *    /    \
 *   2      3
 *  / \    / \
 * 4   6  5   7
 */
const auto SAMPLE4 = LevelOrderToBinaryTree({1, 2, 3, 4, 6, 5, 7});
const ArrayType EXPECTED4 = {{4}, {2}, {1, 5, 6}, {3}, {7}};


THE_BENCHMARK(VerticalTraversal, SAMPLE1);

SIMPLE_TEST(VerticalTraversal, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(VerticalTraversal, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(VerticalTraversal, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(VerticalTraversal, TestSAMPLE4, EXPECTED4, SAMPLE4);
