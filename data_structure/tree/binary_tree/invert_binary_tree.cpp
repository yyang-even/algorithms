#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_traversals.h"
#include "clone_binary_tree.h"
#include "compare_binary_trees.h"


namespace {

/** Invert Binary Tree
 *
 * @reference   https://leetcode.com/problems/invert-binary-tree/
 *
 * Given the root of a binary tree, invert the tree, and return its root.
 */
inline void
InvertBinaryTree_Recursive_Helper(const BinaryTree::Node::PointerType node) {
    if (node) {
        std::swap(node->left, node->right);
        InvertBinaryTree_Recursive_Helper(node->left);
        InvertBinaryTree_Recursive_Helper(node->right);
    }
}

inline auto
InvertBinaryTree_Recursive(const BinaryTree::Node::PointerType root) {
    InvertBinaryTree_Recursive_Helper(root);

    return root;
}


inline auto
InvertBinaryTree_Iterative(const BinaryTree::Node::PointerType root) {
    LevelOrderTraversal_LevelAware_Helper(root, [](auto & node) {
        std::swap(node.left, node.right);
        return true;
    });
    return root;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


THE_BENCHMARK(InvertBinaryTree_Recursive, CloneBinaryTree(SAMPLE1).GetRoot());
THE_BENCHMARK(InvertBinaryTree_Iterative, CloneBinaryTree(SAMPLE1).GetRoot());

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true,
            InvertBinaryTree_Recursive(CloneBinaryTree(SAMPLE1).GetRoot()),
            InvertBinaryTree_Iterative(CloneBinaryTree(SAMPLE1).GetRoot()));
