#include "common_header.h"

#include "binary_search_tree.h"
#include "data_structure/tree/binary_tree/binary_tree_traversals.h"


namespace {

using ListType = std::list<BinaryTree::Node::ValueType>;
using InitializerType = std::initializer_list<ListType::value_type>;

/** Sorted Linked List to Balanced BST
 *
 * @reference   https://www.geeksforgeeks.org/sorted-linked-list-to-balanced-bst/
 */
auto SortedListToBalancedBSTHelper(ListType::const_iterator &cbegin, const int size) {
    if (size <= 0) {
        return BinaryTree::Node::PointerType{};
    }

    const auto left_child = SortedListToBalancedBSTHelper(cbegin, size / 2);

    const auto root = std::make_shared<BinaryTree::Node>(*cbegin);
    root->left = left_child;
    ++cbegin;

    root->right = SortedListToBalancedBSTHelper(cbegin, size - size / 2 - 1);

    return root;
}

inline auto SortedListToBalancedBST(const ListType &sorted_list) {
    assert(std::is_sorted(sorted_list.cbegin(), sorted_list.cend()));

    auto cbegin = sorted_list.cbegin();
    return SortedListToBalancedBSTHelper(cbegin, sorted_list.size());
}


/**
 * @reference   In-place conversion of Sorted DLL to Balanced BST
 *              https://www.geeksforgeeks.org/in-place-conversion-of-sorted-dll-to-balanced-bst/
 *
 * Given a Doubly Linked List which has data members sorted in ascending order. Construct
 * a Balanced Binary Search Tree which has same data members as the given Doubly Linked
 * List. The tree must be constructed in-place (No new node should be allocated for tree
 * conversion)
 */


/**
 * @reference   Sorted Array to Balanced BST
 *              https://www.geeksforgeeks.org/sorted-array-to-balanced-bst/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.3.
 */
auto SortedArrayToBalancedBSTHelper(const BinaryTree::ArrayType &sorted_array,
                                    const int first, const int last) {
    if (first > last) {
        return BinaryTree::Node::PointerType{};
    }

    const auto mid_index = (first + last) / 2;
    const auto root = std::make_shared<BinaryTree::Node>(sorted_array[mid_index]);

    root->left = SortedArrayToBalancedBSTHelper(sorted_array, first, mid_index - 1);
    root->right = SortedArrayToBalancedBSTHelper(sorted_array,  mid_index + 1, last);

    return root;
}

inline auto SortedArrayToBalancedBST(const BinaryTree::ArrayType &sorted_array) {
    assert(std::is_sorted(sorted_array.cbegin(), sorted_array.cend()));

    return SortedArrayToBalancedBSTHelper(sorted_array, 0, sorted_array.size() - 1);
}


/**
 * @reference   Convert a normal BST to Balanced BST
 *              https://www.geeksforgeeks.org/convert-normal-bst-balanced-bst/
 *
 * Given a BST (Binary Search Tree) that may be unbalanced, convert it into a balanced
 * BST that has minimum possible height.
 */


template <typename ToBST>
inline constexpr auto
TestToBalancedBST(const ToBST to_bst, const InitializerType &sorted_sequence) {
    const auto root = to_bst(sorted_sequence);

    BinaryTree::ArrayType inorder_array;
    InorderTraversal_Recursive(root, inorder_array);

    return std::equal(sorted_sequence.begin(), sorted_sequence.end(),
                      inorder_array.cbegin(), inorder_array.cend());
}

}


constexpr InitializerType SAMPLE1 = {};
constexpr InitializerType SAMPLE2 = {1};
constexpr InitializerType SAMPLE3 = {1, 2};
constexpr InitializerType SAMPLE4 = {1, 2, 3};
constexpr InitializerType SAMPLE5 = {1, 2, 3, 4, 5, 6, 7};


THE_BENCHMARK(SortedListToBalancedBST, SAMPLE4);

SIMPLE_TEST(TestToBalancedBST, TestSAMPLEL1, true, SortedListToBalancedBST, SAMPLE1);
SIMPLE_TEST(TestToBalancedBST, TestSAMPLEL2, true, SortedListToBalancedBST, SAMPLE2);
SIMPLE_TEST(TestToBalancedBST, TestSAMPLEL3, true, SortedListToBalancedBST, SAMPLE3);
SIMPLE_TEST(TestToBalancedBST, TestSAMPLEL4, true, SortedListToBalancedBST, SAMPLE4);
SIMPLE_TEST(TestToBalancedBST, TestSAMPLEL5, true, SortedListToBalancedBST, SAMPLE5);


THE_BENCHMARK(SortedArrayToBalancedBST, SAMPLE4);

SIMPLE_TEST(TestToBalancedBST, TestSAMPLEA1, true, SortedArrayToBalancedBST, SAMPLE1);
SIMPLE_TEST(TestToBalancedBST, TestSAMPLEA2, true, SortedArrayToBalancedBST, SAMPLE2);
SIMPLE_TEST(TestToBalancedBST, TestSAMPLEA3, true, SortedArrayToBalancedBST, SAMPLE3);
SIMPLE_TEST(TestToBalancedBST, TestSAMPLEA4, true, SortedArrayToBalancedBST, SAMPLE4);
SIMPLE_TEST(TestToBalancedBST, TestSAMPLEA5, true, SortedArrayToBalancedBST, SAMPLE5);
