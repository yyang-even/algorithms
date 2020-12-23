#include "common_header.h"

#include "binary_search_tree.h"
#include "data_structure/tree/binary_tree/binary_tree_traversals.h"


namespace {

/** Flatten BST to sorted list | Increasing order
 *
 * @reference   https://www.geeksforgeeks.org/flatten-bst-to-sorted-list-increasing-order/
 *
 * Given a binary search tree, the task is to flatten it to a sorted list. Precisely, the
 * value of each node must be lesser than the values of all the nodes at its right, and
 * its left node must be NULL after flattening. We must do it in O(H) extra space where
 * 'H' is the height of BST.
 */
void FlattenBSTtoSortedList_Increasing(const BinaryTree::Node::PointerType node,
                                       BinaryTree::Node::PointerType &previous) {
    if (node) {
        FlattenBSTtoSortedList_Increasing(node->left, previous);

        previous->left = nullptr;
        previous->right = node;
        previous = node;

        FlattenBSTtoSortedList_Increasing(node->right, previous);
    }
}


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
 * @reference   Convert a Binary Search Tree into a Skewed tree in increasing or decreasing order
 *              https://www.geeksforgeeks.org/convert-a-binary-search-tree-into-a-skewed-tree-in-increasing-or-decreasing-order/
 *
 * Given a Binary Search Tree and a binary integer K, the task is to convert Binary search
 * tree into a Skewed Tree in increasing order if K = 0 or in decreasing order if K = 1.
 */


template <typename Flatten_BST_Func>
auto FlattenBSTtoSortedList(const BinaryTree::Node::PointerType root,
                            const Flatten_BST_Func flatten_bst) {
    const auto dummy_node = std::make_shared<BinaryTree::Node>(-1);

    auto previous = dummy_node;
    flatten_bst(root, previous);

    previous->left = previous->right = nullptr;

    return dummy_node->right;
}

}


SIMPLE_BENCHMARK(FlattenBSTtoSortedList, BM_SAMPLE1,
                 MakeTheSampleBST().GetRoot(), FlattenBSTtoSortedList_Increasing);


SIMPLE_BENCHMARK(FlattenBSTtoSortedList, BM_SAMPLE2,
                 MakeTheSampleBST().GetRoot(), FlattenBSTtoSortedList_Decreasing);


#ifdef WANT_TESTS
#define FlattenBSTTest(function_name, do_reverse) namespace {                       \
    TEST(FlattenBSTtoSortedListTest, Test##function_name) {                         \
        const auto SAMPLE_BST = MakeTheSampleBST().GetRoot();                       \
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
