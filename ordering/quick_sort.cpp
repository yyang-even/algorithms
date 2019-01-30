#include "common_header.h"

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
 *
 * @complexity  T(n) = T(k) + T(n-k-1) + O(n)
 * @complexity  O(nLogn)
 */
auto partition(const ArrayType::iterator begin, const ArrayType::size_type size) {
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
void QuickSort(const ArrayType::iterator begin, const ArrayType::size_type size) {
    if (size > 1) {
        const auto mid = partition(begin, size);
        QuickSort(begin, mid);
        const auto mid_plus_one = mid + 1;
        QuickSort(begin + mid_plus_one, size - mid_plus_one);
    }
}
auto QuickSort(ArrayType values) {
    QuickSort(values.begin(), values.size());
    return values;
}


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType EXPECTED4 = {1, 2, 3};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType EXPECTED5 = {1, 2, 3, 4};

SIMPLE_BENCHMARK(QuickSort, VALUES5);

SIMPLE_TEST(QuickSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSort, TestSAMPLE5, EXPECTED5, VALUES5);
