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

/** Compute parity by lookup table
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute parity by lookup table
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
INT_BOOL ParityLookupTable(const InputType n) {
    static const bool ParityTable256[256] = {
#   define P2(n) n, n^1, n^1, n
#   define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
#   define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
        P6(0), P6(1), P6(1), P6(0)
    };

    const unsigned char *byte = reinterpret_cast<const unsigned char *>(&n);
    unsigned char parity = 0;
    for (size_t i = 0; i < sizeof(n); ++i) {
        parity ^= byte[i];
    }
    return ParityTable256[parity];
}


const InputType LOWER = 0;
const InputType UPPER = UINT_MAX;

SIMPLE_BENCHMARK(ParityBrianKernighan, LOWER);
SIMPLE_BENCHMARK(ParityBrianKernighan, UPPER);

SIMPLE_TEST(ParityBrianKernighan, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(ParityBrianKernighan, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(ParityBrianKernighan, TestSAMPLE1, FALSE, 6);
SIMPLE_TEST(ParityBrianKernighan, TestSAMPLE2, TRUE, 13);

SIMPLE_BENCHMARK(ParityLookupTable, LOWER);
SIMPLE_BENCHMARK(ParityLookupTable, UPPER);

SIMPLE_TEST(ParityLookupTable, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(ParityLookupTable, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(ParityLookupTable, TestSAMPLE1, FALSE, 6);
SIMPLE_TEST(ParityLookupTable, TestSAMPLE2, TRUE, 13);

MUTUAL_RANDOM_TEST(ParityBrianKernighan, ParityLookupTable, LOWER, UPPER);
