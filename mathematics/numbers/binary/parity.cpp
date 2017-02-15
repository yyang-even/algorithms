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

/** Compute parity of a byte using 64-bit multiply and modulus division
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute parity of a byte using 64-bit multiply and modulus division
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
INT_BOOL ParityOfByte64bit(const unsigned char n) {
    return (((n * 0x0101010101010101ULL) & 0x8040201008040201ULL) % 0x1FF) & 1;
}

/** Compute parity of word with a multiply
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute parity of word with a multiply
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
INT_BOOL ParityMultiply32(uint32_t n) {
    n ^= n >> 1;
    n ^= n >> 2;
    n = (n & 0x11111111U) * 0x11111111U;
    return (n >> 28) & 1;
}
INT_BOOL ParityMultiply64(uint64_t n) {
    n ^= n >> 1;
    n ^= n >> 2;
    n = (n & 0x1111111111111111UL) * 0x1111111111111111UL;
    return (n >> 60) & 1;
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

SIMPLE_BENCHMARK(ParityOfByte64bit, LOWER);
SIMPLE_BENCHMARK(ParityOfByte64bit, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(ParityOfByte64bit, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(ParityOfByte64bit, TestUPPER, FALSE, static_cast<unsigned char>(UPPER));
SIMPLE_TEST(ParityOfByte64bit, TestSAMPLE1, FALSE, 6);
SIMPLE_TEST(ParityOfByte64bit, TestSAMPLE2, TRUE, 13);

SIMPLE_BENCHMARK(ParityMultiply32, LOWER);
SIMPLE_BENCHMARK(ParityMultiply32, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(ParityMultiply32, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(ParityMultiply32, TestUPPER, FALSE, static_cast<unsigned char>(UPPER));
SIMPLE_TEST(ParityMultiply32, TestSAMPLE1, FALSE, 6);
SIMPLE_TEST(ParityMultiply32, TestSAMPLE2, TRUE, 13);

SIMPLE_BENCHMARK(ParityMultiply64, LOWER);
SIMPLE_BENCHMARK(ParityMultiply64, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(ParityMultiply64, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(ParityMultiply64, TestUPPER, FALSE, static_cast<unsigned char>(UPPER));
SIMPLE_TEST(ParityMultiply64, TestSAMPLE1, FALSE, 6);
SIMPLE_TEST(ParityMultiply64, TestSAMPLE2, TRUE, 13);

MUTUAL_RANDOM_TEST(ParityBrianKernighan, ParityMultiply32, LOWER, UPPER);
MUTUAL_RANDOM_TEST(ParityMultiply32, ParityMultiply64, LOWER, UPPER);
