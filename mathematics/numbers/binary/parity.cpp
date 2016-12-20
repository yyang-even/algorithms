#include "common_header.h"

#include "binary.h"

typedef unsigned InputType;

/** Computing parity the naive way
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Computing parity the naive way
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * 1 if an odd number of bits set, 0 otherwise.
 */
INT_BOOL ParityBrianKernighan(InputType n) {
    bool parity = false;  // parity will be the parity of n

    while (n) {
        parity = !parity;
        n = n & (n - 1);
    }

    return parity;
}


const InputType LOWER = 0;
const InputType UPPER = UINT_MAX;

SIMPLE_BENCHMARK(ParityBrianKernighan, LOWER);
SIMPLE_BENCHMARK(ParityBrianKernighan, UPPER);

SIMPLE_TEST(ParityBrianKernighan, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(ParityBrianKernighan, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(ParityBrianKernighan, TestSAMPLE1, FALSE, 6);
SIMPLE_TEST(ParityBrianKernighan, TestSAMPLE2, TRUE, 13);
