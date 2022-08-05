#include "common_header.h"

#include "binary_search_tree.h"
#include "data_structure/tree/binary_tree/compare_binary_trees.h"
#include "data_structure/tree/binary_tree/single_order_to_binary_tree.h"


namespace {

/** Construct Binary Search Tree from Preorder Traversal
 *
 * @reference   https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/
 *
 * Given an array of integers preorder, which represents the preorder traversal of a BST (i.e.,
 * binary search tree), construct the tree and return its root.
 * It is guaranteed that there is always possible to find a binary search tree with the given
 * requirements for the given test cases.
 * A binary search tree is a binary tree where for every node, any descendant of Node.left has a
 * value strictly less than Node.val, and any descendant of Node.right has a value strictly greater
 * than Node.val.
 * A preorder traversal of a binary tree displays the value of the node first, then traverses
 * Node.left, then traverses Node.right.
 * All the values of preorder are unique.
 */
auto ToBST(const BinaryTree::ArrayType &preorder, const int upper, std::size_t &i) {
    if (i == preorder.size() or preorder[i] >= upper) {
        return BinaryTree::Node::PointerType {};
    }

    const auto value = preorder[i++];
    const auto node = std::make_shared<BinaryTree::Node>(value);
    node->left = ToBST(preorder, value, i);
    node->right = ToBST(preorder, upper, i);

    return node;
}

inline auto ToBST(const BinaryTree::ArrayType &preorder) {
    std::size_t i = 0;
    return ToBST(preorder, INT_MAX, i);
}

} //namespace


const std::vector SAMPLE1 = {8, 5, 1, 7, 10, 12};
const std::vector EXPECTED1 = {8, 5, 10, 1, 7, SENTINEL, 12};

const std::vector SAMPLE2 = {1, 3};
const std::vector EXPECTED2 = {1, SENTINEL, 3};


THE_BENCHMARK(ToBST, SAMPLE1);

SIMPLE_TEST(
    areIdenticalTrees, TestSAMPLE1, true, ToBST(SAMPLE1), LevelOrderToBinaryTree(EXPECTED1));
SIMPLE_TEST(
    areIdenticalTrees, TestSAMPLE2, true, ToBST(SAMPLE2), LevelOrderToBinaryTree(EXPECTED2));
