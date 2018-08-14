#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

using ArrayType = std::vector<int>;


void MergeSort(const ArrayType::iterator begin, const ArrayType::size_type n, const std::function<void(const ArrayType::iterator, const ArrayType::iterator, const ArrayType::iterator)> merge) {
    if (n > 1) {
        const auto middle = n >> 1; //floor(n/2)
        const auto middle_begin = begin + middle;
        MergeSort(begin, middle);
        MergeSort(middle_begin, n - middle);
        merge(begin, middle_begin, begin + n);
    }
}
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

    auto iter = begin;
    auto L_iter = L.cbegin();
    auto R_iter = R.cbegin();
    for (; (L_iter != L.cend()) and (R_iter != R.cend()); ++iter) {
        if (*L_iter <= *R_iter) {
            *iter = *L_iter++;
        } else {
            *iter = *R_iter++;
        }
    }

    while (L_iter != L.cend()) {
        *iter++ = *L_iter++;
    }
    while (R_iter != R.cend()) {
        *iter++ = *R_iter++;
    }
}
auto MergeSort(ArrayType values) {
    MergeSort(values.begin(), values.size(), Merge);
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
    auto R_iter = mid;
    auto iter = begin;
    for (; (L_iter != mid) and (R_iter != end); ++iter) {
        if (*L_iter % max <= *R_iter % max) {
            *iter = *iter + (*L_iter++ % max) * max;
        } else {
            *iter = *iter + (*R_iter++ % max) * max;
        }
    }

    for (;L_iter != L.cend(); ++iter) {
            *iter = *iter + (*L_iter++ % max) * max;
    }
    for (;R_iter != R.cend(); ++iter) {
            *iter = *iter + (*R_iter++ % max) * max;
    }

    for(iter = begin; iter != end; ++iter) {
        *iter = *iter / max;
    }
}
auto MergeSortO1(ArrayType values) {
    const auto max_element = *std::max_element(values.cbegin(), values.cend()) + 1;
    MergeSort(values.begin(), values.size(), [max_element](const ArrayType::iterator begin, const ArrayType::iterator middle,
           const ArrayType::iterator end){
            MergeO1(begin, middle, end, max_element);
            });
    return values;
}


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType EXPECTED4 = {1, 2, 3};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType EXPECTED5 = {1, 2, 3, 4};

SIMPLE_BENCHMARK(MergeSort, SAMPLE_ARRAYS);

SIMPLE_TEST(MergeSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSort, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(MergeSortO1, SAMPLE_ARRAYS);

SIMPLE_TEST(MergeSortO1, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSortO1, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSortO1, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSortO1, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSortO1, TestSAMPLE5, EXPECTED5, VALUES5);
