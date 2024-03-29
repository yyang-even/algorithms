#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_deletion.h"
#include "binary_tree_traversals.h"
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
auto isFullBinaryTree_Recursive(const BinaryTree::Node::PointerType node) {
    if (not node) {
        return true;
    }

    const auto node_type = CheckType(*node);
    if (node_type == BinaryTree::Node::Type::leaf) {
        return true;
    }

    if (node_type == BinaryTree::Node::Type::full) {
        return isFullBinaryTree_Recursive(node->left) and
               isFullBinaryTree_Recursive(node->right);
    }

    return false;
}


/**
 * @reference   Check whether a binary tree is a full binary tree or not | Iterative Approach
 *              https://www.geeksforgeeks.org/check-whether-binary-tree-full-binary-tree-not-iterative-approach/
 */
inline auto isFullBinaryTree_Iterative(const BinaryTree::Node::PointerType root_node) {
    return LevelOrderTraversal_LevelAware_Helper(root_node,
    [](const auto & node) {
        const auto node_type = CheckType(node);

        return node_type == BinaryTree::Node::Type::leaf or
               node_type == BinaryTree::Node::Type::full;
    }, {});
}


/**
 * @reference   Find All the Lonely Nodes
 *              https://leetcode.ca/all/1469.html
 *
 * In a binary tree, a lonely node is a node that is the only child of its parent node.
 * The root of the tree is not lonely because it does not have a parent node.
 * Given the root of a binary tree, return an array containing the values of all lonely
 * nodes in the tree. Return the list in any order.
 */

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
const auto EMPTY_TREE = BinaryTree {} .GetRoot();
const auto SAMPLE2 = BinaryTreeDeletion_Subtree(CloneBinaryTree(SAMPLE1), 5).GetRoot();


THE_BENCHMARK(isFullBinaryTree_Recursive, SAMPLE1);

SIMPLE_TEST(isFullBinaryTree_Recursive, TestSAMPLE0, true, EMPTY_TREE);
SIMPLE_TEST(isFullBinaryTree_Recursive, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isFullBinaryTree_Recursive, TestSAMPLE2, false, SAMPLE2);


THE_BENCHMARK(isFullBinaryTree_Iterative, SAMPLE1);

SIMPLE_TEST(isFullBinaryTree_Iterative, TestSAMPLE0, true, EMPTY_TREE);
SIMPLE_TEST(isFullBinaryTree_Iterative, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isFullBinaryTree_Iterative, TestSAMPLE2, false, SAMPLE2);
