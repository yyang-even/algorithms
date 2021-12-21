#include "common_header.h"

#include "count_total_bits.h"


namespace {

/** Number of leading zeros in binary representation of a given number
 *
 * @reference   https://www.geeksforgeeks.org/number-of-leading-zeros-in-binary-representation-of-a-given-number/
 */
inline constexpr auto CountLeadingZeros_Loop(const unsigned num) {
    return BitsNumber<decltype(num)> - CountTotalBits_Loop(num);
}


constexpr auto CountLeadingZeros_BinarySearch(uint32_t num) {
    unsigned result = 32;
    if (num & 0xffff0000) {
        result -= 16;
        num >>= 16;
    }
    if (num & 0xff00) {
        result -= 8;
        num >>= 8;
    }
    if (num & 0xf0) {
        result -= 4;
        num >>= 4;
    }
    if (num & 0b1100) {
        result -= 2;
        num >>= 2;
    }
    if (num & 0b10) {
        result -= 1;
        num >>= 1;
    }

    return result - num;
}


/**
 * @reference   Number of Steps to Reduce a Number to Zero
 *              https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/
 *
 * Given an integer num, return the number of steps to reduce it to zero. In one step,
 * if the current number is even, you have to divide it by 2, otherwise, you have to
 * subtract 1 from it.
 */

}//namespace


constexpr auto LOWER = std::numeric_limits<uint32_t>::min();
constexpr auto UPPER = std::numeric_limits<uint32_t>::max();


THE_BENCHMARK(CountTotalBits_Log, UPPER);

SIMPLE_TEST(CountTotalBits_Log, TestUPPER, BitsNumber<decltype(UPPER)>, UPPER);
SIMPLE_TEST(CountTotalBits_Log, TestSAMPLE1, 4, 13);
SIMPLE_TEST(CountTotalBits_Log, TestSAMPLE2, 8, 183);
SIMPLE_TEST(CountTotalBits_Log, TestSAMPLE3, 13, 4096);
SIMPLE_TEST(CountTotalBits_Log, TestSAMPLE4, 7, 65);


SIMPLE_BENCHMARK(CountTotalBits_Loop, Sample1, LOWER);
SIMPLE_BENCHMARK(CountTotalBits_Loop, Sample2, UPPER);

SIMPLE_TEST(CountTotalBits_Loop, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountTotalBits_Loop, TestUPPER, BitsNumber<decltype(UPPER)>, UPPER);
SIMPLE_TEST(CountTotalBits_Loop, TestSAMPLE1, 4, 13);
SIMPLE_TEST(CountTotalBits_Loop, TestSAMPLE2, 8, 183);
SIMPLE_TEST(CountTotalBits_Loop, TestSAMPLE3, 13, 4096);
SIMPLE_TEST(CountTotalBits_Loop, TestSAMPLE4, 7, 65);

MUTUAL_RANDOM_TEST(CountTotalBits_Log, CountTotalBits_Loop, LOWER, UPPER);


THE_BENCHMARK(CountLeadingZeros_Loop, 16);

SIMPLE_TEST(CountLeadingZeros_Loop, TestLower, BitsNumber<decltype(LOWER)>, LOWER);
SIMPLE_TEST(CountLeadingZeros_Loop, TestSAMPLE1, 27, 16);
SIMPLE_TEST(CountLeadingZeros_Loop, TestSAMPLE2, 26, 33);
SIMPLE_TEST(CountLeadingZeros_Loop, TestUpper, 0, UPPER);


THE_BENCHMARK(CountLeadingZeros_BinarySearch, 16);

SIMPLE_TEST(CountLeadingZeros_BinarySearch, TestLower, BitsNumber<decltype(LOWER)>,
            LOWER);
SIMPLE_TEST(CountLeadingZeros_BinarySearch, TestSAMPLE1, 27, 16);
SIMPLE_TEST(CountLeadingZeros_BinarySearch, TestSAMPLE2, 26, 33);
SIMPLE_TEST(CountLeadingZeros_BinarySearch, TestUpper, 0, UPPER);

MUTUAL_RANDOM_TEST(CountLeadingZeros_Loop, CountLeadingZeros_BinarySearch,
                   LOWER, UPPER);
