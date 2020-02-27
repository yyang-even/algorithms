#include "common_header.h"

#include "binary_search_tree.h"


namespace {

/** Binary Search Tree | Set 1 (Search and Insertion)
 *
 * @reference   https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
 */
auto BSTSearch_Recursive(const BinaryTree::Node::PointerType node,
                         const BinaryTree::Node::ValueType x) {
    if (not node) {
        return false;
    }
    if (node->value == x) {
        return true;
    }

    return node->value > x ?
           BSTSearch_Recursive(node->left, x) :
           BSTSearch_Recursive(node->right, x);
}


/**
 * @reference   Iterative searching in Binary Search Tree
 *              https://www.geeksforgeeks.org/iterative-searching-binary-search-tree/
 */
auto BSTSearch_Iterative(BinaryTree::Node::PointerType current_node,
                         const BinaryTree::Node::ValueType x) {
    while (current_node) {
        if (x < current_node->value) {
            current_node = current_node->left;
        } else if (x > current_node->value) {
            current_node = current_node->right;
        } else {
            return true;
        }
    }
    return false;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();


SIMPLE_BENCHMARK(BSTSearch_Recursive, SAMPLE1, -1);
SIMPLE_BENCHMARK(BSTSearch_Recursive, SAMPLE1, 1);

SIMPLE_TEST(BSTSearch_Recursive, TestSAMPLE1, true, SAMPLE1, 4);
SIMPLE_TEST(BSTSearch_Recursive, TestSAMPLE2, true, SAMPLE1, 1);
SIMPLE_TEST(BSTSearch_Recursive, TestSAMPLE3, false, SAMPLE1, -1);


SIMPLE_BENCHMARK(BSTSearch_Iterative, SAMPLE1, -1);
SIMPLE_BENCHMARK(BSTSearch_Iterative, SAMPLE1, 1);

SIMPLE_TEST(BSTSearch_Iterative, TestSAMPLE1, true, SAMPLE1, 4);
SIMPLE_TEST(BSTSearch_Iterative, TestSAMPLE2, true, SAMPLE1, 1);
SIMPLE_TEST(BSTSearch_Iterative, TestSAMPLE3, false, SAMPLE1, -1);
