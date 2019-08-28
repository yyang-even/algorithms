#include "common_header.h"

#include "are_all_bits_set.h"


namespace {

using InputType = unsigned;

/** Get the position of rightmost unset bit
 *
 * @reference   https://www.geeksforgeeks.org/get-position-rightmost-unset-bit/
 *
 * Given a non-negative number n. Find the position of rightmost unset bit in the binary
 * representation of n, considering the last bit at position 1, 2nd last bit at position
 * 2 and so on. If no 0’s are there in the binary representation of n. then print “-1”.
 */
int PositionOfRightmostUnsetBit(const InputType num) {
    if (not num) {
        return 1;
    }
    if (AreAllBitsSet(num)) {
        return -1;
    }

    return ffs(~num);
}


/** Position of rightmost common bit in two numbers
 *
 * @reference   https://www.geeksforgeeks.org/position-rightmost-common-bit-two-numbers/
 */
auto PositionOfRightmostCommonBit(const InputType lhs, const InputType rhs) {
    return PositionOfRightmostUnsetBit(lhs ^ rhs);
}

}//namespace


constexpr auto UPPER = std::numeric_limits<InputType>::max();


SIMPLE_BENCHMARK(PositionOfRightmostUnsetBit, 4);

SIMPLE_TEST(PositionOfRightmostUnsetBit, TestLOWER, 1, 0);
SIMPLE_TEST(PositionOfRightmostUnsetBit, TestSample1, 1, 0b110);
SIMPLE_TEST(PositionOfRightmostUnsetBit, TestSample2, 2, 9);
SIMPLE_TEST(PositionOfRightmostUnsetBit, TestSample3, -1, 1);
SIMPLE_TEST(PositionOfRightmostUnsetBit, TestUpper, -1, UPPER);


SIMPLE_BENCHMARK(PositionOfRightmostCommonBit, 10, 9);

SIMPLE_TEST(PositionOfRightmostCommonBit, TestSample1, 3, 10, 9);
SIMPLE_TEST(PositionOfRightmostCommonBit, TestSample2, 4, 16, 7);
