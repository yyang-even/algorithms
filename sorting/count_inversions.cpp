#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

using ArrayType = std::vector<int>;

/** Count Inversions in an array | Set 1 (Using Merge Sort)
 *
 * @reference   Count Inversions in an array | Set 1 (Using Merge Sort)
 *              https://www.geeksforgeeks.org/counting-inversions/
 *
 * Inversion Count for an array indicates – how far (or close) the array is from being sorted.
 * If array is already sorted then inversion count is 0. If array is sorted in reverse order
 * that inversion count is the maximum.
 * Formally speaking, two elements a[i] and a[j] form an inversion if a[i] > a[j] and i < j
 *
 * Example:
 * The sequence 2, 4, 1, 3, 5 has three inversions (2, 1), (4, 1), (4, 3).
 *
 * @complexity: O(n*lgn)
 */
auto Merge(const ArrayType::iterator begin, const ArrayType::iterator middle,
           const ArrayType::iterator end) {
    const auto L = ArrayType(begin, middle);
    const auto R = ArrayType(middle, end);

    auto iter = begin;
    auto L_iter = L.cbegin();
    auto R_iter = R.cbegin();
    unsigned inversion_count = 0u;
    for (; (L_iter != L.cend()) and (R_iter != R.cend()); ++iter) {
        if (*L_iter <= *R_iter) {
            *iter = *L_iter;
            ++L_iter;
        } else {
            *iter = *R_iter;
            ++R_iter;
            inversion_count += (L.cend() - L_iter);
        }
    }

    while (L_iter != L.cend()) {
        *iter++ = *L_iter++;
    }
    while (R_iter != R.cend()) {
        *iter++ = *R_iter++;
    }
    return inversion_count;
}
unsigned MergeSort(const ArrayType::iterator begin, const ArrayType::size_type n) {
    if (n > 1) {
        const auto middle = n >> 1; //floor(n/2)
        const auto middle_begin = begin + middle;
        const auto left_inversion_count = MergeSort(begin, middle);
        const auto right_inversion_count = MergeSort(middle_begin, n - middle);
        return left_inversion_count + right_inversion_count + Merge(begin, middle_begin, begin + n);
    }
    return 0u;
}
auto CountInversionsMergeSort(ArrayType values) {
    return MergeSort(values.begin(), values.size());
}


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType VALUES6 = {1, 20, 6, 4, 5};
const ArrayType VALUES7 = {2, 4, 1, 3, 5};

SIMPLE_TEST(CountInversionsMergeSort, TestSAMPLE1, 0, VALUES1);
SIMPLE_TEST(CountInversionsMergeSort, TestSAMPLE2, 0, VALUES2);
SIMPLE_TEST(CountInversionsMergeSort, TestSAMPLE3, 0, VALUES3);
SIMPLE_TEST(CountInversionsMergeSort, TestSAMPLE4, 2, VALUES4);
SIMPLE_TEST(CountInversionsMergeSort, TestSAMPLE5, 6, VALUES5);
SIMPLE_TEST(CountInversionsMergeSort, TestSAMPLE6, 5, VALUES6);
SIMPLE_TEST(CountInversionsMergeSort, TestSAMPLE7, 3, VALUES7);
