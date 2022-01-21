#include "common_header.h"

#include "calculate_xor_of_all_numbers_1_to_n.h"


namespace {

/**
 * @reference   XOR Operation in an Array
 *              https://leetcode.com/problems/xor-operation-in-an-array/
 *
 * You are given an integer n and an integer start.
 * Define an array nums where nums[i] = start + 2 * i (0-indexed) and n == nums.length.
 * Return the bitwise XOR of all elements of nums.
 */
inline constexpr auto XorOperationB(const unsigned n, const unsigned start) {
    if (n % 2 == 0) {
        return (n / 2) & 1;
    } else {
        return ((n / 2) & 1) ^ (start + n - 1);
    }
}

inline constexpr auto XorOperationA(const unsigned n, const unsigned start) {
    if (start & 1) {
        return (start - 1) ^ XorOperationB(n + 1, start - 1);
    } else {
        return XorOperationB(n, start);
    }
}

inline constexpr auto XorOperation(const unsigned n, const unsigned start) {
    const auto result = 2 * XorOperationA(n, start / 2);
    return (n & start & 1) ? result + 1 : result;
}

}//namespace


THE_BENCHMARK(XorOfAllFrom1toN, 4);

SIMPLE_TEST(XorOfAllFrom1toN, TestLOWER, 0, 0);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample1, 1, 1);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample2, 3, 2);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample3, 3, 2);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample4, 0, 3);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample5, 1, 5);


THE_BENCHMARK(XorOperation, 5, 0);

SIMPLE_TEST(XorOperation, TestSample1, 8, 5, 0);
SIMPLE_TEST(XorOperation, TestSample2, 8, 4, 3);
