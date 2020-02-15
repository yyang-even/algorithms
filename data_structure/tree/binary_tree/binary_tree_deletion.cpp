#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_deletion.h"
#include "clone_binary_tree.h"
#include "compare_binary_trees.h"


namespace {

/** Deletion in a Binary Tree
 *
 * @reference   https://www.geeksforgeeks.org/deletion-binary-tree/
 *
 * Given a binary tree, delete a node from it by making sure that tree shrinks from
 * the bottom (i.e. the deleted node is replaced by bottom most and rightmost node).
 */
auto BinaryTreeDeletion_BottomShrink(BinaryTree binary_tree, const BinaryTree::Node::ValueType x) {
    std::queue<BinaryTree::Node::PointerType *> remaining_nodes;
    auto *last_visited_node = &binary_tree.GetMutableRoot();
    if (*last_visited_node) {
        remaining_nodes.push(last_visited_node);
    }

    BinaryTree::Node::PointerType key_node;
    while (not remaining_nodes.empty()) {
        last_visited_node = remaining_nodes.front();
        auto &current_node = *last_visited_node;
        remaining_nodes.pop();

        if (current_node->value == x) {
            key_node = current_node;
        }

        if (current_node->left) {
            remaining_nodes.push(&current_node->left);
        }
        if (current_node->right) {
            remaining_nodes.push(&current_node->right);
        }
    }

    if (key_node) {
        if (key_node != *last_visited_node) {
            key_node->value = (*last_visited_node)->value;
        }
        *last_visited_node = nullptr;
    }

    return binary_tree;
}

}//namespace


const auto SAMPLE0 = MakeTheSampleCompleteTree().GetRoot();
const auto EMPTY_TREE = BinaryTree {} .GetRoot();
const auto SAMPLE1_LHS = BinaryTreeDeletion_Subtree(CloneBinaryTree(SAMPLE0), 5).GetRoot();
const auto SAMPLE1_RHS = BinaryTreeDeletion_BottomShrink(CloneBinaryTree(SAMPLE0), 5).GetRoot();
const auto SAMPLE2_LHS = BinaryTreeDeletion_BottomShrink(
                             CloneBinaryTree(SAMPLE0), SAMPLE0->value).GetRoot();
const auto SAMPLE2_RHS = SetNode(CloneBinaryTree(BinaryTreeDeletion_Subtree(
                                     CloneBinaryTree(SAMPLE0), 5).GetRoot()).GetRoot(), 5);


SIMPLE_BENCHMARK(BinaryTreeDeletion_Subtree, CloneBinaryTree(SAMPLE0), 4);


SIMPLE_BENCHMARK(BinaryTreeDeletion_BottomShrink, CloneBinaryTree(SAMPLE0), 4);

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true, SAMPLE1_LHS, SAMPLE1_RHS);
SIMPLE_TEST(areIdenticalTrees, TestSAMPLE2, true, SAMPLE2_LHS, SAMPLE2_RHS);
