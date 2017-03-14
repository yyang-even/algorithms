#include "common_header.h"

typedef unsigned InputType;

/** Reverse bits
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Reverse bits the obvious way
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
InputType ReverseBits(InputType num) {
    auto size = sizeof(num) * CHAR_BIT - 1;
    InputType ret = num;
    for (num >>= 1; num; num >>= 1) {
        ret <<= 1;
        ret |= (num & 1);
        --size;
    }
    return ret << size;
}


const InputType LOWER = 0;
const InputType UPPER = UINT_MAX;

SIMPLE_BENCHMARK(ReverseBits, UPPER);

SIMPLE_TEST(ReverseBits, ReverseBitsLOWER, LOWER, LOWER);
SIMPLE_TEST(ReverseBits, ReverseBitsUPPER, UPPER, UPPER);
SIMPLE_TEST(ReverseBits, ReverseBitsSAMPLE3, 0XB0000000, 0b1101);
SIMPLE_TEST(ReverseBits, ReverseBitsSAMPLE4, 0X80, 0X01000000);
