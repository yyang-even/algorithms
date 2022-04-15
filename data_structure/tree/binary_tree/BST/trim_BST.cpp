#include "common_header.h"

#include "binary_search_tree.h"

#include "data_structure/tree/binary_tree/clone_binary_tree.h"
#include "data_structure/tree/binary_tree/compare_binary_trees.h"
#include "data_structure/tree/binary_tree/single_order_to_binary_tree.h"


namespace {

/** Trim a Binary Search Tree
 *
 * @reference   https://leetcode.com/problems/trim-a-binary-search-tree/
 *
 * Given the root of a binary search tree and the lowest and highest boundaries as low
 * and high, trim the tree so that all its elements lies in [low, high]. Trimming the
 * tree should not change the relative structure of the elements that will remain in the
 * tree (i.e., any node's descendant should remain a descendant). It can be proven that
 * there is a unique answer.
 * Return the root of the trimmed binary search tree. Note that the root may change
 * depending on the given bounds.
 */
auto TrimBST(const BinaryTree::Node::PointerType root, const int low, const int high) {
    if (not root) {
        return root;
    }

    if (root->value < low) {
        return TrimBST(root->right, low, high);
    } else if (root->value > high) {
        return TrimBST(root->left, low, high);
    }

    root->left = TrimBST(root->left, low, high);
    root->right = TrimBST(root->right, low, high);
    return root;
}

}//namespace


/**
 *     1
 *    / \
 *   0   2
 */
const auto SAMPLE1 = LevelOrderToBinaryTree( {
    1, 0, 2
});
/**
 *     1
 *      \
 *       2
 */
const auto EXPECTED1 = LevelOrderToBinaryTree( {
    1, SENTINEL, 2
});

/**
 *     3
 *    / \
 *   0   4
 *    \
 *     2
 *    /
 *   1
 */
const auto SAMPLE2 = LevelOrderToBinaryTree( {
    3, 0, 4, SENTINEL, 2, SENTINEL, SENTINEL, SENTINEL, SENTINEL, 1
});
/**
 *     3
 *    /
 *   2
 *  /
 * 1
 */
const auto EXPECTED2 = LevelOrderToBinaryTree( {
    3, 2, SENTINEL, 1
});


THE_BENCHMARK(TrimBST, CloneBinaryTree(SAMPLE1).GetRoot(), 1, 2);

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true, EXPECTED1,
            TrimBST(CloneBinaryTree(SAMPLE1).GetRoot(), 1, 2));
SIMPLE_TEST(areIdenticalTrees, TestSAMPLE2, true, EXPECTED2,
            TrimBST(CloneBinaryTree(SAMPLE2).GetRoot(), 1, 3));
