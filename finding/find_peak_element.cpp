#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find a peak element
 *
 * @reference   https://www.geeksforgeeks.org/find-a-peak-in-a-given-array/
 *
 * Given an array of integers. Find a peak element in it. An array element is peak if it
 * is NOT smaller than its neighbors. For corner elements, we need to consider only one
 * neighbor. For example, for input array {5, 10, 20, 15}, 20 is the only peak element.
 * For input array {10, 20, 15, 2, 23, 90, 67}, there are two peak elements: 20 and 90.
 * Note that we need to return any one peak element.
 *
 * @reference   Find the maximum element in an array which is first increasing and then decreasing
 *              https://www.geeksforgeeks.org/find-the-maximum-element-in-an-array-which-is-first-increasing-and-then-decreasing/
 */
auto FindOnePeakElement(const ArrayType &elements,
                        const ArrayType::const_iterator cbegin,
                        const ArrayType::size_type length) {
    const auto half = length / 2;
    const auto mid = cbegin + half;
    const auto mid_next = std::next(mid);

    if ((mid == elements.cbegin() or * std::prev(mid) <= *mid)
        and (mid_next == elements.cend() or * mid_next <= *mid)) {
        return mid;
    }
    if (mid != elements.cbegin() and * std::prev(mid) > *mid) {
        return FindOnePeakElement(elements, cbegin, half);
    }
    return FindOnePeakElement(elements, mid_next, length - half - 1);
}

inline auto
FindOnePeakElement(const ArrayType &elements) {
    return *FindOnePeakElement(elements, elements.cbegin(), elements.size());
}


/** Find a local minima in an array
 *
 * @reference   https://www.geeksforgeeks.org/find-local-minima-array/
 *
 * Given an array arr[0 .. n-1] of distinct integers, the task is to find a local minima
 * in it. We say that an element arr[x] is a local minimum if it is less than or equal
 * to both its neighbors.
 *
 * @reference   Minimum in an array which is first decreasing then increasing
 *              https://www.geeksforgeeks.org/minimum-in-an-array-which-is-first-decreasing-then-increasing/
 */


/** Check if an array is increasing or decreasing
 *
 * @reference   https://www.geeksforgeeks.org/check-if-an-array-is-increasing-or-decreasing/
 *
 * Given an array arr[] of N elements where N >= 2, the task is to check the type of
 * array whether it is:
 *  1. Increasing.
 *  2. Decreasing.
 *  3. Increasing then decreasing.
 *  4. Decreasing then increasing.
 * Note that the given array is definitely one of the given types.
 */

}//namespace


const ArrayType SAMPLE1 = {5, 10, 20, 15};
const ArrayType INCREASING = {10, 20, 30, 40, 50};
const ArrayType DECREASING = {100, 80, 60, 50, 20};
const ArrayType ALL_SAME = {10, 10, 10, 10, 10};


THE_BENCHMARK(FindOnePeakElement, SAMPLE1);

SIMPLE_TEST(FindOnePeakElement, TestSAMPLE1, 20, SAMPLE1);
SIMPLE_TEST(FindOnePeakElement, TestINCREASING, INCREASING.back(), INCREASING);
SIMPLE_TEST(FindOnePeakElement, TestDECREASING, DECREASING.front(), DECREASING);
SIMPLE_TEST(FindOnePeakElement, TestALL_SAME, ALL_SAME.back(), ALL_SAME);
