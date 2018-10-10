#include "common_header.h"


using ArrayType = std::vector<unsigned>;

/** Find the Number Occurring Odd Number of Times
 *
 * @reference   https://www.geeksforgeeks.org/find-the-number-occurring-odd-number-of-times/
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


const ArrayType SAMPLE1 = {1, 2, 3, 2, 3, 1, 3};
const ArrayType SAMPLE2 = {5, 7, 2, 7, 5, 2, 5};
const ArrayType SAMPLE3 = {2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 4, 2};

SIMPLE_BENCHMARK(FindTheOddNumber, SAMPLE1);

SIMPLE_TEST(FindTheOddNumber, TestSample1, 3, SAMPLE1);
SIMPLE_TEST(FindTheOddNumber, TestSample2, 5, SAMPLE2);
SIMPLE_TEST(FindTheOddNumber, TestSample3, 5, SAMPLE3);
