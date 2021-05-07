#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::unordered_set<ArrayType::value_type>;

#include "kth_smallest_or_largest_element.h"

/** k largest(or smallest) elements in an array
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 9-1.
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
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.6.
 *
 * Write an efficient program for printing k largest elements in an array. Elements in
 * array can be in any order.
 *
 * @reference   Find the largest pair sum in an unsorted array
 *              https://www.geeksforgeeks.org/find-the-largest-pair-sum-in-an-unsorted-array/
 * @reference   Smallest Pair Sum in an array
 *              https://www.geeksforgeeks.org/smallest-pair-sum-in-an-array/
 *
 * Given an unsorted of distinct integers, find the largest pair sum in it.
 *
 * @reference   Minimum product pair an array of positive Integers
 *              https://www.geeksforgeeks.org/minimum-product-pair-an-array-of-positive-integers/
 *
 * Given an array of positive integers. We are required to write a program to print the
 * minimum product of any two numbers of the given array.
 *
 * @highlight   Use of std::make_heap() and std::pop_heap()
 *              Use of std::make_reverse_iterator()
 */
/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 9-1.a.
 */
inline auto KSmallestElements_Sort(ArrayType values, const ArrayType::size_type K) {
    assert(K <= values.size());

    std::sort(values.begin(), values.end());
    return OutputType{std::make_move_iterator(values.begin()),
                      std::make_move_iterator(values.begin() + K)};
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 9-1.b.
 */
auto KSmallestElements_MinHeap(ArrayType values, ArrayType::size_type K) {
    assert(K <= values.size());

    static constexpr auto compare = std::greater<ArrayType::value_type> {};
    std::make_heap(values.begin(), values.end(), compare);

    auto end = values.end();
    for (; K--; --end) {
        std::pop_heap(values.begin(), end, compare);
    }

    return OutputType{std::make_move_iterator(values.rbegin()),
                      std::make_move_iterator(std::make_reverse_iterator(end))};
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 9-1.c.
 */
inline auto KSmallestElements_QuickSelect(ArrayType values, ArrayType::size_type K) {
    assert(K and K <= values.size());

    const auto kth =
        KthSmallest_QuickSelect(values.begin(), values.end(), values.cbegin() + (K - 1));

    return OutputType{std::make_move_iterator(values.begin()),
                      std::make_move_iterator(std::next(kth))};
}


auto KSmallestElements_MaxHeap(const ArrayType &values, ArrayType::size_type K) {
    assert(K and K <= values.size());

    auto iter = values.cbegin() + K;
    std::priority_queue heap{values.cbegin(), iter};
    for (; iter != values.cend(); ++iter) {
        if (*iter < heap.top()) {
            heap.pop();
            heap.push(*iter);
        }
    }

    OutputType results;
    while (not heap.empty()) {
        results.emplace(std::move(heap.top()));
        heap.pop();
    }

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
 * We are given an array of m-elements, we need to find n smallest elements from the
 * array but they must be in the same order as they are in given array.
 */
auto StableKSmallestElements_Sort(const ArrayType &values,
                                  const ArrayType::size_type K) {
    assert(K <= values.size());

    auto sorted_values = values;
    std::stable_sort(sorted_values.begin(), sorted_values.end());

    const auto cend = sorted_values.cbegin() + K;
    OutputType results;
    for (const auto i : values) {
        if (std::binary_search(sorted_values.cbegin(), cend, i)) {
            results.emplace(i);
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

    return OutputType{std::make_move_iterator(values.begin()),
                      std::make_move_iterator(iter_K)};
}

}//namespace


using InitializerType = std::initializer_list<ArrayType::value_type>;

constexpr InitializerType EMPTY = {};
constexpr InitializerType VALUES1 = {1, 23, 12, 9, 30, 2, 50};
constexpr InitializerType EXPECTED1 = {1, 2, 9};


THE_BENCHMARK(KSmallestElements_Sort, VALUES1, EXPECTED1.size());

SIMPLE_TEST(KSmallestElements_Sort, TestEmpty, EMPTY, VALUES1, EMPTY.size());
SIMPLE_TEST(KSmallestElements_Sort, TestSAMPLE1, EXPECTED1, VALUES1, EXPECTED1.size());
SIMPLE_TEST(KSmallestElements_Sort, TestSAMPLE2, VALUES1, VALUES1, VALUES1.size());


THE_BENCHMARK(KSmallestElements_MinHeap, VALUES1, EXPECTED1.size());

SIMPLE_TEST(KSmallestElements_MinHeap, TestEmpty, EMPTY, VALUES1, EMPTY.size());
SIMPLE_TEST(KSmallestElements_MinHeap, TestSAMPLE1, EXPECTED1,
            VALUES1, EXPECTED1.size());
SIMPLE_TEST(KSmallestElements_MinHeap, TestSAMPLE2, VALUES1, VALUES1, VALUES1.size());


THE_BENCHMARK(KSmallestElements_QuickSelect, VALUES1, EXPECTED1.size());

SIMPLE_TEST(KSmallestElements_QuickSelect, TestSAMPLE1, EXPECTED1,
            VALUES1, EXPECTED1.size());
SIMPLE_TEST(KSmallestElements_QuickSelect, TestSAMPLE2, VALUES1,
            VALUES1, VALUES1.size());


THE_BENCHMARK(KSmallestElements_MaxHeap, VALUES1, EXPECTED1.size());

SIMPLE_TEST(KSmallestElements_MaxHeap, TestSAMPLE1, EXPECTED1,
            VALUES1, EXPECTED1.size());
SIMPLE_TEST(KSmallestElements_MaxHeap, TestSAMPLE2, VALUES1, VALUES1, VALUES1.size());


const ArrayType VALUES2 = {1, 5, 8, 9, 6, 7, 3, 4, 2, 0};
constexpr InitializerType EXPECTED2 = {1, 3, 4, 2, 0};


THE_BENCHMARK(StableKSmallestElements_Sort, VALUES1, EXPECTED1.size());

SIMPLE_TEST(StableKSmallestElements_Sort, TestSAMPLE1, EXPECTED1,
            VALUES1, EXPECTED1.size());
SIMPLE_TEST(StableKSmallestElements_Sort, TestSAMPLE2, EXPECTED2,
            VALUES2, EXPECTED2.size());
SIMPLE_TEST(StableKSmallestElements_Sort, TestSAMPLE3, VALUES1,
            VALUES1, VALUES1.size());


THE_BENCHMARK(StableKSmallestElements_Insertion, VALUES1, EXPECTED1.size());

SIMPLE_TEST(StableKSmallestElements_Insertion, TestSAMPLE1, EXPECTED1,
            VALUES1, EXPECTED1.size());
SIMPLE_TEST(StableKSmallestElements_Insertion, TestSAMPLE2, EXPECTED2,
            VALUES2, EXPECTED2.size());
SIMPLE_TEST(StableKSmallestElements_Insertion, TestSAMPLE3, VALUES1,
            VALUES1, VALUES1.size());
