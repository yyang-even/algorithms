#include "common_header.h"

#include "binary_heap.h"

#include "data_structure/tree/binary_tree/binary_tree.h"
#include "data_structure/tree/binary_tree/complete_binary_tree.h"
#include "data_structure/tree/binary_tree/single_order_to_binary_tree.h"


namespace {

inline auto isMaxHeap_Recursive(const MaxHeap<int>::ArrayType &values) {
    return MaxHeap<int>::isHeap_Recursive(values);
}


inline auto isMaxHeap_Iterative(const MaxHeap<int>::ArrayType &values) {
    return MaxHeap<int>::isHeap_Iterative(values);
}


inline auto isMinHeap_Iterative(const MinHeap<int>::ArrayType &values) {
    return MinHeap<int>::isHeap_Iterative(values);
}


/** Check if a given Binary Tree is Heap
 *
 * @reference   https://www.geeksforgeeks.org/check-if-a-given-binary-tree-is-heap/
 */
auto isMaxHeap_Helper(const BinaryTree::Node::PointerType node) {
    if ((not node) or (not node->left and not node->right)) {
        return true;
    }

    if (not node->right) {
        return node->value >= node->left->value;
    }

    if (node->value >= node->left->value and
        node->value >= node->right->value)
        return isMaxHeap_Helper(node->left) and
               isMaxHeap_Helper(node->right);

    return false;
}

inline auto isMaxHeap(const BinaryTree::Node::PointerType root_node) {
    return isCompleteBinaryTree(root_node) and isMaxHeap_Helper(root_node);
}

}//namespace


const MaxHeap<int>::ArrayType SAMPLE_ARRAY1 = {90, 15, 10, 7, 12, 2};
const MaxHeap<int>::ArrayType SAMPLE_ARRAY2 = {9, 15, 10, 7, 12, 11};
const MaxHeap<int>::ArrayType SAMPLE_ARRAY3 = {9};
const MaxHeap<int>::ArrayType SAMPLE_ARRAY4 = {90, 15, 10, 7, 12, 2, 7, 3};


THE_BENCHMARK(isMaxHeap_Recursive, SAMPLE_ARRAY1);

SIMPLE_TEST(isMaxHeap_Recursive, TestSample1, true, SAMPLE_ARRAY1);
SIMPLE_TEST(isMaxHeap_Recursive, TestSample2, false, SAMPLE_ARRAY2);
SIMPLE_TEST(isMaxHeap_Recursive, TestSample3, true, SAMPLE_ARRAY3);
SIMPLE_TEST(isMaxHeap_Recursive, TestSample4, true, SAMPLE_ARRAY4);


THE_BENCHMARK(isMaxHeap_Iterative, SAMPLE_ARRAY1);

SIMPLE_TEST(isMaxHeap_Iterative, TestSample1, true, SAMPLE_ARRAY1);
SIMPLE_TEST(isMaxHeap_Iterative, TestSample2, false, SAMPLE_ARRAY2);
SIMPLE_TEST(isMaxHeap_Iterative, TestSample3, true, SAMPLE_ARRAY3);
SIMPLE_TEST(isMaxHeap_Iterative, TestSample4, true, SAMPLE_ARRAY4);


const MinHeap<int>::ArrayType SAMPLE_ARRAY5 = {10, 15, 14, 25, 30};
const MinHeap<int>::ArrayType SAMPLE_ARRAY6 = {30, 56, 22, 49, 30, 51, 2, 67};


THE_BENCHMARK(isMinHeap_Iterative, SAMPLE_ARRAY5);

SIMPLE_TEST(isMinHeap_Iterative, TestSample1, true, SAMPLE_ARRAY5);
SIMPLE_TEST(isMinHeap_Iterative, TestSample2, false, SAMPLE_ARRAY6);


const auto SAMPLE_TREE1 = MakeTheSampleCompleteTree().GetRoot();
/**
 *     5
 *    / \
 *   3   4
 *  / \
 * 2   1
 */
const auto SAMPLE_TREE2 = LevelOrderToBinaryTree( {
    5, 3, 4, 2, 1
});


THE_BENCHMARK(isMaxHeap, SAMPLE_TREE1);

SIMPLE_TEST(isMaxHeap, TestSample1, false, SAMPLE_TREE1);
SIMPLE_TEST(isMaxHeap, TestSample2, true, SAMPLE_TREE2);
