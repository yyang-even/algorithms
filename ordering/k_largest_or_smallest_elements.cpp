#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

#include "kth_smallest_or_largest_element.h"

/** k largest(or smallest) elements in an array
 *
 * @reference   k largest(or smallest) elements in an array | added Min Heap method
 *              https://www.geeksforgeeks.org/k-largestor-smallest-elements-in-an-array/
 * @reference   Find the largest three elements in an array
 *              https://www.geeksforgeeks.org/find-the-largest-three-elements-in-an-array/
 * @reference   Program to print N minimum elements from list of integers
 *              https://www.geeksforgeeks.org/program-to-print-n-minimum-elements-from-list-of-integers/
 * @reference   Find the smallest and second smallest elements in an array
 *              https://www.geeksforgeeks.org/to-find-smallest-and-second-smallest-element-in-an-array/
 * @reference   Find the first, second and third minimum elements in an array
 *              https://www.geeksforgeeks.org/find-the-first-second-and-third-minimum-elements-in-an-array/
 *
 * Write an efficient program for printing k largest elements in an array.
 * Elements in array can be in any order.
 *
 * @reference   Find the largest pair sum in an unsorted array
 *              https://www.geeksforgeeks.org/find-the-largest-pair-sum-in-an-unsorted-array/
 *
 * Given an unsorted of distinct integers, find the largest pair sum in it.
 *
 * @highlight   Use of std::make_heap() and std::pop_heap()
 *              Use of std::make_reverse_iterator()
 */
auto KSmallestElements_Sort(ArrayType values, const ArrayType::size_type K) {
    assert(K <= values.size());

    std::sort(values.begin(), values.end());
    return ArrayType{std::make_move_iterator(values.cbegin()),
                     std::make_move_iterator(values.cbegin() + K)};
}


auto KSmallestElements_MinHeap(ArrayType values, ArrayType::size_type K) {
    assert(K <= values.size());

    const auto compare = std::greater<ArrayType::value_type> {};
    std::make_heap(values.begin(), values.end(), compare);

    auto end = values.end();
    for (; K--; --end) {
        std::pop_heap(values.begin(), end, compare);
    }

    return ArrayType{std::make_move_iterator(values.rbegin()),
                     std::make_move_iterator(std::make_reverse_iterator(end))};
}


auto KSmallestElements_QuickSelect(ArrayType values, ArrayType::size_type K) {
    assert(K and K <= values.size());

    const auto kth = KthSmallest_QuickSelect(values.begin(), values.end(), values.cbegin() + (K - 1));

    return ArrayType{std::make_move_iterator(values.begin()),
                     std::make_move_iterator(std::next(kth))};
}
auto SortedKSmallestElements_QuickSelect(const ArrayType &values, ArrayType::size_type K) {
    auto results = KSmallestElements_QuickSelect(values, K);
    std::sort(results.begin(), results.end());
    return results;
}


auto KSmallestElements_MaxHeap(const ArrayType &values, ArrayType::size_type K) {
    assert(K and K <= values.size());

    auto iter = values.cbegin() + K;
    std::priority_queue<ArrayType::value_type> heap{values.cbegin(), iter};
    for (; iter != values.cend(); ++iter) {
        if (*iter < heap.top()) {
            heap.pop();
            heap.push(*iter);
        }
    }

    ArrayType results;
    while (not heap.empty()) {
        results.push_back(std::move(heap.top()));
        heap.pop();
    }

    std::reverse(results.begin(), results.end());
    return results;
}


/** Print n smallest elements from given array in their original order
 *
 * @reference   https://www.geeksforgeeks.org/find-n-smallest-element-given-array-order-array/
 * @reference   Find k maximum elements of array in original order
 *              https://www.geeksforgeeks.org/find-k-maximum-elements-array-original-order/
 * @reference   k smallest elements in same order using O(1) extra space
 *              https://www.geeksforgeeks.org/k-smallest-elements-order-using-o1-extra-space/
 *
 * We are given an array of m-elements, we need to find n smallest elements from
 * the array but they must be in the same order as they are in given array.
 */
auto StableKSmallestElements_Sort(const ArrayType &values, const ArrayType::size_type K) {
    assert(K <= values.size());

    auto sorted_values = values;
    std::stable_sort(sorted_values.begin(), sorted_values.end());

    const auto cend = sorted_values.cbegin() + K;
    ArrayType results;
    for (const auto i : values) {
        if (std::binary_search(sorted_values.cbegin(), cend, i)) {
            results.push_back(i);
        }
    }

    return results;
}


