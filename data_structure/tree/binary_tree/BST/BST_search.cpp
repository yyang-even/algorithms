#include "common_header.h"

#include "binary_search_tree.h"
#include "data_structure/tree/binary_tree/binary_tree_search.h"


namespace {

/** Binary Search Tree | Set 1 (Search and Insertion)
 *
 * @reference   https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 12.2.
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


/** Find the node with minimum value in a Binary Search Tree
 *
 * @reference   https://www.geeksforgeeks.org/find-the-minimum-element-in-a-binary-search-tree/
 * @reference   Find the node with minimum value in a Binary Search Tree using recursion
 *              https://www.geeksforgeeks.org/find-the-node-with-minimum-value-in-a-binary-search-tree-using-recursion/
 * @reference   Find the node with maximum value in a Binary Search Tree
 *              https://www.geeksforgeeks.org/find-the-node-with-maximum-value-in-a-binary-search-tree/
 * @reference   Find the node with maximum value in a Binary Search Tree using recursion
 *              https://www.geeksforgeeks.org/find-the-node-with-maximum-value-in-a-binary-search-tree-using-recursion/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 12.2-2.
 */
auto Minimum(const BinaryTree::Node::PointerType root_node) {
    assert(root_node);
    return LeftmostNode(root_node)->value;
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


SIMPLE_BENCHMARK(Minimum, SAMPLE1);

SIMPLE_TEST(Minimum, TestSAMPLE1, 1, SAMPLE1);
