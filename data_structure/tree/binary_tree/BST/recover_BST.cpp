#include "common_header.h"

#include "binary_search_tree.h"

#include "data_structure/tree/binary_tree/clone_binary_tree.h"
#include "data_structure/tree/binary_tree/compare_binary_trees.h"
#include "data_structure/tree/binary_tree/single_order_to_binary_tree.h"


namespace {

/** Recover Binary Search Tree
 *
 * @reference   https://leetcode.com/problems/recover-binary-search-tree/
 *
 * You are given the root of a binary search tree (BST), where the values of exactly two nodes of the
 * tree were swapped by mistake. Recover the tree without changing its structure.
 * Follow up: A solution using O(n) space is pretty straight-forward. Could you devise a constant O(1)
 * space solution?
 */
void RecoverBST(const BinaryTree::Node::PointerType node,
                BinaryTree::Node::PointerType &prev,
                BinaryTree::Node::PointerType &first,
                BinaryTree::Node::PointerType &second) {
    if (not node) {
        return;
    }

    RecoverBST(node->left, prev, first, second);

    if (not first and prev->value > node->value) {
        first = prev;
    }
    if (first and prev->value > node->value) {
        second = node;
    }
    prev = node;

    RecoverBST(node->right, prev, first, second);
}

auto RecoverBST(const BinaryTree::Node::PointerType root) {
    BinaryTree::Node::PointerType first;
    BinaryTree::Node::PointerType second;
    auto prev = std::make_shared<BinaryTree::Node>(INT_MIN);
    RecoverBST(root, prev, first, second);

    std::swap(first->value, second->value);

    return root;
}

} //namespace


/**
 *     1
 *    /
 *   3
 *    \
 *     2
 */
const auto SAMPLE1 = LevelOrderToBinaryTree({1, 3, SENTINEL, SENTINEL, 2});
/**
 *     3
 *    /
 *   1
 *    \
 *     2
 */
const auto EXPECTED1 = LevelOrderToBinaryTree({3, 1, SENTINEL, SENTINEL, 2});

/**
 *     3
 *    / \
 *   1   4
 *      /
 *     2
 */
const auto SAMPLE2 = LevelOrderToBinaryTree({3, 1, 4, SENTINEL, SENTINEL, 2});
/**
 *     2
 *    / \
 *   1   4
 *      /
 *     3
 */
const auto EXPECTED2 = LevelOrderToBinaryTree({2, 1, 4, SENTINEL, SENTINEL, 3});


THE_BENCHMARK(RecoverBST, CloneBinaryTree(SAMPLE1).GetRoot());

SIMPLE_TEST(areIdenticalTrees,
            TestSAMPLE1,
            true,
            EXPECTED1,
            RecoverBST(CloneBinaryTree(SAMPLE1).GetRoot()));
SIMPLE_TEST(areIdenticalTrees,
            TestSAMPLE2,
            true,
            EXPECTED2,
            RecoverBST(CloneBinaryTree(SAMPLE2).GetRoot()));
