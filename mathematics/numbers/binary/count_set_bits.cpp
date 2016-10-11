#include "common_header.h"

#include "binary.h"

typedef unsigned InputType;

/**Count set bits in an integer
 *
 * @reference   http://www.geeksforgeeks.org/count-set-bits-in-an-integer/
 *
 * Write an efficient program to count number of 1s in binary representation of an integer.
 */

/**
 * Brian Kernighan’s Algorithm
 */
InputType CountSetBitsBrianKernighan(InputType n) {
    InputType count = 0;
    while (n) {
        ++count;
        n &= (n - 1);
    }
    return count;
}

/**
 * @reference   Counting bits set by lookup table
 *              http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetTable
 */
static const unsigned char BitsSetTable256[256] = {
#define B2(n) n,     n+1,     n+1,     n+2
#define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
    B6(0), B6(1), B6(1), B6(2)
};
InputType CountSetBitsLookupTable(const InputType n) {
    auto *p = reinterpret_cast<const unsigned char *>(&n);
    auto num_bytes = sizeof(InputType);
    unsigned char count = 0;
    for (size_t i = 0; i < num_bytes; ++i) {
        count += BitsSetTable256[p[i]];
    }
    return count;
}


const InputType LOWER = 0;
constexpr InputType UPPER = UINT_MAX;

SIMPLE_BENCHMARK(CountSetBitsBrianKernighan, LOWER);
SIMPLE_BENCHMARK(CountSetBitsBrianKernighan, UPPER);
RANDOM_BENCHMARK(CountSetBitsBrianKernighan, LOWER, UPPER);

SIMPLE_TEST(CountSetBitsBrianKernighan, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountSetBitsBrianKernighan, TestUPPER, sizeof(UPPER) * CHAR_BIT, UPPER);
SIMPLE_TEST(CountSetBitsBrianKernighan, TestSAMPLE1, 2, 6);
SIMPLE_TEST(CountSetBitsBrianKernighan, TestSAMPLE2, 3, 13);

SIMPLE_BENCHMARK(CountSetBitsLookupTable, LOWER);
SIMPLE_BENCHMARK(CountSetBitsLookupTable, UPPER);
RANDOM_BENCHMARK(CountSetBitsLookupTable, LOWER, UPPER);

SIMPLE_TEST(CountSetBitsLookupTable, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountSetBitsLookupTable, TestUPPER, sizeof(UPPER) * CHAR_BIT, UPPER);
SIMPLE_TEST(CountSetBitsLookupTable, TestSAMPLE1, 2, 6);
SIMPLE_TEST(CountSetBitsLookupTable, TestSAMPLE2, 3, 13);

MUTUAL_RANDOM_TEST(CountSetBitsBrianKernighan, CountSetBitsLookupTable, LOWER, UPPER);
