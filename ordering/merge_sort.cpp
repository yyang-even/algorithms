#include "common_header.h"

#include "merge_sort.h"
#include "merge_two_sorted_arrays.h"

using ArrayType = std::vector<int>;


/** Merge Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 2.3.
 *
 *              http://www.geeksforgeeks.org/merge-sort/
 *
 * @complexity: O(n*lgn)
 */
void Merge(const ArrayType::iterator begin, const ArrayType::iterator middle,
           const ArrayType::iterator end) {
    const auto L = ArrayType(begin, middle);
    const auto R = ArrayType(middle, end);

    MergeTwoSortedArrays(L, R, begin);
}
auto MergeSort(ArrayType values) {
    MergeSort<ArrayType>(values.begin(), values.size(), Merge);
    return values;
}


/** Iterative Merge Sort
 *
 * @reference   https://www.geeksforgeeks.org/iterative-merge-sort/
 *
 * Merge subarrays in bottom up manner. First merge subarrays of size 1
 * to create sorted subarrays of size 2, then merge subarrays of size 2
 * to create sorted subarrays of size 4, and so on.
 */
auto MergeSortIterative(ArrayType values) {
    for (ArrayType::size_type current_size = 1; current_size < values.size(); current_size *= 2) {
        for (ArrayType::size_type i = 0ul; i < (values.size() - 1);) {
            const auto begin = values.begin() + i;
            const auto mid = begin + current_size;
            i += current_size * 2;
            const auto end = values.begin() + std::min(i, values.size());
            Merge(begin, mid, end);
        }
    }
    return values;
}


/** Merge Sort with O(1) extra space merge and O(n lg n) time
 *
 * @reference   https://www.geeksforgeeks.org/merge-sort-with-o1-extra-space-merge-and-on-lg-n-time/
 *
 * How to modify the algorithm so that merge works in O(1) extra space and algorithm still works in O(n Log n) time.
 */
void MergeO1(const ArrayType::iterator begin, const ArrayType::iterator middle,
             const ArrayType::iterator end, const ArrayType::value_type max) {
    auto L_iter = begin;
    auto R_iter = middle;
    auto iter = begin;
    for (; (L_iter != middle) and (R_iter != end); ++iter) {
        if (*L_iter % max <= *R_iter) {
            *iter = *iter + (*L_iter++ % max) * max;
        } else {
            *iter = *iter + (*R_iter++) * max;
        }
    }

    std::transform(L_iter, middle, iter, iter,
    [max](const ArrayType::value_type v1, const ArrayType::value_type v2) {
        return v2 + (v1 % max) * max;
    });

    // Restore to original values
    std::transform(begin, R_iter, begin, [max](const ArrayType::value_type v) {
        return v / max;
    });
}
auto MergeSortO1(ArrayType values) {
    if (not values.empty()) {
        const auto max_element = *std::max_element(values.cbegin(), values.cend()) + 1;
        MergeSort<ArrayType>(values.begin(), values.size(), [max_element](const ArrayType::iterator begin,
        const ArrayType::iterator middle, const ArrayType::iterator end) {
            MergeO1(begin, middle, end, max_element);
        });
    }
    return values;
}


/** The external merge sort algorithm
 *
 * @reference   External Sorting
 *              https://www.geeksforgeeks.org/external-sorting/
 *
 * External sorting is a term for a class of sorting algorithms that can handle massive
 * amounts of data. External sorting is required when the data being sorted do not fit
 * into the main memory of a computing device (usually RAM) and instead they must reside
 * in the slower external memory (usually a hard drive). External sorting typically uses
 * a hybrid sort-merge strategy. In the sorting phase, chunks of data small enough to fit
 * in main memory are read, sorted, and written out to a temporary file. In the merge phase,
 * the sorted sub-files are combined into a single larger file.
 */


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType EXPECTED4 = {1, 2, 3};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType EXPECTED5 = {1, 2, 3, 4};

SIMPLE_BENCHMARK(MergeSort, VALUES5);

SIMPLE_TEST(MergeSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSort, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(MergeSortO1, VALUES5);

SIMPLE_TEST(MergeSortO1, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSortO1, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSortO1, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSortO1, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSortO1, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(MergeSortIterative, VALUES5);

SIMPLE_TEST(MergeSortIterative, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSortIterative, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSortIterative, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSortIterative, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSortIterative, TestSAMPLE5, EXPECTED5, VALUES5);
