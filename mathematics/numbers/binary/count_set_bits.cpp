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


const InputType LOWER = 0;
constexpr InputType UPPER = UINT_MAX;

SIMPLE_BENCHMARK(CountSetBitsBrianKernighan, LOWER);
SIMPLE_BENCHMARK(CountSetBitsBrianKernighan, UPPER);
RANDOM_BENCHMARK(CountSetBitsBrianKernighan, LOWER, UPPER);

SIMPLE_TEST(CountSetBitsBrianKernighan, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountSetBitsBrianKernighan, TestUPPER, sizeof(UPPER) * CHAR_BIT, UPPER);
SIMPLE_TEST(CountSetBitsBrianKernighan, TestSAMPLE1, 2, 6);
SIMPLE_TEST(CountSetBitsBrianKernighan, TestSAMPLE2, 3, 13);
