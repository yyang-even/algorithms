#include "common_header.h"

#include "binary_search_tree.h"
#include "flatten_BST.h"
#include "data_structure/tree/binary_tree/binary_tree_traversals.h"


namespace {

/**
 * @reference   Flatten BST to sorted list | Decreasing order
 *              https://www.geeksforgeeks.org/flatten-bst-to-sorted-list-decreasing-order/
 */
void FlattenBSTtoSortedList_Decreasing(const BinaryTree::Node::PointerType node,
                                       BinaryTree::Node::PointerType &previous) {
    if (node) {
        FlattenBSTtoSortedList_Decreasing(node->right, previous);

        previous->left = nullptr;
        previous->right = node;
        previous = node;

        FlattenBSTtoSortedList_Decreasing(node->left, previous);
    }
}


/**
 * @reference   Convert a given Binary Tree to Doubly Linked List | Set 1
 *              https://www.geeksforgeeks.org/in-place-convert-a-given-binary-tree-to-doubly-linked-list/
 * @reference   Convert a given Binary Tree to Doubly Linked List | Set 2
 *              https://www.geeksforgeeks.org/convert-a-given-binary-tree-to-doubly-linked-list-set-2/
 * @reference   Convert a given Binary Tree to Doubly Linked List | Set 3
 *              https://www.geeksforgeeks.org/convert-given-binary-tree-doubly-linked-list-set-3/
 * @reference   Convert a given Binary Tree to Doubly Linked List | Set 4
 *              https://www.geeksforgeeks.org/convert-a-given-binary-tree-to-doubly-linked-list-set-4/
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.13.
 *
 * @reference   The Great Tree-List Recursion Problem.
 *              https://www.geeksforgeeks.org/the-great-tree-list-recursion-problem/
 * @reference   Convert a Binary Tree to a Circular Doubly Link List
 *              https://www.geeksforgeeks.org/convert-a-binary-tree-to-a-circular-doubly-link-list/
 * @reference   Convert a given Binary Tree to Circular Doubly Linked List | Set 2
 *              https://www.geeksforgeeks.org/convert-a-given-binary-tree-to-circular-doubly-linked-list-set-2/
 */


/**
 * @reference   Convert a Binary Search Tree into a Skewed tree in increasing or decreasing order
 *              https://www.geeksforgeeks.org/convert-a-binary-search-tree-into-a-skewed-tree-in-increasing-or-decreasing-order/
 *
 * Given a Binary Search Tree and a binary integer K, the task is to convert Binary search
 * tree into a Skewed Tree in increasing order if K = 0 or in decreasing order if K = 1.
 *
 * @reference   Skewed Binary Tree
 *              https://www.geeksforgeeks.org/skewed-binary-tree/
 */

}


SIMPLE_BENCHMARK(FlattenBSTtoSortedList, BM_SAMPLE1,
                 MakeTheSampleBST(), FlattenBSTtoSortedList_Increasing);


SIMPLE_BENCHMARK(FlattenBSTtoSortedList, BM_SAMPLE2,
                 MakeTheSampleBST(), FlattenBSTtoSortedList_Decreasing);


#ifdef WANT_TESTS
#define FlattenBSTTest(function_name, do_reverse) namespace {                       \
    TEST(FlattenBSTtoSortedListTest, Test##function_name) {                         \
        const auto SAMPLE_BST = MakeTheSampleBST();                                 \
        BinaryTree::ArrayType EXPECTED;                                             \
        InorderTraversal_Recursive(SAMPLE_BST, EXPECTED);                           \
        if (do_reverse) {                                                           \
            std::reverse(EXPECTED.begin(), EXPECTED.end());                         \
        }                                                                           \
                                                                                    \
        const auto sorted_list = FlattenBSTtoSortedList(SAMPLE_BST, function_name); \
                                                                                    \
        auto current = sorted_list;                                                 \
        for (const auto expected_value : EXPECTED) {                                \
            EXPECT_EQ(nullptr, current->left);                                      \
            EXPECT_EQ(expected_value, current->value);                              \
            current = current->right;                                               \
        }                                                                           \
                                                                                    \
        EXPECT_EQ(nullptr, current);                                                \
    }                                                                               \
}


FlattenBSTTest(FlattenBSTtoSortedList_Increasing, false);


FlattenBSTTest(FlattenBSTtoSortedList_Decreasing, true);
#endif
