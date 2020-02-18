#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_deletion.h"
#include "clone_binary_tree.h"


namespace {

/** Check whether a binary tree is a full binary tree or not
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-binary-tree-full-binary-tree-not/
 *
 * A full binary tree is defined as a binary tree in which all nodes have either zero or
 * two child nodes. Conversely, there is no node in a full binary tree, which has one
 * child node.
 */
auto isFullBinaryTree(const BinaryTree::Node::PointerType node) {
    if (not node) {
        return true;
    }

    const auto node_type = CheckType(*node);
    if (node_type == BinaryTree::Node::Type::leaf) {
        return true;
    }

    if (node_type == BinaryTree::Node::Type::full) {
        return isFullBinaryTree(node->left) and isFullBinaryTree(node->right);
    }

    return false;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
const auto EMPTY_TREE = BinaryTree {} .GetRoot();
const auto SAMPLE2 = BinaryTreeDeletion_Subtree(CloneBinaryTree(SAMPLE1), 5).GetRoot();


SIMPLE_BENCHMARK(isFullBinaryTree, SAMPLE1);

SIMPLE_TEST(isFullBinaryTree, TestSAMPLE0, true, EMPTY_TREE);
SIMPLE_TEST(isFullBinaryTree, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isFullBinaryTree, TestSAMPLE2, false, SAMPLE2);
