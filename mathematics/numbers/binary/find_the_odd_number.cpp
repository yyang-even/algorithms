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
 *
 * Given an array of positive integers. All numbers occur even number of times
 * except one number which occurs odd number of times. Find the number in O(n)
 * time & constant space.
 *
 * @complexity  O(n)
 */
auto FindTheOddNumber(const ArrayType &values) {
    return std::accumulate(values.cbegin(), values.cend(), 0u, std::bit_xor<ArrayType::value_type> {});
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3, 2, 3, 1, 3};
const ArrayType SAMPLE2 = {5, 7, 2, 7, 5, 2, 5};
const ArrayType SAMPLE3 = {2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 4, 2};
const ArrayType SAMPLE4 = {7, 3, 5, 4, 5, 3, 4};


SIMPLE_BENCHMARK(FindTheOddNumber, SAMPLE1);

SIMPLE_TEST(FindTheOddNumber, TestSample1, 3u, SAMPLE1);
SIMPLE_TEST(FindTheOddNumber, TestSample2, 5u, SAMPLE2);
SIMPLE_TEST(FindTheOddNumber, TestSample3, 5u, SAMPLE3);
SIMPLE_TEST(FindTheOddNumber, TestSample4, 7u, SAMPLE4);