auto StableKSmallestElements_Insertion(ArrayType values, const ArrayType::size_type K) {
    assert(K and K <= values.size());

    const auto iter_K = values.begin() + K;
    for (auto iter = iter_K; iter != values.end(); ++iter) {
        auto max_iter = std::max_element(values.begin(), iter_K);

        if (*max_iter > *iter) {
            for (auto next = std::next(max_iter); next != iter_K; ++next, ++max_iter) {
                *max_iter = std::move(*next);
            }
            *max_iter = std::move(*iter);
        }
    }

    return ArrayType{std::make_move_iterator(values.begin()),
                     std::make_move_iterator(iter_K)};
}

}//namespace


const ArrayType EMPTY = {};
const ArrayType VALUES1 = {1, 23, 12, 9, 30, 2, 50};
const ArrayType SORTED_EXPECTED1 = {1, 2, 9};
const ArrayType SORTED_VALUES1 = {1, 2, 9, 12, 23, 30, 50};


SIMPLE_BENCHMARK(KSmallestElements_Sort, VALUES1, SORTED_EXPECTED1.size());

SIMPLE_TEST(KSmallestElements_Sort, TestEmpty, EMPTY, VALUES1, EMPTY.size());
SIMPLE_TEST(KSmallestElements_Sort, TestSAMPLE1, SORTED_EXPECTED1, VALUES1,
            SORTED_EXPECTED1.size());
SIMPLE_TEST(KSmallestElements_Sort, TestSAMPLE2, SORTED_VALUES1, VALUES1, VALUES1.size());


SIMPLE_BENCHMARK(KSmallestElements_MinHeap, VALUES1, SORTED_EXPECTED1.size());

SIMPLE_TEST(KSmallestElements_MinHeap, TestEmpty, EMPTY, VALUES1, EMPTY.size());
SIMPLE_TEST(KSmallestElements_MinHeap, TestSAMPLE1, SORTED_EXPECTED1, VALUES1,
            SORTED_EXPECTED1.size());
SIMPLE_TEST(KSmallestElements_MinHeap, TestSAMPLE2, SORTED_VALUES1, VALUES1, VALUES1.size());


SIMPLE_BENCHMARK(SortedKSmallestElements_QuickSelect, VALUES1, SORTED_EXPECTED1.size());

SIMPLE_TEST(SortedKSmallestElements_QuickSelect, TestSAMPLE1, SORTED_EXPECTED1, VALUES1,
            SORTED_EXPECTED1.size());
SIMPLE_TEST(SortedKSmallestElements_QuickSelect, TestSAMPLE2, SORTED_VALUES1, VALUES1,
            VALUES1.size());


SIMPLE_BENCHMARK(KSmallestElements_MaxHeap, VALUES1, SORTED_EXPECTED1.size());

SIMPLE_TEST(KSmallestElements_MaxHeap, TestSAMPLE1, SORTED_EXPECTED1, VALUES1,
            SORTED_EXPECTED1.size());
SIMPLE_TEST(KSmallestElements_MaxHeap, TestSAMPLE2, SORTED_VALUES1, VALUES1, VALUES1.size());


const ArrayType STABLE_EXPECTED1 = {1, 9, 2};
const ArrayType VALUES2 = {1, 5, 8, 9, 6, 7, 3, 4, 2, 0};
const ArrayType STABLE_EXPECTED2 = {1, 3, 4, 2, 0};


SIMPLE_BENCHMARK(StableKSmallestElements_Sort, VALUES1, SORTED_EXPECTED1.size());

SIMPLE_TEST(StableKSmallestElements_Sort, TestSAMPLE1, STABLE_EXPECTED1, VALUES1,
            STABLE_EXPECTED1.size());
SIMPLE_TEST(StableKSmallestElements_Sort, TestSAMPLE2, STABLE_EXPECTED2, VALUES2,
            STABLE_EXPECTED2.size());
SIMPLE_TEST(StableKSmallestElements_Sort, TestSAMPLE3, VALUES1, VALUES1, VALUES1.size());


SIMPLE_BENCHMARK(StableKSmallestElements_Insertion, VALUES1, SORTED_EXPECTED1.size());

SIMPLE_TEST(StableKSmallestElements_Insertion, TestSAMPLE1, STABLE_EXPECTED1, VALUES1,
            STABLE_EXPECTED1.size());
SIMPLE_TEST(StableKSmallestElements_Insertion, TestSAMPLE2, STABLE_EXPECTED2, VALUES2,
            STABLE_EXPECTED2.size());
SIMPLE_TEST(StableKSmallestElements_Insertion, TestSAMPLE3, VALUES1, VALUES1, VALUES1.size());
