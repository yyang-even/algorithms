#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Program for Mean and median of an unsorted array
 *
 * @reference   https://www.geeksforgeeks.org/program-for-mean-and-median-of-an-unsorted-array/
 *
 * Mean of an array = (sum of all elements) / (number of elements)
 */
inline auto Mean(const ArrayType &values) {
    assert(not values.empty());

    const double sum = std::accumulate(values.cbegin(), values.cend(), 0);
    return sum / values.size();
}


/**
 * @reference   Mean of array using recursion
 *              https://www.geeksforgeeks.org/mean-of-array-using-recursion/
 */


/**
 * @reference   Compute average of two numbers without overflow
 *              https://www.geeksforgeeks.org/compute-average-two-numbers-without-overflow/
 */
constexpr inline auto Average_NoOverflow(const int a, const int b) {
    return (a / 2) + (b / 2) + ((a % 2 + b % 2) / 2);
}


/**
 * @reference   Find average of two numbers using bit operation
 *              https://www.geeksforgeeks.org/find-average-of-two-numbers-using-bit-operation/
 * @reference   Fast average of two numbers without division
 *              https://www.geeksforgeeks.org/fast-average-two-numbers-without-division/
 */
constexpr inline auto Average_Bit(const int a, const int b) {
    return (a & b) + ((a ^ b) >> 1);
}

}//namespace


const ArrayType VALUES1 = {1};
const ArrayType VALUES2 = {1, 2};
const ArrayType VALUES3 = {2, 3, 1};
const ArrayType VALUES4 = {1, 3, 4, 2, 6, 5, 8, 7};
const ArrayType VALUES5 = {4, 4, 4, 4, 4};


THE_BENCHMARK(Mean, VALUES4);

SIMPLE_DOUBLE_TEST(Mean, TestSAMPLE1, 1, VALUES1);
SIMPLE_DOUBLE_TEST(Mean, TestSAMPLE2, 1.5, VALUES2);
SIMPLE_DOUBLE_TEST(Mean, TestSAMPLE3, 2, VALUES3);
SIMPLE_DOUBLE_TEST(Mean, TestSAMPLE4, 4.5, VALUES4);
SIMPLE_DOUBLE_TEST(Mean, TestSAMPLE5, 4, VALUES5);


constexpr auto UPPER = std::numeric_limits<int>::max();


THE_BENCHMARK(Average_NoOverflow, UPPER, UPPER);

SIMPLE_TEST(Average_NoOverflow, TestSAMPLE1, UPPER, UPPER, UPPER);
SIMPLE_TEST(Average_NoOverflow, TestSAMPLE2, 3, 2, 4);
SIMPLE_TEST(Average_NoOverflow, TestSAMPLE3, 9, 10, 9);


THE_BENCHMARK(Average_Bit, UPPER, UPPER);

SIMPLE_TEST(Average_Bit, TestSAMPLE1, UPPER, UPPER, UPPER);
SIMPLE_TEST(Average_Bit, TestSAMPLE2, 3, 2, 4);
SIMPLE_TEST(Average_Bit, TestSAMPLE3, 9, 10, 9);
