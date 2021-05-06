#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

#include "is_k_sorted_array.h"

/** Check if given array is almost sorted (elements are at-most one position away)
 *
 * @reference   https://www.geeksforgeeks.org/check-given-array-almost-sorted-elements-one-position-away/
 *
 * Given an array with n distinct elements. An array is said to be almost sorted
 * (non-decreasing) if any of its elements can occur at a maximum of 1 distance away
 * from their original places in the sorted array. We need to find whether the given
 * array is almost sorted or not.
 */
auto IsAlmostSorted_Bubble(ArrayType values) {
    for (auto iter = values.begin(); iter != std::prev(values.end());) {
        auto next = std::next(iter);
        if (*next < *iter) {
            std::iter_swap(next++, iter);
        }
        iter = next;
    }

    return std::is_sorted(values.cbegin(), values.cend());
}

}//namespace


const ArrayType SampleArray1 = {3, 2, 1, 5, 6, 4};
const ArrayType SampleArray2 = {13, 8, 10, 7, 15, 14, 12};
const ArrayType SampleArray3 = {1, 3, 2, 4};
const ArrayType SampleArray4 = {1, 4, 2, 3};


THE_BENCHMARK(IsKSorted, SampleArray1, 2);

SIMPLE_TEST(IsKSorted, TestSample1, true, SampleArray1, 2);
SIMPLE_TEST(IsKSorted, TestSample2, false, SampleArray2, 3);
SIMPLE_TEST(IsKSorted, TestSample3, true, SampleArray3, 1);
SIMPLE_TEST(IsKSorted, TestSample4, false, SampleArray4, 1);


THE_BENCHMARK(IsAlmostSorted_Bubble, SampleArray3);

SIMPLE_TEST(IsAlmostSorted_Bubble, TestSample3, true, SampleArray3);
SIMPLE_TEST(IsAlmostSorted_Bubble, TestSample4, false, SampleArray4);
