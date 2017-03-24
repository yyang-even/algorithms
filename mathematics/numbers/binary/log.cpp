#include "common_header.h"

typedef unsigned InputType;

/** Find the log base 2 of an integer with the MSB N set in O(N) operations (the obvious way)
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find the log base 2 of an integer with the MSB N set in O(N) operations (the obvious way)
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * The log base 2 of an integer is the same as the position of the highest bit set (or most significant bit set, MSB).
 */
InputType LogBase2(InputType num) {
    unsigned result = 0;
    while (num >>= 1) {
        ++result;
    }

    return result;
}


/** Find the integer log base 2 of an integer with an 64-bit IEEE float
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find the integer log base 2 of an integer with an 64-bit IEEE float
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
InputType LogBase2Float(const InputType num) {
    union {
        unsigned int uNum[2];
        double dNum;
    } temp;

    temp.uNum[__FLOAT_WORD_ORDER == LITTLE_ENDIAN] = 0x43300000;
    temp.uNum[__FLOAT_WORD_ORDER != LITTLE_ENDIAN] = num;
    temp.dNum -= 4503599627370496.0;
    return (temp.uNum[__FLOAT_WORD_ORDER == LITTLE_ENDIAN] >> 20) - 0x3FF;
}


/** Find the log base 2 of an integer with a lookup table
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find the log base 2 of an integer with a lookup table
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
InputType LogBase2LookupTable(const InputType num) {
    static_assert(sizeof(InputType) * CHAR_BIT == 32, "InputType is not 32 bits.");

    static const char LogTable256[256] = {
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
        -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
        LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
        LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
    };

    register InputType t, tt; // temporaries

    if (tt = num >> 16) {
        return (t = tt >> 8) ? 24 + LogTable256[t] : 16 + LogTable256[tt];
    } else {
        return (t = num >> 8) ? 8 + LogTable256[t] : LogTable256[num];
    }
}


const InputType LOWER = 1;
const InputType UPPER = UINT_MAX;

SIMPLE_BENCHMARK(LogBase2, UPPER);

SIMPLE_TEST(LogBase2, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2, TestSAMPLE2, 4, 17);

SIMPLE_BENCHMARK(LogBase2Float, UPPER);

SIMPLE_TEST(LogBase2Float, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2Float, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2Float, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2Float, TestSAMPLE2, 4, 17);

MUTUAL_RANDOM_TEST(LogBase2, LogBase2Float, LOWER, UPPER);

SIMPLE_BENCHMARK(LogBase2LookupTable, UPPER);

SIMPLE_TEST(LogBase2LookupTable, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2LookupTable, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2LookupTable, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2LookupTable, TestSAMPLE2, 4, 17);

MUTUAL_RANDOM_TEST(LogBase2LookupTable, LogBase2Float, LOWER, UPPER);
