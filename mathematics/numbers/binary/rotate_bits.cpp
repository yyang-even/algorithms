#include "common_header.h"


namespace {

using InputType = unsigned;

/** Rotate bits of a number
 *
 * @reference   https://www.geeksforgeeks.org/rotate-bits-of-an-integer/
 *
 * Bit Rotation: A rotation (or circular shift) is an operation similar to shift
 * except that the bits that fall off at one end are put back to the other end.
 * In left rotation, the bits that fall off at left end are put back at right end.
 * In right rotation, the bits that fall off at right end are put back at left end.
 */
auto LeftRotate(const InputType num, const InputType r) {
    return (num << r) | (num >> (Bits_Number<decltype(num)>() - r));
}


auto RightRotate(const InputType num, const InputType r) {
    return (num >> r) | (num << (Bits_Number<decltype(num)>() - r));
}

}//namespace


SIMPLE_BENCHMARK(LeftRotate, 0b1101, 4);

SIMPLE_TEST(LeftRotate, TestSample1, 0b1000u, 1, 3);
SIMPLE_TEST(LeftRotate, TestSample2, 64u, 16, 2);


SIMPLE_BENCHMARK(RightRotate, 0b1101, 4);

SIMPLE_TEST(RightRotate, TestSample1, 1u, 0b1000, 3);
SIMPLE_TEST(RightRotate, TestSample2, 4u, 16, 2);
