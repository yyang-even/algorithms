#include "common_header.h"

#include "count_set_bits.h"


namespace {

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
 * Write an efficient program to count number of 1s in binary representation of an
 * integer.
 *
 * @reference   Number of 1 Bits
 *              https://leetcode.com/problems/number-of-1-bits/
 *
 * Write a function that takes an unsigned integer and returns the number of '1' bits it
 * has (also known as the Hamming weight).
 */
/** Check if a number has same number of set and unset bits
 *
 * @reference   https://www.geeksforgeeks.org/check-if-a-number-has-same-number-of-set-and-unset-bits/
 *
 * Given a number N, the task is to check whether the count of the set and unset bits in
 * the given number are same.
 */


/** Counting bits set by lookup table
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Counting bits set by lookup table
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Count set bits in an integer using Lookup Table
 *              https://www.geeksforgeeks.org/count-set-bits-integer-using-lookup-table/
 */
constexpr unsigned char BitsSetTable256[256] = {
#define B2(n) n,     n+1,     n+1,     n+2
#define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
    B6(0), B6(1), B6(1), B6(2)
};

constexpr unsigned CountSetBits_LookupTable(const unsigned n) {
    const auto *p = reinterpret_cast<const unsigned char *>(&n);
    constexpr auto num_bytes = sizeof(unsigned);
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
inline constexpr uint32_t CountSetBits_MagicBinaries32(uint32_t n) {
    n = n - ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    return (((n + (n >> 4)) & 0xF0F0F0F) * 0x1010101) >> 24;
}


template <typename T>
inline constexpr T CountSetBitsMagicBinaries(T n) {
    n = n - ((n >> 1) & (T)~(T)0 / 3);
    n = (n & (T)~(T)0 / 15 * 3) + ((n >> 2) & (T)~(T)0 / 15 * 3);
    n = (n + (n >> 4)) & (T)~(T)0 / 255 * 15;
    return (T)(n * ((T)~(T)0 / 255)) >> (BitsNumber<T> - CHAR_BIT);
}

inline constexpr unsigned CountSetBits_MagicBinariesUnsigned(const unsigned n) {
    return CountSetBitsMagicBinaries(n);
}


/** Count bits set (rank) from the most-significant bit upto a given position
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count bits set (rank) from the most-significant bit upto a given position
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
inline constexpr uint64_t CountSetBitsFromMSB(uint64_t n, const unsigned pos) {
    // Shift out bits after given position.
    n = n >> (BitsNumber<decltype(n)> - pos);
    // Count set bits in parallel.
    return CountSetBitsMagicBinaries<uint64_t>(n);
}


/** Select the bit position (from the most-significant bit) with the given count (rank)
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Select the bit position (from the most-significant bit) with the given count (rank)
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Selects the position of the rth 1 bit when counting from the left. In other words if
 * we start at the most significant bit and proceed to the right, counting the number of
 * bits set to 1 until we reach the desired rank, r, then the position where we stop is
 * returned. If the rank requested exceeds the count of bits set, then 64 is returned.
 */
constexpr unsigned SelectPositionWithCountFromMSB(const uint64_t n, unsigned rank) {
    unsigned int s{};       // Output: Resulting position of bit with rank r [1-64]
    unsigned int t{};       // Bit count temporary.

    // Do a normal parallel bit count for a 64-bit integer,
    // but store all intermediate steps.
    // a = (n & 0x5555...) + ((n >> 1) & 0x5555...);
    const uint64_t a =  n - ((n >> 1) & ~0ULL / 3);
    // b = (a & 0x3333...) + ((a >> 2) & 0x3333...);
    const uint64_t b = (a & ~0ULL / 5) + ((a >> 2) & ~0ULL / 5);
    // c = (b & 0x0f0f...) + ((b >> 4) & 0x0f0f...);
    const uint64_t c = (b + (b >> 4)) & ~0ULL / 0x11;
    // d = (c & 0x00ff...) + ((c >> 8) & 0x00ff...);
    const uint64_t d = (c + (c >> 8)) & ~0ULL / 0x101;
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
inline constexpr auto AreBitAnagram(const unsigned a, const unsigned b) {
    return CountSetBits_BrianKernighan(a) == CountSetBits_BrianKernighan(b);
}


/** Check if binary representation of a given number and its complement are anagram
 *
 * @reference   https://www.geeksforgeeks.org/check-binary-representation-given-number-complement-anagram/
 */
inline constexpr auto
AreNumberAndItsComplementAnagram(const unsigned long long number) {
    return CountSetBits_BrianKernighan(number) == BitsNumber<decltype(number)> / 2;
}


/**
 * @reference   Prime Number of Set Bits in Binary Representation
 *              https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/
 *
 * Given two integers left and right, return the count of numbers in the inclusive range
 * [left, right] having a prime number of set bits in their binary representation. Recall
 * that the number of set bits an integer has is the number of 1's present when written
 * in binary.
 */
auto CountPrimeSetBits(const unsigned left, const unsigned right) {
    static const std::unordered_set<unsigned> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

    int result = 0;
    for (unsigned i = left; i <= right; ++i) {
        const auto count = CountSetBits_BrianKernighan(i);
        if (primes.find(count) != primes.cend()) {
            ++result;
        }
    }

    return result;
}


/** Count number of bits to be flipped to convert A to B
 *
 * @reference   https://www.geeksforgeeks.org/count-number-of-bits-to-be-flipped-to-convert-a-to-b/
 * @reference   Number of mismatching bits in the binary representation of two integers
 *              https://www.geeksforgeeks.org/number-of-mismatching-bits-in-the-binary-representation-of-two-integers/
 * @reference   Count number of bits to be flipped to convert A to B | Set-2
 *              https://www.geeksforgeeks.org/count-number-of-bits-to-be-flipped-to-convert-a-to-b-set-2/
 *
 * Given two numbers 'a' and 'b'. Write a program to count number of bits needed to be
 * flipped to convert 'a' to 'b'.
 *
 * @reference   Minimum Bit Flips to Convert Number
 *              https://leetcode.com/problems/minimum-bit-flips-to-convert-number/
 *
 * A bit flip of a number x is choosing a bit in the binary representation of x and
 * flipping it from either 0 to 1 or 1 to 0.
 *  For example, for x = 7, the binary representation is 111 and we may choose any bit
 *      (including any leading zeros not shown) and flip it. We can flip the first bit
 *      from the right to get 110, flip the second bit from the right to get 101, flip
 *      the fifth bit from the right (a leading zero) to get 10111, etc.
 * Given two integers start and goal, return the minimum number of bit flips to convert
 * start to goal.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 5.5.
 *
 * @reference   Hamming Distance
 *              https://leetcode.com/problems/hamming-distance/
 *
 * The Hamming distance between two integers is the number of positions at which the
 * corresponding bits are different. Given two integers x and y, return the Hamming
 * distance between them.
 */
inline constexpr auto CountDiffBits(const unsigned a, const unsigned b) {
    return CountSetBits_BrianKernighan(a ^ b);
}

}//namespace


constexpr auto LOWER = std::numeric_limits<uint32_t>::min();
constexpr auto UPPER = std::numeric_limits<uint32_t>::max();


SIMPLE_BENCHMARK(CountSetBits_BrianKernighan, Sample1, LOWER);
SIMPLE_BENCHMARK(CountSetBits_BrianKernighan, Sample2, UPPER);

SIMPLE_TEST(CountSetBits_BrianKernighan, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountSetBits_BrianKernighan, TestUPPER, BitsNumber<decltype(UPPER)>, UPPER);
SIMPLE_TEST(CountSetBits_BrianKernighan, TestSAMPLE1, 2, 6);
SIMPLE_TEST(CountSetBits_BrianKernighan, TestSAMPLE2, 3, 13);

#ifdef __GNUG__
MUTUAL_RANDOM_TEST(CountSetBits_BrianKernighan, __builtin_popcount, LOWER, UPPER);
#endif


SIMPLE_BENCHMARK(CountSetBits_LookupTable, Sample1, LOWER);
SIMPLE_BENCHMARK(CountSetBits_LookupTable, Sample2, UPPER);

SIMPLE_TEST(CountSetBits_LookupTable, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountSetBits_LookupTable, TestUPPER, BitsNumber<decltype(UPPER)>, UPPER);
SIMPLE_TEST(CountSetBits_LookupTable, TestSAMPLE1, 2, 6);
SIMPLE_TEST(CountSetBits_LookupTable, TestSAMPLE2, 3, 13);

MUTUAL_RANDOM_TEST(CountSetBits_BrianKernighan, CountSetBits_LookupTable, LOWER, UPPER);


SIMPLE_BENCHMARK(CountSetBits_MagicBinaries32, Sample1, LOWER);
SIMPLE_BENCHMARK(CountSetBits_MagicBinaries32, Sample2, UPPER);

SIMPLE_TEST(CountSetBits_MagicBinaries32, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountSetBits_MagicBinaries32, TestUPPER, BitsNumber<decltype(UPPER)>,
            UPPER);
SIMPLE_TEST(CountSetBits_MagicBinaries32, TestSAMPLE1, 2, 6);
SIMPLE_TEST(CountSetBits_MagicBinaries32, TestSAMPLE2, 3, 13);

MUTUAL_RANDOM_TEST(CountSetBits_BrianKernighan, CountSetBits_MagicBinaries32,
                   LOWER, UPPER);


SIMPLE_BENCHMARK(CountSetBits_MagicBinariesUnsigned, Sample1, LOWER);
SIMPLE_BENCHMARK(CountSetBits_MagicBinariesUnsigned, Sample2, UPPER);

SIMPLE_TEST(CountSetBits_MagicBinariesUnsigned, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountSetBits_MagicBinariesUnsigned, TestUPPER, BitsNumber<decltype(UPPER)>,
            UPPER);
SIMPLE_TEST(CountSetBits_MagicBinariesUnsigned, TestSAMPLE1, 2, 6);
SIMPLE_TEST(CountSetBits_MagicBinariesUnsigned, TestSAMPLE2, 3, 13);

MUTUAL_RANDOM_TEST(CountSetBits_BrianKernighan, CountSetBits_MagicBinariesUnsigned,
                   LOWER, UPPER);


SIMPLE_BENCHMARK(CountSetBitsFromMSB, Sample1, LOWER, CHAR_BIT);
SIMPLE_BENCHMARK(CountSetBitsFromMSB, Sample2, UPPER, CHAR_BIT);

SIMPLE_TEST(CountSetBitsFromMSB, TestLOWER, 0, LOWER, CHAR_BIT);
SIMPLE_TEST(CountSetBitsFromMSB, TestUPPER, CHAR_BIT, -1, CHAR_BIT);
SIMPLE_TEST(CountSetBitsFromMSB, TestSAMPLE1, 2, 0x06FFFFFFFFFFFFFF, CHAR_BIT);
SIMPLE_TEST(CountSetBitsFromMSB, TestSAMPLE2, 3, 0x13FFFFFFFFFFFFFF, CHAR_BIT);


SIMPLE_BENCHMARK(SelectPositionWithCountFromMSB, Sample1, LOWER, CHAR_BIT);
SIMPLE_BENCHMARK(SelectPositionWithCountFromMSB, Sample2, UPPER, CHAR_BIT);

SIMPLE_TEST(SelectPositionWithCountFromMSB, TestLOWER, 64, LOWER, CHAR_BIT);
SIMPLE_TEST(SelectPositionWithCountFromMSB, TestUPPER, CHAR_BIT, -1, CHAR_BIT);
SIMPLE_TEST(SelectPositionWithCountFromMSB, TestSAMPLE1, 14,
            0x06FFFFFFFFFFFFFF, CHAR_BIT);
SIMPLE_TEST(SelectPositionWithCountFromMSB, TestSAMPLE2, 13,
            0x13FFFFFFFFFFFFFF, CHAR_BIT);


THE_BENCHMARK(AreBitAnagram, 8, 4);

SIMPLE_TEST(AreBitAnagram, TestSAMPLE1, true, 8, 4);
SIMPLE_TEST(AreBitAnagram, TestSAMPLE2, false, 5, 4);


THE_BENCHMARK(AreNumberAndItsComplementAnagram, 4294967295);

SIMPLE_TEST(AreNumberAndItsComplementAnagram, TestSAMPLE1, true, 4294967295);
SIMPLE_TEST(AreNumberAndItsComplementAnagram, TestSAMPLE2, false, 4);


THE_BENCHMARK(CountPrimeSetBits, 6, 10);

SIMPLE_TEST(CountPrimeSetBits, TestSAMPLE1, 4, 6, 10);
SIMPLE_TEST(CountPrimeSetBits, TestSAMPLE2, 5, 10, 15);


THE_BENCHMARK(CountDiffBits, 10, 20);

SIMPLE_TEST(CountDiffBits, TestSample1, 4, 10, 20);
SIMPLE_TEST(CountDiffBits, TestSample2, 3, 10, 7);
SIMPLE_TEST(CountDiffBits, TestSample3, 2, 12, 15);
SIMPLE_TEST(CountDiffBits, TestSample4, 3, 3, 16);
