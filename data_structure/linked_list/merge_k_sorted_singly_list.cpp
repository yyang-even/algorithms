#include "common_header.h"

#include <forward_list>
#include <queue>

namespace {

using ListType = std::forward_list<int>;

/** Merge K sorted linked lists
 *
 * @reference   Merge K sorted linked lists | Set 1
 *              https://www.geeksforgeeks.org/merge-k-sorted-linked-lists/
 *              Merge k sorted linked lists | Set 2 (Using Min Heap)
 *              https://www.geeksforgeeks.org/merge-k-sorted-linked-lists-set-2-using-min-heap/
 *
 * Given K sorted linked lists of size N each, merge them and print the sorted output.
 */
std::vector<ListType>::iterator MergeKSortedListsRecursive(const std::vector<ListType>::iterator
        begin,
        const std::vector<ListType>::size_type size) {
    if (size <= 1) {
    } else if (size == 2) {
        begin->merge(std::move(*(std::next(begin))));
    } else {
        const auto half = size / 2;
        auto left_iter = MergeKSortedListsRecursive(begin, half);
        auto right_iter = MergeKSortedListsRecursive(begin + half, size - half);
        left_iter->merge(std::move(*right_iter));
    }
    return begin;
}
auto MergeKSortedListsRecursive(std::vector<ListType> k_lists) {
    return *MergeKSortedListsRecursive(k_lists.begin(), k_lists.size());
}


using Node = std::pair<ListType *, ListType::const_iterator>;

auto MergeKSortedListsMinHeap(std::vector<ListType> k_lists) {
    ListType final_sorted_list;
    auto current = final_sorted_list.cbefore_begin();

    std::vector<ListType *> first_elements;
    for (auto &l : k_lists) {
        if (not l.empty()) {
            first_elements.emplace_back(&l);
        }
    }

    const auto compare = [](ListType * lhs, ListType * rhs) {
        return  lhs->front() > rhs->front();
    };
    std::priority_queue<ListType *, std::vector<ListType *>, decltype(compare)> heap(compare,
            std::move(first_elements));

    while (not heap.empty()) {
        auto *const l = heap.top();
        heap.pop();
        final_sorted_list.splice_after(current, *l, l->cbefore_begin());
        ++current;

        if (not l->empty()) {
            heap.emplace(l);
        }
    }

    return final_sorted_list;
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

SIMPLE_BENCHMARK(MergeKSortedListsRecursive, SAMPLE_LISTS);
SIMPLE_BENCHMARK(MergeKSortedListsRecursive, SAMPLE_DIFF_SIZE_LISTS);

SIMPLE_TEST(MergeKSortedListsRecursive, TestSAMPLE, EXPECTED_LIST, SAMPLE_LISTS);
SIMPLE_TEST(MergeKSortedListsRecursive, TestSampleDiffSize, EXPECTED_DIFF_SIZE_LIST,
            SAMPLE_DIFF_SIZE_LISTS);


SIMPLE_BENCHMARK(MergeKSortedListsMinHeap, SAMPLE_LISTS);
SIMPLE_BENCHMARK(MergeKSortedListsMinHeap, SAMPLE_DIFF_SIZE_LISTS);

SIMPLE_TEST(MergeKSortedListsMinHeap, TestSAMPLE, EXPECTED_LIST, SAMPLE_LISTS);
SIMPLE_TEST(MergeKSortedListsMinHeap, TestSampleDiffSize, EXPECTED_DIFF_SIZE_LIST,
            SAMPLE_DIFF_SIZE_LISTS);
