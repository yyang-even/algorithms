#include "common_header.h"

#include "binary_search_tree.h"
#include "is_BST.h"


namespace {

/** A program to check if a binary tree is BST or not
 *
 * @reference   https://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/
 */
auto isBST_Recursive(const BinaryTree::Node::PointerType node,
                     const BinaryTree::Node::ValueType min = std::numeric_limits<BinaryTree::Node::ValueType>::min(),
                     const BinaryTree::Node::ValueType max = std::numeric_limits<BinaryTree::Node::ValueType>::max()) {
    if (not node) {
        return true;
    }

    if (node->value < min or node->value > max) {
        return false;
    }

    return isBST_Recursive(node->left, min, node->value - 1) and
           isBST_Recursive(node->right, node->value + 1, max);
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();
const auto SAMPLE2 = MakeTheSampleCompleteTree().GetRoot();
/**
 *     3
 *    / \
 *   2   5
 *  / \
 * 1   4
 */
static inline auto MakeSample3() {
    BinaryTree binary_tree{3};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 2);
    SetRightChild(root, 5);
    SetLeftChild(left_child, 1);
    SetRightChild(left_child, 4);

    return binary_tree;
}
const auto SAMPLE3 = MakeSample3().GetRoot();


SIMPLE_BENCHMARK(isBST_Recursive, SAMPLE1);
SIMPLE_BENCHMARK(isBST_Recursive, SAMPLE2);

SIMPLE_TEST(isBST_Recursive, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isBST_Recursive, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(isBST_Recursive, TestSAMPLE3, false, SAMPLE3);


SIMPLE_BENCHMARK(isBST_Recursive_Inorder, SAMPLE1);
SIMPLE_BENCHMARK(isBST_Recursive_Inorder, SAMPLE2);

SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE3, false, SAMPLE3);
