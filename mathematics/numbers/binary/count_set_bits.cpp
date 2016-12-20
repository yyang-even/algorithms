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

/** Counting bits set by lookup table
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Counting bits set by lookup table
 *              https://graphics.stanford.edu/~seander/bithacks.html
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

/** TODO: Counting bits set in 14, 24, or 32-bit words using 64-bit instructions
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Counting bits set in 14, 24, or 32-bit words using 64-bit instructions
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */

/** Counting bits set, in parallel
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Counting bits set, in parallel
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
uint32_t CountSetBitsMagicBinaries32(uint32_t n) {
    n = n - ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    return ((n + (n >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
}
template <typename T>
T CountSetBitsMagicBinaries(T n) {
    n = n - ((n >> 1) & (T)~(T)0 / 3);
    n = (n & (T)~(T)0 / 15 * 3) + ((n >> 2) & (T)~(T)0 / 15 * 3);
    n = (n + (n >> 4)) & (T)~(T)0 / 255 * 15;
    return (T)(n * ((T)~(T)0 / 255)) >> (sizeof(T) - 1) * CHAR_BIT;
}
unsigned CountSetBitsMagicBinariesUnsigned(unsigned n) {
    return CountSetBitsMagicBinaries<unsigned>(n);
}


/** Count bits set (rank) from the most-significant bit upto a given position
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count bits set (rank) from the most-significant bit upto a given position
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
uint64_t CountSetBitsFromMSB(uint64_t n, const unsigned pos) {
    const auto sizeof_n = sizeof(n);
    // Shift out bits after given position.
    n = n >> (sizeof_n * CHAR_BIT - pos);
    // Count set bits in parallel.
    return CountSetBitsMagicBinaries<uint64_t>(n);
}

/** Select the bit position (from the most-significant bit) with the given count (rank)
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Select the bit position (from the most-significant bit) with the given count (rank)
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Selects the position of the rth 1 bit when counting from the left. In other words if we start at the
 * most significant bit and proceed to the right, counting the number of bits set to 1 until we reach the
 * desired rank, r, then the position where we stop is returned. If the rank requested exceeds the count
 * of bits set, then 64 is returned.
 */
unsigned SelectPositionWithCountFromMSB(const uint64_t n, unsigned rank) {
    unsigned int s;       // Output: Resulting position of bit with rank r [1-64]
    uint64_t a, b, c, d;  // Intermediate temporaries for bit count.
    unsigned int t;       // Bit count temporary.

    // Do a normal parallel bit count for a 64-bit integer,
    // but store all intermediate steps.
    // a = (n & 0x5555...) + ((n >> 1) & 0x5555...);
    a =  n - ((n >> 1) & ~0UL / 3);
    // b = (a & 0x3333...) + ((a >> 2) & 0x3333...);
    b = (a & ~0UL / 5) + ((a >> 2) & ~0UL / 5);
    // c = (b & 0x0f0f...) + ((b >> 4) & 0x0f0f...);
    c = (b + (b >> 4)) & ~0UL / 0x11;
    // d = (c & 0x00ff...) + ((c >> 8) & 0x00ff...);
    d = (c + (c >> 8)) & ~0UL / 0x101;
    t = (d >> 32) + (d >> 48);
    // Now do branchless select!
    s  = 64;
    // if (rank > t) {s -= 32; rank -= t;}
    s -= ((t - rank) & 256) >> 3;
    rank -= (t & ((t - rank) >> 8));
    t  = (d >> (s - 16)) & 0xff;
    // if (rank > t) {s -= 16; rank -= t;}
    s -= ((t - rank) & 256) >> 4;
    rank -= (t & ((t - rank) >> 8));
    t  = (c >> (s - 8)) & 0xf;
    // if (rank > t) {s -= 8; rank -= t;}
    s -= ((t - rank) & 256) >> 5;
    rank -= (t & ((t - rank) >> 8));
    t  = (b >> (s - 4)) & 0x7;
    // if (rank > t) {s -= 4; rank -= t;}
    s -= ((t - rank) & 256) >> 6;
    rank -= (t & ((t - rank) >> 8));
    t  = (a >> (s - 2)) & 0x3;
    // if (rank > t) {s -= 2; rank -= t;}
    s -= ((t - rank) & 256) >> 7;
    rank -= (t & ((t - rank) >> 8));
    t  = (n >> (s - 1)) & 0x1;
    // if (rank > t) s--;
    s -= ((t - rank) & 256) >> 8;
    return 65 - s;
}

