#include "common_header.h"


namespace {

/** Rotate bits of a number
 *
 * @reference   https://www.geeksforgeeks.org/rotate-bits-of-an-integer/
 *
 * Bit Rotation: A rotation (or circular shift) is an operation similar to shift except
 * that the bits that fall off at one end are put back to the other end.
 * In left rotation, the bits that fall off at left end are put back at right end.
 * In right rotation, the bits that fall off at right end are put back at left end.
 */
inline constexpr auto LeftRotate(const unsigned num, const unsigned r) {
    return (num << r) | (num >> (BitsNumber<decltype(num)> - r));
}


inline constexpr auto RightRotate(const unsigned num, const unsigned r) {
    return (num >> r) | (num << (BitsNumber<decltype(num)> - r));
}

}//namespace


THE_BENCHMARK(LeftRotate, 0b1101, 4);

SIMPLE_TEST(LeftRotate, TestSample1, 0b1000, 1, 3);
SIMPLE_TEST(LeftRotate, TestSample2, 64, 16, 2);


THE_BENCHMARK(RightRotate, 0b1101, 4);

SIMPLE_TEST(RightRotate, TestSample1, 1, 0b1000, 3);
SIMPLE_TEST(RightRotate, TestSample2, 4, 16, 2);
