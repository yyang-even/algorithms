#include "common_header.h"

#include "binary_tree.h"
#include "clone_binary_tree.h"
#include "compare_binary_trees.h"


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
static inline auto MakeTheSampleTree() {
    const BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 0);
    auto &right_child = *SetRightChild(root, 0);
    SetLeftChild(left_child, 0);
    SetRightChild(left_child, 0);
    SetRightChild(right_child, 1);

    return binary_tree;
}

/**
 *     1
 *      \
 *       0
 *        \
 *         1
 */
static inline auto MakeTheExpectedTree() {
    const BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    auto &right_child = *SetRightChild(root, 0);
    SetRightChild(right_child, 1);

    return binary_tree;
}


const auto SAMPLE1 = MakeTheSampleTree().GetRoot();
const auto EXPECTED1 = MakeTheExpectedTree().GetRoot();


THE_BENCHMARK(PruneTree, CloneBinaryTree(SAMPLE1).GetRoot());

SIMPLE_TEST(PruneTree, TestSAMPLE1, EXPECTED1, CloneBinaryTree(SAMPLE1).GetRoot());
SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true, EXPECTED1,
            PruneTree(CloneBinaryTree(SAMPLE1).GetRoot()));
