#include "common_header.h"

#include "count_set_bits.h"

namespace {

using InputType = unsigned;

/** Count set bits in an integer
 *
 * @reference   https://www.geeksforgeeks.org/count-set-bits-in-an-integer/
 * @reference   Count Set-bits of number using Recursion
 *              https://www.geeksforgeeks.org/count-set-bits-of-number-using-recursion/
 * @reference   C/C++ Program to Count set bits in an integer
 *              https://www.geeksforgeeks.org/c-program-for-count-set-bits-in-an-integer/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 13.
 *
 * Write an efficient program to count number of 1s in binary representation of an integer.
 */
/** Check if a number has same number of set and unset bits
 *
 * @reference   https://www.geeksforgeeks.org/check-if-a-number-has-same-number-of-set-and-unset-bits/
 *
 * Given a number N, the task is to check whether the count of the set and unset bits in the given number are same.
 */


/** Counting bits set by lookup table
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Counting bits set by lookup table
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Count set bits in an integer using Lookup Table
 *              https://www.geeksforgeeks.org/count-set-bits-integer-using-lookup-table/
 */
static const unsigned char BitsSetTable256[256] = {
#define B2(n) n,     n+1,     n+1,     n+2
#define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
    B6(0), B6(1), B6(1), B6(2)
};
InputType CountSetBits_LookupTable(const InputType n) {
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
uint32_t CountSetBits_MagicBinaries32(uint32_t n) {
    n = n - ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    return (((n + (n >> 4)) & 0xF0F0F0F) * 0x1010101) >> 24;
}


template <typename T>
T CountSetBitsMagicBinaries(T n) {
    n = n - ((n >> 1) & (T)~(T)0 / 3);
    n = (n & (T)~(T)0 / 15 * 3) + ((n >> 2) & (T)~(T)0 / 15 * 3);
    n = (n + (n >> 4)) & (T)~(T)0 / 255 * 15;
    return (T)(n * ((T)~(T)0 / 255)) >> (BitsNumber<T> - CHAR_BIT);
}
unsigned CountSetBits_MagicBinariesUnsigned(unsigned n) {
    return CountSetBitsMagicBinaries<unsigned>(n);
}


/** Count bits set (rank) from the most-significant bit upto a given position
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count bits set (rank) from the most-significant bit upto a given position
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
uint64_t CountSetBitsFromMSB(uint64_t n, const unsigned pos) {
    // Shift out bits after given position.
    n = n >> (BitsNumber<decltype(n)> - pos);
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


/** Check if binary representations of two numbers are anagram
 *
 * @reference   https://www.geeksforgeeks.org/check-binary-representations-two-numbers-anagram/
 */
auto AreBitAnagram(const unsigned a, const unsigned b) {
    return CountSetBits_BrianKernighan(a) == CountSetBits_BrianKernighan(b);
}


/** Check if binary representation of a given number and its complement are anagram
 *
 * @reference   https://www.geeksforgeeks.org/check-binary-representation-given-number-complement-anagram/
 */
auto AreNumberAndItsComplementAnagram(const unsigned long long number) {
    return CountSetBits_BrianKernighan(number) == BitsNumber<decltype(number)> / 2;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<uint32_t>::min();
constexpr auto UPPER = std::numeric_limits<uint32_t>::max();


SIMPLE_BENCHMARK(CountSetBits_BrianKernighan, Sample1, LOWER);
SIMPLE_BENCHMARK(CountSetBits_BrianKernighan, Sample2, UPPER);

SIMPLE_TEST(CountSetBits_BrianKernighan, TestLOWER, 0u, LOWER);
SIMPLE_TEST(CountSetBits_BrianKernighan, TestUPPER, BitsNumber<decltype(UPPER)>, UPPER);
SIMPLE_TEST(CountSetBits_BrianKernighan, TestSAMPLE1, 2u, 6);
SIMPLE_TEST(CountSetBits_BrianKernighan, TestSAMPLE2, 3u, 13);

#ifdef __GNUG__
MUTUAL_RANDOM_TEST(CountSetBits_BrianKernighan, __builtin_popcount, LOWER, UPPER);
#endif


SIMPLE_BENCHMARK(CountSetBits_LookupTable, Sample1, LOWER);
SIMPLE_BENCHMARK(CountSetBits_LookupTable, Sample2, UPPER);

SIMPLE_TEST(CountSetBits_LookupTable, TestLOWER, 0u, LOWER);
SIMPLE_TEST(CountSetBits_LookupTable, TestUPPER, BitsNumber<decltype(UPPER)>, UPPER);
SIMPLE_TEST(CountSetBits_LookupTable, TestSAMPLE1, 2u, 6);
SIMPLE_TEST(CountSetBits_LookupTable, TestSAMPLE2, 3u, 13);

MUTUAL_RANDOM_TEST(CountSetBits_BrianKernighan, CountSetBits_LookupTable, LOWER, UPPER);


SIMPLE_BENCHMARK(CountSetBits_MagicBinaries32, Sample1, LOWER);
SIMPLE_BENCHMARK(CountSetBits_MagicBinaries32, Sample2, UPPER);

SIMPLE_TEST(CountSetBits_MagicBinaries32, TestLOWER, 0u, LOWER);
SIMPLE_TEST(CountSetBits_MagicBinaries32, TestUPPER, BitsNumber<decltype(UPPER)>,
            UPPER);
SIMPLE_TEST(CountSetBits_MagicBinaries32, TestSAMPLE1, 2u, 6);
SIMPLE_TEST(CountSetBits_MagicBinaries32, TestSAMPLE2, 3u, 13);

MUTUAL_RANDOM_TEST(CountSetBits_BrianKernighan, CountSetBits_MagicBinaries32,
                   LOWER, UPPER);


SIMPLE_BENCHMARK(CountSetBits_MagicBinariesUnsigned, Sample1, LOWER);
SIMPLE_BENCHMARK(CountSetBits_MagicBinariesUnsigned, Sample2, UPPER);

SIMPLE_TEST(CountSetBits_MagicBinariesUnsigned, TestLOWER, 0u, LOWER);
SIMPLE_TEST(CountSetBits_MagicBinariesUnsigned, TestUPPER, BitsNumber<decltype(UPPER)>,
            UPPER);
SIMPLE_TEST(CountSetBits_MagicBinariesUnsigned, TestSAMPLE1, 2u, 6);
SIMPLE_TEST(CountSetBits_MagicBinariesUnsigned, TestSAMPLE2, 3u, 13);

MUTUAL_RANDOM_TEST(CountSetBits_BrianKernighan, CountSetBits_MagicBinariesUnsigned,
                   LOWER, UPPER);


SIMPLE_BENCHMARK(CountSetBitsFromMSB, Sample1, LOWER, CHAR_BIT);
SIMPLE_BENCHMARK(CountSetBitsFromMSB, Sample2, UPPER, CHAR_BIT);

SIMPLE_TEST(CountSetBitsFromMSB, TestLOWER, 0u, LOWER, CHAR_BIT);
SIMPLE_TEST(CountSetBitsFromMSB, TestUPPER, static_cast<unsigned>(CHAR_BIT),
            -1ULL, CHAR_BIT);
SIMPLE_TEST(CountSetBitsFromMSB, TestSAMPLE1, 2u, 0x06FFFFFFFFFFFFFFULL, CHAR_BIT);
SIMPLE_TEST(CountSetBitsFromMSB, TestSAMPLE2, 3u, 0x13FFFFFFFFFFFFFFULL, CHAR_BIT);


SIMPLE_BENCHMARK(SelectPositionWithCountFromMSB, Sample1, LOWER, CHAR_BIT);
SIMPLE_BENCHMARK(SelectPositionWithCountFromMSB, Sample2, UPPER, CHAR_BIT);

SIMPLE_TEST(SelectPositionWithCountFromMSB, TestLOWER, 64, LOWER, CHAR_BIT);
SIMPLE_TEST(SelectPositionWithCountFromMSB, TestUPPER,
            static_cast<unsigned>(CHAR_BIT), -1ULL, CHAR_BIT);
SIMPLE_TEST(SelectPositionWithCountFromMSB, TestSAMPLE1, 14,
            0x06FFFFFFFFFFFFFFULL, CHAR_BIT);
SIMPLE_TEST(SelectPositionWithCountFromMSB, TestSAMPLE2, 13,
            0x13FFFFFFFFFFFFFFULL, CHAR_BIT);


SIMPLE_BENCHMARK(AreBitAnagram, Sample1, 8, 4);

SIMPLE_TEST(AreBitAnagram, TestSAMPLE1, true, 8, 4);
SIMPLE_TEST(AreBitAnagram, TestSAMPLE2, false, 5, 4);


SIMPLE_BENCHMARK(AreNumberAndItsComplementAnagram, Sample1, 4294967295);

SIMPLE_TEST(AreNumberAndItsComplementAnagram, TestSAMPLE1, true, 4294967295);
SIMPLE_TEST(AreNumberAndItsComplementAnagram, TestSAMPLE2, false, 4);
