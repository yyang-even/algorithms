#include "common_header.h"

#include "toggle_all_bits_after_most_significant_bit.h"


namespace {

/**
 * @reference   Number Complement
 *              https://leetcode.com/problems/number-complement/
 * @reference   Complement of Base 10 Integer
 *              https://leetcode.com/problems/complement-of-base-10-integer/
 *
 * The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's
 * to 0's in its binary representation.
 *  For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
 * Given an integer n, return its complement.
 *
 * @tags    #bit-tricks
 */
inline constexpr unsigned Complement(const uint32_t n) {
    if (n == 0) {
        return 1;
    }
    return ToggleAllBitsAfterMSB(n);
}

} //namespace


THE_BENCHMARK(ToggleAllBitsAfterMSB, 0);

SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample1, 0, 0);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample2, 0, 1);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample3, 5, 10);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample4, 2, 5);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample5, 0, 7);


THE_BENCHMARK(Complement, 0);

SIMPLE_TEST(Complement, TestSample1, 1, 0);
SIMPLE_TEST(Complement, TestSample2, 0, 1);
SIMPLE_TEST(Complement, TestSample3, 5, 10);
SIMPLE_TEST(Complement, TestSample4, 2, 5);
SIMPLE_TEST(Complement, TestSample5, 0, 7);
