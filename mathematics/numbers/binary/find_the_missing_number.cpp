#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Find the Missing Number
 *
 * @reference   https://www.geeksforgeeks.org/find-the-missing-number/
 *
 * You are given a list of n-1 integers and these integers are in the range of 1 to n.
 * There are no duplicates in list. One of the integers is missing in the list.
 * Write an efficient code to find the missing integer.
 *
 * @complexity  O(n)
 */
auto FindTheMissingNumber_Sum(const ArrayType &integers) {
    assert(not integers.empty());

    const auto N = integers.size() + 1u;
    const auto sum = N * (N + 1) / 2;
    return std::accumulate(integers.cbegin(), integers.cend(), sum, std::minus<ArrayType::value_type> {});
}


auto FindTheMissingNumber_Xor(const ArrayType &integers, ArrayType::value_type min = 1) {
    assert(not integers.empty());

    const ArrayType::value_type N = integers.size() + min;
    auto xor_of_all = integers[0] ^ min++;
    for (ArrayType::size_type i = 1ul; i < integers.size(); ++i) {
        xor_of_all ^= (min++ ^ integers[i]);
    }

    return xor_of_all ^ N;
}

/** Find the one missing number in range
 *
 * @reference   https://www.geeksforgeeks.org/find-one-missing-number-range/
 *
 * Given an array of size n. It is also given that range of numbers is from smallestNumber
 * to smallestNumber + n where smallestNumber is the smallest number in array. The array
 * contains number in this range but one number is missing so the task is to find this
 * missing number.
 */
auto FindTheMissingNumberRange_Xor(const ArrayType &integers) {
    const auto min = std::min_element(integers.cbegin(), integers.cend());

    return FindTheMissingNumber_Xor(integers, *min);
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 4, 6, 3, 7, 8};
const ArrayType SAMPLE2 = {1, 2, 4, 5, 6};


SIMPLE_BENCHMARK(FindTheMissingNumber_Sum, SAMPLE1);

SIMPLE_TEST(FindTheMissingNumber_Sum, TestSample1, 5u, SAMPLE1);
SIMPLE_TEST(FindTheMissingNumber_Sum, TestSample2, 3u, SAMPLE2);


SIMPLE_BENCHMARK(FindTheMissingNumber_Xor, SAMPLE1);

SIMPLE_TEST(FindTheMissingNumber_Xor, TestSample1, 5u, SAMPLE1);
SIMPLE_TEST(FindTheMissingNumber_Xor, TestSample2, 3u, SAMPLE2);


const ArrayType SAMPLE3 = {13, 12, 11, 15};
const ArrayType SAMPLE4 = {33, 36, 35, 34};


SIMPLE_BENCHMARK(FindTheMissingNumberRange_Xor, SAMPLE1);

SIMPLE_TEST(FindTheMissingNumberRange_Xor, TestSample1, 5u, SAMPLE1);
SIMPLE_TEST(FindTheMissingNumberRange_Xor, TestSample2, 3u, SAMPLE2);
SIMPLE_TEST(FindTheMissingNumberRange_Xor, TestSample3, 14u, SAMPLE3);
SIMPLE_TEST(FindTheMissingNumberRange_Xor, TestSample4, 37u, SAMPLE4);
