#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Count number of occurrences (or frequency) in a sorted array
 *
 * @reference   https://www.geeksforgeeks.org/count-number-of-occurrences-or-frequency-in-a-sorted-array/
 *
 * Given a sorted array arr[] and a number x, write a function that counts the
 * occurrences of x in arr[]. Expected time complexity is O(Logn)
 *
 * @reference   Count 1’s in a sorted binary array
 *              https://www.geeksforgeeks.org/count-of-only-repeated-element-in-a-sorted-array-of-consecutive-elements/
 *
 * Given a sorted array of consecutive elements. The array has only one element repeated
 * many times. The task is to find length of the sequence of repeated element.
 * Expected Time Complexity : Less than 0(n)
 *
 * @reference   Find the number of zeroes
 *              https://www.geeksforgeeks.org/find-number-zeroes/
 *
 * Given an array of 1s and 0s which has all 1s first followed by all 0s. Find the number
 * of 0s. Count the number of zeroes in the given array.
 *
 * @highlight   The use of std::equal_range()
 */
inline auto CountOccurrencesInSortedArray_STL(const ArrayType &values,
                                              const ArrayType::value_type x) {
    assert(std::is_sorted(values.cbegin(), values.cend()));

    const auto [lower, upper] = std::equal_range(values.cbegin(), values.cend(), x);
    return upper - lower;
}

}//namespace


const ArrayType VALUES1 = {1, 1, 2, 2, 2, 2, 3};


THE_BENCHMARK(CountOccurrencesInSortedArray_STL, VALUES1, 2);

SIMPLE_TEST(CountOccurrencesInSortedArray_STL, TestSAMPLE1, 2, VALUES1, 1);
SIMPLE_TEST(CountOccurrencesInSortedArray_STL, TestSAMPLE2, 4, VALUES1, 2);
SIMPLE_TEST(CountOccurrencesInSortedArray_STL, TestSAMPLE3, 1, VALUES1, 3);
SIMPLE_TEST(CountOccurrencesInSortedArray_STL, TestSAMPLE4, 0, VALUES1, 4);
