#include "common_header.h"

#include "find_most_significant_bit.h"


namespace {

/**
 * @reference   Bitwise AND of Numbers Range
 *              https://leetcode.com/problems/bitwise-and-of-numbers-range/
 *
 * Given two integers left and right that represent the range [left, right], return the
 * bitwise AND of all numbers in this range, inclusive.
 *
 * @reference   Bitwise and (or &) of a range
 *              https://www.geeksforgeeks.org/bitwise-and-or-of-a-range/
 */
constexpr auto BitwiseAndOfRange(unsigned left, unsigned right) {
    unsigned result = 0;

    while (left and right) {
        const auto msb_left = FindMSB(left);
        const auto msb_right = FindMSB(right);

        if (msb_left != msb_right) {
            break;
        }

        result += msb_left;

        left -= msb_left;
        right -= msb_right;
    }

    return result;
}


constexpr auto
BitwiseAndOfRange_BrianKernighan(const unsigned left, unsigned right) {
    while (left < right) {
        right = right & (right - 1);
    }

    return right & left;
}

}//namespace


THE_BENCHMARK(BitwiseAndOfRange, 12, 15);

SIMPLE_TEST(BitwiseAndOfRange, TestSample1, 12, 12, 15);
SIMPLE_TEST(BitwiseAndOfRange, TestSample2, 0, 10, 20);
SIMPLE_TEST(BitwiseAndOfRange, TestSample3, 16, 17, 19);
SIMPLE_TEST(BitwiseAndOfRange, TestSample4, 4, 5, 7);
SIMPLE_TEST(BitwiseAndOfRange, TestSample5, 0, 0, 0);
SIMPLE_TEST(BitwiseAndOfRange, TestSample6, 0, 1, 2147483647);


THE_BENCHMARK(BitwiseAndOfRange_BrianKernighan, 12, 15);

SIMPLE_TEST(BitwiseAndOfRange_BrianKernighan, TestSample1, 12, 12, 15);
SIMPLE_TEST(BitwiseAndOfRange_BrianKernighan, TestSample2, 0, 10, 20);
SIMPLE_TEST(BitwiseAndOfRange_BrianKernighan, TestSample3, 16, 17, 19);
SIMPLE_TEST(BitwiseAndOfRange_BrianKernighan, TestSample4, 4, 5, 7);
SIMPLE_TEST(BitwiseAndOfRange_BrianKernighan, TestSample5, 0, 0, 0);
SIMPLE_TEST(BitwiseAndOfRange_BrianKernighan, TestSample6, 0, 1, 2147483647);
