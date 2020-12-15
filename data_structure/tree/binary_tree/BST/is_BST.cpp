#include "common_header.h"

#include "binary_search_tree.h"
#include "is_BST.h"


namespace {

/** A program to check if a binary tree is BST or not
 *
 * @reference   https://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/
 */
auto isBST_Recursive(const BinaryTree::Node::PointerType node,
                     const BinaryTree::Node::ValueType min =
                         std::numeric_limits<BinaryTree::Node::ValueType>::min(),
                     const BinaryTree::Node::ValueType max =
                         std::numeric_limits<BinaryTree::Node::ValueType>::max()) {
    if (not node) {
        return true;
    }

    if (node->value < min or node->value > max) {
        return false;
    }

    return isBST_Recursive(node->left, min, node->value - 1) and
           isBST_Recursive(node->right, node->value + 1, max);
}


auto isBST_Iterative_Inorder(const BinaryTree::Node::PointerType root) {
    std::stack<BinaryTree::Node::PointerType> remaining_nodes;
    BinaryTree::Node::PointerType previous_node;

    for (auto current_node = root;
         current_node or not remaining_nodes.empty();
         current_node = current_node->right) {
        while (current_node) {
            remaining_nodes.push(current_node);
            current_node = current_node->left;
        }

        current_node = remaining_nodes.top();
        remaining_nodes.pop();

        if (previous_node and current_node->value <= previous_node->value) {
            return false;
        }

        previous_node = current_node;
    }

    return true;
}


/** Check if an array represents Inorder of Binary Search tree or not
 *
 * @reference   https://www.geeksforgeeks.org/check-array-represents-inorder-binary-search-tree-not/
 */
auto isBSTInorderRepresent(const BinaryTree::ArrayType &array) {
    return std::is_sorted(array.cbegin(), array.cend());
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


SIMPLE_BENCHMARK(isBST_Recursive, Sample1, SAMPLE1);
SIMPLE_BENCHMARK(isBST_Recursive, Sample2, SAMPLE2);

SIMPLE_TEST(isBST_Recursive, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isBST_Recursive, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(isBST_Recursive, TestSAMPLE3, false, SAMPLE3);


SIMPLE_BENCHMARK(isBST_Recursive_Inorder, Sample1, SAMPLE1);
SIMPLE_BENCHMARK(isBST_Recursive_Inorder, Sample2, SAMPLE2);

SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE3, false, SAMPLE3);


SIMPLE_BENCHMARK(isBST_Iterative_Inorder, Sample1, SAMPLE1);
SIMPLE_BENCHMARK(isBST_Iterative_Inorder, Sample2, SAMPLE2);

SIMPLE_TEST(isBST_Iterative_Inorder, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isBST_Iterative_Inorder, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(isBST_Iterative_Inorder, TestSAMPLE3, false, SAMPLE3);


const BinaryTree::ArrayType ARRAY1 = {19, 23, 25, 30, 45};
const BinaryTree::ArrayType ARRAY2 = {19, 23, 30, 25, 45};


SIMPLE_BENCHMARK(isBSTInorderRepresent, Sample1, ARRAY1);

SIMPLE_TEST(isBSTInorderRepresent, TestSAMPLE1, true, ARRAY1);
SIMPLE_TEST(isBSTInorderRepresent, TestSAMPLE2, false, ARRAY2);
