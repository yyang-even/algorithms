#include "common_header.h"

#include "binary_search_tree.h"
#include "BST_search.h"


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


auto hasNode_iterative(const BinaryTree::Node::PointerType current_node,
                       const BinaryTree::Node::ValueType x) {
    return static_cast<bool>(BSTSearch_Iterative(current_node, x));
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();


SIMPLE_BENCHMARK(BSTSearch_Recursive, SAMPLE1, -1);
SIMPLE_BENCHMARK(BSTSearch_Recursive, SAMPLE1, 1);

SIMPLE_TEST(BSTSearch_Recursive, TestSAMPLE1, true, SAMPLE1, 4);
SIMPLE_TEST(BSTSearch_Recursive, TestSAMPLE2, true, SAMPLE1, 1);
SIMPLE_TEST(BSTSearch_Recursive, TestSAMPLE3, false, SAMPLE1, -1);


SIMPLE_BENCHMARK(hasNode_iterative, SAMPLE1, -1);
SIMPLE_BENCHMARK(hasNode_iterative, SAMPLE1, 1);

SIMPLE_TEST(hasNode_iterative, TestSAMPLE1, true, SAMPLE1, 4);
SIMPLE_TEST(hasNode_iterative, TestSAMPLE2, true, SAMPLE1, 1);
SIMPLE_TEST(hasNode_iterative, TestSAMPLE3, false, SAMPLE1, -1);


SIMPLE_BENCHMARK(MinimumNode, SAMPLE1);

SIMPLE_TEST(MinimumNode, TestSAMPLE1, SAMPLE1->left->left, SAMPLE1);


SIMPLE_BENCHMARK(MaximumNode, SAMPLE1);

SIMPLE_TEST(MaximumNode, TestSAMPLE1, SAMPLE1->right, SAMPLE1);
