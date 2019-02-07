#include "common_header.h"

#include <forward_list>

namespace {

using ListType = std::forward_list<int>;

/** Merge K sorted linked lists
 *
 * @reference   Merge K sorted linked lists | Set 1
 *              https://www.geeksforgeeks.org/merge-k-sorted-linked-lists/
 */
std::vector<ListType>::iterator MergeKSortedLists(const std::vector<ListType>::iterator begin,
        const std::vector<ListType>::size_type size) {
    if (size <= 1) {
    } else if (size == 2) {
        begin->merge(std::move(*(std::next(begin))));
    } else {
        const auto half = size / 2;
        auto left_iter = MergeKSortedLists(begin, half);
        auto right_iter = MergeKSortedLists(begin + half, size - half);
        left_iter->merge(std::move(*right_iter));
    }
    return begin;
}
auto MergeKSortedLists(std::vector<ListType> k_arrays) {
    return *MergeKSortedLists(k_arrays.begin(), k_arrays.size());
}

}//namespace


const std::vector<ListType> SAMPLE_LISTS = {{1, 3, 5, 7, 9},
    {2, 4, 6, 8, 10},
    {11, 12, 13, 19},
    {14, 15, 16, 20}
};
const ListType EXPECTED_LIST = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 19, 20};

const std::vector<ListType> SAMPLE_DIFF_SIZE_LISTS = {{1, 3, 5, 7, 9},
    {2, 4, 6, 8},
    {11},
    {10, 12, 13, 14, 15, 16, 20}
};
const ListType EXPECTED_DIFF_SIZE_LIST = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 20};

SIMPLE_BENCHMARK(MergeKSortedLists, SAMPLE_LISTS);
SIMPLE_BENCHMARK(MergeKSortedLists, SAMPLE_DIFF_SIZE_LISTS);

SIMPLE_TEST(MergeKSortedLists, TestSAMPLE, EXPECTED_LIST, SAMPLE_LISTS);
SIMPLE_TEST(MergeKSortedLists, TestSampleDiffSize, EXPECTED_DIFF_SIZE_LIST,
            SAMPLE_DIFF_SIZE_LISTS);
