#include "common_header.h"

#include <stack>

namespace {
using ArrayType = std::vector<int>;

/** QuickSort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 7.
 * @reference   https://www.geeksforgeeks.org/quick-sort/
 * @reference   When does the worst case of Quicksort occur?
 *              https://www.geeksforgeeks.org/when-does-the-worst-case-of-quicksort-occur/
 * @reference   Generic Implementation of QuickSort Algorithm in C
 *              https://www.geeksforgeeks.org/generic-implementation-of-quicksort-algorithm-in-c/
 * @reference   C++ Program for QuickSort
 *              https://www.geeksforgeeks.org/cpp-program-for-quicksort/
 * @reference   Why quicksort is better than mergesort ?
 *              https://www.geeksforgeeks.org/quicksort-better-mergesort/
 * @reference   Why Quick Sort preferred for Arrays and Merge Sort for Linked Lists?
 *              https://www.geeksforgeeks.org/why-quick-sort-preferred-for-arrays-and-merge-sort-for-linked-lists/
 * @reference   Quick Sort vs Merge Sort
 *              https://www.geeksforgeeks.org/quick-sort-vs-merge-sort/
 * @reference   Iterative Quick Sort
 *              https://www.geeksforgeeks.org/iterative-quick-sort/
 * @reference   C Program for Iterative Quick Sort
 *              https://www.geeksforgeeks.org/c-program-for-iterative-quick-sort/
 * @reference   Tail Recursion
 *              https://www.geeksforgeeks.org/tail-recursion/
 * @reference   Tail Call Elimination
 *              https://www.geeksforgeeks.org/tail-call-elimination/
 * @reference   QuickSort Tail Call Optimization (Reducing worst case space to Log n )
 *              https://www.geeksforgeeks.org/quicksort-tail-call-optimization-reducing-worst-case-space-log-n/
 * @reference   Hoare’s vs Lomuto partition scheme in QuickSort
 *              https://www.geeksforgeeks.org/hoares-vs-lomuto-partition-scheme-quicksort/
 * Hoare’s scheme is more efficient than Lomuto’s partition scheme because it does three times fewer
 * swaps on average, and it creates efficient partitions even when all values are equal.
 * @reference   QuickSort using Random Pivoting
 *              https://www.geeksforgeeks.org/quicksort-using-random-pivoting/
 * @reference   Stable QuickSort
 *              https://www.geeksforgeeks.org/stable-quicksort/
 * @reference   Stability in sorting algorithms
 *              https://www.geeksforgeeks.org/stability-in-sorting-algorithms/
 *
 * @complexity  T(n) = T(k) + T(n-k-1) + O(n)
 * @complexity  O(nLogn)
 */
auto partitionLomuto(const ArrayType::iterator begin, const ArrayType::size_type size) {
    const auto pivot = begin + (size - 1);
    ArrayType::size_type mid = 0;
    for (auto iter = begin; iter != pivot; ++iter) {
        if (*iter <= *pivot) {
            std::iter_swap(iter, (begin + mid++));
        }
    }
    std::iter_swap(pivot, begin + mid);

    return mid;
}

auto partitionHoare(const ArrayType::iterator begin, const ArrayType::size_type size) {
    const auto pivot = begin;
    auto left = begin;
    auto mid = size - 1;    //to avoid right - left, which is more expensive
    auto right = begin + mid;

    while (true) {
        for (; *left < *pivot; ++left);
        for (; *right > *pivot; --right, --mid);

        if (left >= right) {
            break;
        }
        std::iter_swap(left, right);
    }

    return mid;
}

auto partitionRandomizedHoare(const ArrayType::iterator begin, const ArrayType::size_type size) {
    const auto random_pivot_index = Random_Number<ArrayType::size_type>(0, size - 1);
    std::iter_swap(begin, begin + random_pivot_index);
    return partitionHoare(begin, size);
}

auto partitionStable(const ArrayType::iterator begin, const ArrayType::size_type size) {
    const auto pivot = begin + (size - 1);
    ArrayType::size_type mid = 0;
    ArrayType smaller, greater;

    for (auto iter = begin; iter != pivot; ++iter) {
        if (*iter <= *pivot) {
            smaller.push_back(*iter);
            ++mid;
        } else {
            greater.push_back(*iter);
        }
    }
    std::copy(smaller.cbegin(), smaller.cend(), begin);
    const auto mid_iter = begin + mid;
    std::iter_swap(pivot, mid_iter);
    std::copy(greater.cbegin(), greater.cend(), mid_iter + 1);

    return mid;
}


template <typename PartitionFunc>
void QuickSort(const ArrayType::iterator begin, const ArrayType::size_type size,
               const PartitionFunc partition) {
    if (size > 1) {
        const auto mid = partition(begin, size);
        QuickSort(begin, mid, partition);
        const auto mid_plus_one = mid + 1;
        QuickSort(begin + mid_plus_one, size - mid_plus_one, partition);
    }
}
auto QuickSortLomuto(ArrayType values) {
    QuickSort(values.begin(), values.size(), &partitionLomuto);
    return values;
}


auto QuickSortHoare(ArrayType values) {
    QuickSort(values.begin(), values.size(), &partitionHoare);
    return values;
}


auto QuickSortIterative(ArrayType values) {
    if (values.size() > 1) {
        std::stack<std::pair<const ArrayType::iterator, const ArrayType::size_type> > range_stack;
        range_stack.emplace(values.begin(), values.size());

        while (not range_stack.empty()) {
            const auto range = range_stack.top();
            range_stack.pop();
            const auto mid = partitionLomuto(range.first, range.second);
            if (mid > 1) {
                range_stack.emplace(range.first, mid);
            }
            const auto mid_plus_one = mid + 1;
            const auto right_size = range.second - mid_plus_one;
            if (right_size > 1) {
                range_stack.emplace(range.first + mid_plus_one, right_size);
            }
        }
    }

    return values;
}


auto QuickSortRandomizedHoare(ArrayType values) {
    QuickSort(values.begin(), values.size(), &partitionRandomizedHoare);
    return values;
}


auto QuickSortStable(ArrayType values) {
    QuickSort(values.begin(), values.size(), &partitionStable);
    return values;
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType EXPECTED4 = {1, 2, 3};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType EXPECTED5 = {1, 2, 3, 4};

SIMPLE_BENCHMARK(QuickSortLomuto, VALUES5);

SIMPLE_TEST(QuickSortLomuto, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortLomuto, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortLomuto, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortLomuto, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortLomuto, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(QuickSortIterative, VALUES5);

SIMPLE_TEST(QuickSortIterative, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortIterative, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortIterative, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortIterative, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortIterative, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(QuickSortHoare, VALUES5);

SIMPLE_TEST(QuickSortHoare, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortHoare, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortHoare, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortHoare, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortHoare, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(QuickSortRandomizedHoare, VALUES5);

SIMPLE_TEST(QuickSortRandomizedHoare, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortRandomizedHoare, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortRandomizedHoare, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortRandomizedHoare, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortRandomizedHoare, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(QuickSortStable, VALUES5);

SIMPLE_TEST(QuickSortStable, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortStable, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortStable, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortStable, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortStable, TestSAMPLE5, EXPECTED5, VALUES5);
