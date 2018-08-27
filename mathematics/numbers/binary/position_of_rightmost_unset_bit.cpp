#include "common_header.h"

#include "are_all_bits_set.h"
#include "find_first_bit_set.h"

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

    return FindFirstBitSet(~num);
}


constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(PositionOfRightmostUnsetBit, 4);

SIMPLE_TEST(PositionOfRightmostUnsetBit, TestLOWER, 1, 0);
SIMPLE_TEST(PositionOfRightmostUnsetBit, TestSample1, 1, 0b110);
SIMPLE_TEST(PositionOfRightmostUnsetBit, TestSample2, 2, 9);
SIMPLE_TEST(PositionOfRightmostUnsetBit, TestSample3, -1, 1);
SIMPLE_TEST(PositionOfRightmostUnsetBit, TestUpper, -1, UPPER);
