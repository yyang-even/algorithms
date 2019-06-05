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
auto SortedMergeList_STL(ListType L, ListType R) {
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

}//namespace


const ListType EMPTY = {};

const ListType SAMPLE1L = {1, 3, 5, 7};
const ListType SAMPLE1R = {2, 4, 6, 8};
const ListType EXPECTED1 = {1, 2, 3, 4, 5, 6, 7, 8};

const ListType SAMPLE2L = {5, 8, 9};
const ListType SAMPLE2R = {4, 7, 8};
const ListType EXPECTED2 = {4, 5, 7, 8, 8, 9};

SIMPLE_BENCHMARK(SortedMergeList_STL, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(SortedMergeList_STL, TestSAMPLE1, EXPECTED1, SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(SortedMergeList_STL, TestSAMPLE2, EXPECTED2, SAMPLE2L, SAMPLE2R);
SIMPLE_TEST(SortedMergeList_STL, TestSAMPLE3, SAMPLE1L, SAMPLE1L, EMPTY);
SIMPLE_TEST(SortedMergeList_STL, TestSAMPLE4, SAMPLE1R, EMPTY, SAMPLE1R);