const InputType LOWER = 0;
const InputType UPPER = UINT_MAX;

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

SIMPLE_BENCHMARK(CountSetBitsMagicBinaries32, LOWER);
SIMPLE_BENCHMARK(CountSetBitsMagicBinaries32, UPPER);

SIMPLE_TEST(CountSetBitsMagicBinaries32, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountSetBitsMagicBinaries32, TestUPPER, sizeof(UPPER) * CHAR_BIT, UPPER);
SIMPLE_TEST(CountSetBitsMagicBinaries32, TestSAMPLE1, 2, 6);
SIMPLE_TEST(CountSetBitsMagicBinaries32, TestSAMPLE2, 3, 13);

MUTUAL_RANDOM_TEST(CountSetBitsBrianKernighan, CountSetBitsMagicBinaries32, LOWER, UPPER);

SIMPLE_BENCHMARK(CountSetBitsMagicBinariesUnsigned, LOWER);
SIMPLE_BENCHMARK(CountSetBitsMagicBinariesUnsigned, UPPER);

SIMPLE_TEST(CountSetBitsMagicBinariesUnsigned, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountSetBitsMagicBinariesUnsigned, TestUPPER, sizeof(UPPER) * CHAR_BIT, UPPER);
SIMPLE_TEST(CountSetBitsMagicBinariesUnsigned, TestSAMPLE1, 2, 6);
SIMPLE_TEST(CountSetBitsMagicBinariesUnsigned, TestSAMPLE2, 3, 13);

MUTUAL_RANDOM_TEST(CountSetBitsBrianKernighan, CountSetBitsMagicBinariesUnsigned, LOWER, UPPER);

SIMPLE_BENCHMARK(CountSetBitsFromMSB, LOWER, CHAR_BIT);
SIMPLE_BENCHMARK(CountSetBitsFromMSB, UPPER, CHAR_BIT);

SIMPLE_TEST(CountSetBitsFromMSB, TestLOWER, 0, LOWER, CHAR_BIT);
SIMPLE_TEST(CountSetBitsFromMSB, TestUPPER, CHAR_BIT, -1ULL, CHAR_BIT);
SIMPLE_TEST(CountSetBitsFromMSB, TestSAMPLE1, 2, 0x06FFFFFFFFFFFFFFULL, CHAR_BIT);
SIMPLE_TEST(CountSetBitsFromMSB, TestSAMPLE2, 3, 0x13FFFFFFFFFFFFFFULL, CHAR_BIT);

SIMPLE_BENCHMARK(SelectPositionWithCountFromMSB, LOWER, CHAR_BIT);
SIMPLE_BENCHMARK(SelectPositionWithCountFromMSB, UPPER, CHAR_BIT);

SIMPLE_TEST(SelectPositionWithCountFromMSB, TestLOWER, 64, LOWER, CHAR_BIT);
SIMPLE_TEST(SelectPositionWithCountFromMSB, TestUPPER, CHAR_BIT, -1ULL, CHAR_BIT);
SIMPLE_TEST(SelectPositionWithCountFromMSB, TestSAMPLE1, 14, 0x06FFFFFFFFFFFFFFULL, CHAR_BIT);
SIMPLE_TEST(SelectPositionWithCountFromMSB, TestSAMPLE2, 13, 0x13FFFFFFFFFFFFFFULL, CHAR_BIT);
