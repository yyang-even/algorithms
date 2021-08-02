#include "common_header.h"

#include "toggle_all_bits_after_most_significant_bit.h"


namespace {

/**
 * @reference   Number Complement
 *              https://leetcode.com/problems/number-complement/
 *
 * Given a positive integer num, output its complement number. The complement strategy
 * is to flip the bits of its binary representation.
 *
 * @reference   Complement of Base 10 Integer
 *              https://leetcode.com/problems/complement-of-base-10-integer/
 *
 * Every non-negative integer n has a binary representation.  For example, 5 can be
 * represented as "101" in binary, 11 as "1011" in binary, and so on.  Note that except
 * for n = 0, there are no leading zeroes in any binary representation. The complement
 * of a binary representation is the number in binary you get when changing every 1 to a
 * 0 and 0 to a 1.  For example, the complement of "101" in binary is "010" in binary.
 * For a given number n in base-10, return the complement of it's binary representation
 * as a base-10 integer.
 */
inline constexpr unsigned Complement(const uint32_t n) {
    if (n == 0) {
        return 1;
    }
    return ToggleAllBitsAfterMSB(n);
}

}//namespace


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
