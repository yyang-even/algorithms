#include "common_header.h"


namespace {

using ListType = std::forward_list<int>;

/** Merge two sorted linked lists
 *
 * @reference   https://www.geeksforgeeks.org/merge-two-sorted-linked-lists/
 * @reference   Merge two sorted lists (in-place)
 *              https://www.geeksforgeeks.org/merge-two-sorted-lists-place/
 *
 * Write a SortedMerge() function that takes two lists, each of which is
 * sorted in increasing order, and merges the two together into one list
 * which is in increasing order. SortedMerge() should return the new list.
 * The new list should be made by splicing together the nodes of the first
 * two lists.
 * There are many cases to deal with: either ‘a’ or ‘b’ may be empty,
 * during processing either ‘a’ or ‘b’ may run out first, and finally
 * there’s the problem of starting the result list empty, and building
 * it up while going through ‘a’ and ‘b’.
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


auto SortedMergeList_Doubly_STL(std::list<int> L, std::list<int> R) {
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


auto testSortedMergeList_Single_STL(const std::vector<int> &L, const std::vector<int> &R) {
    const auto sorted_list = SortedMergeList_Single_STL({L.cbegin(), L.cend()},
    {R.cbegin(), R.cend()});
    return std::vector<int> {sorted_list.cbegin(), sorted_list.cend()};
}


auto testSortedMergeList_Doubly_STL(const std::vector<int> &L, const std::vector<int> &R) {
    const auto sorted_list = SortedMergeList_Doubly_STL({L.cbegin(), L.cend()},
    {R.cbegin(), R.cend()});
    return std::vector<int> {sorted_list.cbegin(), sorted_list.cend()};
}

}//namespace


const std::vector<int> EMPTY = {};

const std::vector<int> SAMPLE1L = {1, 3, 5, 7};
const std::vector<int> SAMPLE1R = {2, 4, 6, 8};
const std::vector<int> EXPECTED1 = {1, 2, 3, 4, 5, 6, 7, 8};

const std::vector<int> SAMPLE2L = {5, 8, 9};
const std::vector<int> SAMPLE2R = {4, 7, 8};
const std::vector<int> EXPECTED2 = {4, 5, 7, 8, 8, 9};


SIMPLE_BENCHMARK(testSortedMergeList_Single_STL, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(testSortedMergeList_Single_STL, TestSAMPLE1, EXPECTED1, SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(testSortedMergeList_Single_STL, TestSAMPLE2, EXPECTED2, SAMPLE2L, SAMPLE2R);
SIMPLE_TEST(testSortedMergeList_Single_STL, TestSAMPLE3, SAMPLE1L, SAMPLE1L, EMPTY);
SIMPLE_TEST(testSortedMergeList_Single_STL, TestSAMPLE4, SAMPLE1R, EMPTY, SAMPLE1R);


SIMPLE_BENCHMARK(testSortedMergeList_Doubly_STL, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(testSortedMergeList_Doubly_STL, TestSAMPLE1, EXPECTED1, SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(testSortedMergeList_Doubly_STL, TestSAMPLE2, EXPECTED2, SAMPLE2L, SAMPLE2R);
SIMPLE_TEST(testSortedMergeList_Doubly_STL, TestSAMPLE3, SAMPLE1L, SAMPLE1L, EMPTY);
SIMPLE_TEST(testSortedMergeList_Doubly_STL, TestSAMPLE4, SAMPLE1R, EMPTY, SAMPLE1R);
