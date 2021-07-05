#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Find the Number Occurring Odd Number of Times
 *
 * @reference   https://www.geeksforgeeks.org/find-the-number-occurring-odd-number-of-times/
 * @reference   Find the element that appears once in an array where every other element appears twice
 *              https://www.geeksforgeeks.org/find-element-appears-array-every-element-appears-twice/
 * @reference   Find single in an array of 2n+1 integer elements
 *              https://www.geeksforgeeks.org/find-single-array-2n1-integer-elements/
 * @reference   Single Number
 *              https://leetcode.com/problems/single-number/
 *
 * Given an array of positive integers. All numbers occur even number of times except one
 * number which occurs odd number of times. Find the number in O(n) time & constant space.
 *
 * @complexity  O(n)
 */
inline auto FindTheOddNumber(const ArrayType &values) {
    return std::accumulate(values.cbegin(), values.cend(), 0u,
                           std::bit_xor<ArrayType::value_type> {});
}


/** Find the element that appears once in a sorted array
 *
 * @reference   https://www.geeksforgeeks.org/find-the-element-that-appears-once-in-a-sorted-array/
 *
 * Given a sorted array in which all elements appear twice (one after one) and one
 * element appears only once. Find that element in O(log n) complexity.
 */
auto FindTheOddNumber_Sorted_BinarySearch(const ArrayType &values,
                                          const ArrayType::size_type low,
                                          const ArrayType::size_type high) {
    if (low == high) {
        return low;
    }

    const auto mid = (low + high) / 2;
    if (mid % 2 == 0) {
        if (values[mid] == values[mid + 1]) {
            return FindTheOddNumber_Sorted_BinarySearch(values, mid + 2, high);
        } else {
            return FindTheOddNumber_Sorted_BinarySearch(values, low, mid);
        }
    } else {
        if (values[mid] == values[mid - 1]) {
            return FindTheOddNumber_Sorted_BinarySearch(values, mid + 1, high);
        } else {
            return FindTheOddNumber_Sorted_BinarySearch(values, low, mid - 1);
        }
    }
}

inline auto FindTheOddNumber_Sorted_BinarySearch(const ArrayType &values) {
    assert(not values.empty());
    assert(std::is_sorted(values.cbegin(), values.cend()));

    return values[FindTheOddNumber_Sorted_BinarySearch(values, 0, values.size() - 1)];
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3, 2, 3, 1, 3};
const ArrayType SAMPLE2 = {5, 7, 2, 7, 5, 2, 5};
const ArrayType SAMPLE3 = {2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 4, 2};
const ArrayType SAMPLE4 = {7, 3, 5, 4, 5, 3, 4};


THE_BENCHMARK(FindTheOddNumber, SAMPLE1);

SIMPLE_TEST(FindTheOddNumber, TestSample1, 3, SAMPLE1);
SIMPLE_TEST(FindTheOddNumber, TestSample2, 5, SAMPLE2);
SIMPLE_TEST(FindTheOddNumber, TestSample3, 5, SAMPLE3);
SIMPLE_TEST(FindTheOddNumber, TestSample4, 7, SAMPLE4);


const ArrayType SORTED_SAMPLE1 = {1, 2, 2, 4, 4, 5, 5, 6, 6};
const ArrayType SORTED_SAMPLE2 = {1, 1, 2, 4, 4, 5, 5, 6, 6};
const ArrayType SORTED_SAMPLE3 = {1, 1, 2, 2, 4, 4, 5, 5, 6};


THE_BENCHMARK(FindTheOddNumber_Sorted_BinarySearch, SORTED_SAMPLE1);

SIMPLE_TEST(FindTheOddNumber_Sorted_BinarySearch, TestFront, SORTED_SAMPLE1.front(),
            SORTED_SAMPLE1);
SIMPLE_TEST(FindTheOddNumber_Sorted_BinarySearch, TestSample2, 2, SORTED_SAMPLE2);
SIMPLE_TEST(FindTheOddNumber_Sorted_BinarySearch, TestBack, SORTED_SAMPLE3.back(),
            SORTED_SAMPLE3);
