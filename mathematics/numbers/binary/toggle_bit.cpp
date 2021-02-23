#include "common_header.h"


namespace {

/** Toggling a bit at nth position
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 * @reference   Toggling k-th bit of a number
 *              https://www.geeksforgeeks.org/toggling-k-th-bit-number/
 * @reference   Bitwise Operators in C/C++
 *              https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/
 * @reference   Program to toggle K-th bit of a number N
 *              https://www.geeksforgeeks.org/program-to-toggle-k-th-bit-of-a-number-n/
 */
auto ToggleBit(const unsigned num, const unsigned position) {
    return num ^ (1 << position);
}


/** Toggle all the bits of a number except k-th bit.
 *
 * @reference   https://www.geeksforgeeks.org/toggle-bits-number-except-k-th-bit/
 */
auto ToggleAllBitsExceptKth(const unsigned num, const unsigned position) {
    return ~(num ^ (1 << position));
}


/** Toggle the last m bits
 *
 * @reference   https://www.geeksforgeeks.org/toggle-last-m-bits/
 */
auto ToggleLastBits(const unsigned num, const unsigned m) {
    const auto mask = (1 << m) - 1;
    return num ^ mask;
}

}//namespace


SIMPLE_BENCHMARK(ToggleBit, Sample1, 0, 4);

SIMPLE_TEST(ToggleBit, TestSample1, 0b110u, 0b100, 1);
SIMPLE_TEST(ToggleBit, TestSample2, 1u, 0, 0);
SIMPLE_TEST(ToggleBit, TestSample3, 0b10u, 0, 1);


SIMPLE_BENCHMARK(ToggleAllBitsExceptKth, Sample1, 0, 4);

SIMPLE_TEST(ToggleAllBitsExceptKth, TestSample1, 1u,
            std::numeric_limits<unsigned>::max(), 0);


SIMPLE_BENCHMARK(ToggleLastBits, Sample1, 21, 2);

SIMPLE_TEST(ToggleLastBits, TestSample1, 22u, 21, 2);
SIMPLE_TEST(ToggleLastBits, TestSample2, 100u, 107, 4);
