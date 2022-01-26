#include "common_header.h"

#include "data_structure/tree/binary_tree/BST/binary_search_tree.h"


namespace {

using ListType = std::forward_list<int>;
using ArrayType = std::vector<int>;

/** Merge two sorted linked lists
 *
 * @reference   https://www.geeksforgeeks.org/merge-two-sorted-linked-lists/
 * @reference   Merge two sorted lists (in-place)
 *              https://www.geeksforgeeks.org/merge-two-sorted-lists-place/
 * @reference   Merge Two Sorted Lists
 *              https://leetcode.com/problems/merge-two-sorted-lists/
 *
 * Write a SortedMerge() function that takes two lists, each of which is sorted in
 * increasing order, and merges the two together into one list which is in increasing
 * order. SortedMerge() should return the new list. The new list should be made by
 * splicing together the nodes of the first two lists. There are many cases to deal
 * with: either 'a' or 'b' may be empty, during processing either 'a' or 'b' may run out
 * first, and finally there's the problem of starting the result list empty, and building
 * it up while going through 'a' and 'b'.
 */
auto SortedMergeList_Single_STL(ListType L, ListType R) {
    assert(std::is_sorted(L.cbegin(), L.cend()));
    assert(std::is_sorted(R.cbegin(), R.cend()));

    auto current = L.cbefore_begin();
    for (auto next = L.cbegin(); next != L.cend() and not R.empty(); ++current) {
        if (*next <= R.front()) {
            ++next;
        } else {
            L.splice_after(current, R, R.cbefore_begin());
        }
    }

    L.splice_after(current, R, R.cbefore_begin(), R.cend());

    return L;
}


auto SortedMergeList_Doubly_STL(std::list<ListType::value_type> L,
                                std::list<ListType::value_type> R) {
    assert(std::is_sorted(L.cbegin(), L.cend()));
    assert(std::is_sorted(R.cbegin(), R.cend()));

    for (auto next = L.cbegin(); next != L.cend() and not R.empty();) {
        if (*next <= R.front()) {
            ++next;
        } else {
            L.splice(next, R, R.cbegin());
        }
    }

    L.splice(L.cend(), R, R.cbegin(), R.cend());

    return L;
}


/** Sorted merge of two sorted doubly circular linked lists
 *
 * @reference   https://www.geeksforgeeks.org/sorted-merge-of-two-sorted-doubly-circular-linked-lists/
 */


/**
 * @reference   All Elements in Two Binary Search Trees
 *              https://leetcode.com/problems/all-elements-in-two-binary-search-trees/
 *
 * Given two binary search trees root1 and root2, return a list containing all the
 * integers from both trees sorted in ascending order.
 */
void pushLeft(std::stack<BinaryTree::Node::PointerType> &s,
              BinaryTree::Node::PointerType node) {
    while (node) {
        s.push(std::exchange(node, node->left));
    }
}

auto MergeTwoBST(const BinaryTree::Node::PointerType root1,
                 const BinaryTree::Node::PointerType root2) {
    std::stack<BinaryTree::Node::PointerType> s1, s2;
    pushLeft(s1, root1);
    pushLeft(s2, root2);

    ArrayType result;
    while (not s1.empty() or not s2.empty()) {
        auto &s = s1.empty() ? s2 : s1.top()->value <= s2.top()->value ? s1 : s2;
        const auto node = s.top();
        s.pop();
        result.push_back(node->value);
        pushLeft(s, node->right);
    }

    return result;
}

}//namespace


using InitializerType = std::initializer_list<ListType::value_type>;

constexpr InitializerType EMPTY = {};

constexpr InitializerType SAMPLE1L = {1, 3, 5, 7};
constexpr InitializerType SAMPLE1R = {2, 4, 6, 8};
constexpr InitializerType EXPECTED1 = {1, 2, 3, 4, 5, 6, 7, 8};

constexpr InitializerType SAMPLE2L = {5, 8, 9};
constexpr InitializerType SAMPLE2R = {4, 7, 8};
constexpr InitializerType EXPECTED2 = {4, 5, 7, 8, 8, 9};


THE_BENCHMARK(SortedMergeList_Single_STL, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(SortedMergeList_Single_STL, TestSAMPLE1, EXPECTED1, SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(SortedMergeList_Single_STL, TestSAMPLE2, EXPECTED2, SAMPLE2L, SAMPLE2R);
SIMPLE_TEST(SortedMergeList_Single_STL, TestSAMPLE3, SAMPLE1L, SAMPLE1L, EMPTY);
SIMPLE_TEST(SortedMergeList_Single_STL, TestSAMPLE4, SAMPLE1R, EMPTY, SAMPLE1R);


THE_BENCHMARK(SortedMergeList_Doubly_STL, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(SortedMergeList_Doubly_STL, TestSAMPLE1, EXPECTED1, SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(SortedMergeList_Doubly_STL, TestSAMPLE2, EXPECTED2, SAMPLE2L, SAMPLE2R);
SIMPLE_TEST(SortedMergeList_Doubly_STL, TestSAMPLE3, SAMPLE1L, SAMPLE1L, EMPTY);
SIMPLE_TEST(SortedMergeList_Doubly_STL, TestSAMPLE4, SAMPLE1R, EMPTY, SAMPLE1R);


const auto SAMPLE1T = MakeTheSampleBST();
const ArrayType EXPECTED1T = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};


THE_BENCHMARK(MergeTwoBST, SAMPLE1T, SAMPLE1T);

SIMPLE_TEST(MergeTwoBST, TestSAMPLE1, EXPECTED1T, SAMPLE1T, SAMPLE1T);
