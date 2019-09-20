#include "common_header.h"


namespace {

using InputType = unsigned;

/** Count total bits in a number
 *
 * @reference   https://www.geeksforgeeks.org/count-total-bits-number/
 *
 * Given a positive number n, count total bit in it.
 */
auto CountTotalBits_Log(const InputType num) {
    assert(num);
    return static_cast<InputType>(log2(num)) + 1;
}


auto CountTotalBits_Loop(InputType num) {
    InputType count = 0;
    for (; num; num >>= 1) {
        ++count;
    }
    return count;
}


/** Number of leading zeros in binary representation of a given number
 *
 * @reference   https://www.geeksforgeeks.org/number-of-leading-zeros-in-binary-representation-of-a-given-number/
 */
auto CountLeadingZeros_Loop(const InputType num) {
    return BitsNumber<decltype(num)> - CountTotalBits_Loop(num);
}


auto CountLeadingZeros_BinarySearch(uint32_t num) {
    InputType result = 32;
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


}//namespace


constexpr auto LOWER = std::numeric_limits<uint32_t>::min();
constexpr auto UPPER = std::numeric_limits<uint32_t>::max();


SIMPLE_BENCHMARK(CountTotalBits_Log, UPPER);
RANDOM_BENCHMARK(CountTotalBits_Log, LOWER, UPPER);

SIMPLE_TEST(CountTotalBits_Log, TestUPPER, BitsNumber<decltype(UPPER)>, UPPER);
SIMPLE_TEST(CountTotalBits_Log, TestSAMPLE1, 4u, 13);
SIMPLE_TEST(CountTotalBits_Log, TestSAMPLE2, 8u, 183);
SIMPLE_TEST(CountTotalBits_Log, TestSAMPLE3, 13u, 4096);
SIMPLE_TEST(CountTotalBits_Log, TestSAMPLE4, 7u, 65);


SIMPLE_BENCHMARK(CountTotalBits_Loop, LOWER);
SIMPLE_BENCHMARK(CountTotalBits_Loop, UPPER);
RANDOM_BENCHMARK(CountTotalBits_Loop, LOWER, UPPER);

SIMPLE_TEST(CountTotalBits_Loop, TestLOWER, 0u, LOWER);
SIMPLE_TEST(CountTotalBits_Loop, TestUPPER, BitsNumber<decltype(UPPER)>, UPPER);
SIMPLE_TEST(CountTotalBits_Loop, TestSAMPLE1, 4u, 13);
SIMPLE_TEST(CountTotalBits_Loop, TestSAMPLE2, 8u, 183);
SIMPLE_TEST(CountTotalBits_Loop, TestSAMPLE3, 13u, 4096);
SIMPLE_TEST(CountTotalBits_Loop, TestSAMPLE4, 7u, 65);

MUTUAL_RANDOM_TEST(CountTotalBits_Log, CountTotalBits_Loop, LOWER, UPPER);


SIMPLE_BENCHMARK(CountLeadingZeros_Loop, 16);
RANDOM_BENCHMARK(CountLeadingZeros_Loop, LOWER, UPPER);

SIMPLE_TEST(CountLeadingZeros_Loop, TestLower, BitsNumber<decltype(LOWER)>, LOWER);
SIMPLE_TEST(CountLeadingZeros_Loop, TestSAMPLE1, 27u, 16);
SIMPLE_TEST(CountLeadingZeros_Loop, TestSAMPLE2, 26u, 33);
SIMPLE_TEST(CountLeadingZeros_Loop, TestUpper, 0u, UPPER);


SIMPLE_BENCHMARK(CountLeadingZeros_BinarySearch, 16);
RANDOM_BENCHMARK(CountLeadingZeros_BinarySearch, LOWER, UPPER);

SIMPLE_TEST(CountLeadingZeros_BinarySearch, TestLower, BitsNumber<decltype(LOWER)>, LOWER);
SIMPLE_TEST(CountLeadingZeros_BinarySearch, TestSAMPLE1, 27u, 16);
SIMPLE_TEST(CountLeadingZeros_BinarySearch, TestSAMPLE2, 26u, 33);
SIMPLE_TEST(CountLeadingZeros_BinarySearch, TestUpper, 0u, UPPER);

MUTUAL_RANDOM_TEST(CountLeadingZeros_Loop, CountLeadingZeros_BinarySearch, LOWER, UPPER);
