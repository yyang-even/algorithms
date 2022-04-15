#include "common_header.h"

#include "binary_tree.h"
#include "clone_binary_tree.h"
#include "compare_binary_trees.h"
#include "single_order_to_binary_tree.h"


namespace {

/** Binary Tree Pruning
 *
 * @reference   https://leetcode.com/problems/binary-tree-pruning/
 *
 * Given the root of a binary tree, return the same tree where every subtree (of the
 * given tree) not containing a 1 has been removed. A subtree of a node node is node
 * plus every node that is a descendant of node.
 */
BinaryTree::Node::PointerType
PruneTree(BinaryTree::Node::PointerType node) {
    if (node) {
        node->left = PruneTree(node->left);
        node->right = PruneTree(node->right);

        if (node->value == 0 and not node->left and not node->right) {
            node = nullptr;
        }
    }

    return node;

}

}//namespace


/**
 *     1
 *    / \
 *   0   0
 *  / \   \
 * 0   0   1
 */
const auto SAMPLE1 = LevelOrderToBinaryTree( {
    1, 0, 0, 0, 0, SENTINEL, 1
});
/**
 *     1
 *      \
 *       0
 *        \
 *         1
 */
const auto EXPECTED1 = LevelOrderToBinaryTree( {
    1, SENTINEL, 0, SENTINEL, SENTINEL, SENTINEL, 1
});


THE_BENCHMARK(PruneTree, CloneBinaryTree(SAMPLE1).GetRoot());

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true, EXPECTED1,
            PruneTree(CloneBinaryTree(SAMPLE1).GetRoot()));
