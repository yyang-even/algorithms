#include "common_header.h"

#include "count_set_bits.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Count set bits in an integer
 *              https://www.geeksforgeeks.org/count-set-bits-in-an-integer/
 * @reference   Count Set-bits of number using Recursion
 *              https://www.geeksforgeeks.org/count-set-bits-of-number-using-recursion/
 * @reference   C/C++ Program to Count set bits in an integer
 *              https://www.geeksforgeeks.org/c-program-for-count-set-bits-in-an-integer/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 13.
 *
 * Write an efficient program to count number of 1s in binary representation of an integer.
 *
 * @reference   Number of 1 Bits
 *              https://leetcode.com/problems/number-of-1-bits/
 *
 * Write a function that takes an unsigned integer and returns the number of '1' bits it has (also known
 * as the Hamming weight).
 *
 * @tags    #count-set-bits
 */


/**
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Counting bits set by lookup table
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Count set bits in an integer using Lookup Table
 *              https://www.geeksforgeeks.org/count-set-bits-integer-using-lookup-table/
 */
constexpr unsigned char BitsSetTable256[256] = {
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
    B6(0), B6(1), B6(1), B6(2)};

unsigned CountSetBits_LookupTable(const unsigned n) {
    const auto *p = reinterpret_cast<const unsigned char *>(&n);
    constexpr auto num_bytes = sizeof(unsigned);
    unsigned char count = 0;
    for (size_t i = 0; i < num_bytes; ++i) {
        count += BitsSetTable256[p[i]];
    }
    return count;
}


/** TODO
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Counting bits set in 14, 24, or 32-bit words using 64-bit instructions
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */


/**
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Counting bits set, in parallel
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
inline constexpr uint32_t CountSetBits_MagicBinaries32(uint32_t n) {
    n = n - ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    return (((n + (n >> 4)) & 0xF0F0F0F) * 0x1010101) >> 24;
}


template<typename T>
inline constexpr T CountSetBitsMagicBinaries(T n) {
    n = n - ((n >> 1) & (T) ~(T)0 / 3);
    n = (n & (T) ~(T)0 / 15 * 3) + ((n >> 2) & (T) ~(T)0 / 15 * 3);
    n = (n + (n >> 4)) & (T) ~(T)0 / 255 * 15;
    return (T)(n * ((T) ~(T)0 / 255)) >> (BitsNumber<T> - CHAR_BIT);
}

inline constexpr unsigned CountSetBits_MagicBinariesUnsigned(const unsigned n) {
    return CountSetBitsMagicBinaries(n);
}


/**
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


/**
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Select the bit position (from the most-significant bit) with the given count (rank)
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Selects the position of the rth 1 bit when counting from the left. In other words if we start at the
 * most significant bit and proceed to the right, counting the number of bits set to 1 until we reach
 * the desired rank, r, then the position where we stop is returned. If the rank requested exceeds the
 * count of bits set, then 64 is returned.
 */
constexpr unsigned SelectPositionWithCountFromMSB(const uint64_t n, unsigned rank) {
    unsigned int s {}; // Output: Resulting position of bit with rank r [1-64]
    unsigned int t {}; // Bit count temporary.

    // Do a normal parallel bit count for a 64-bit integer,
    // but store all intermediate steps.
    // a = (n & 0x5555...) + ((n >> 1) & 0x5555...);
    const uint64_t a = n - ((n >> 1) & ~0ULL / 3);
    // b = (a & 0x3333...) + ((a >> 2) & 0x3333...);
    const uint64_t b = (a & ~0ULL / 5) + ((a >> 2) & ~0ULL / 5);
    // c = (b & 0x0f0f...) + ((b >> 4) & 0x0f0f...);
    const uint64_t c = (b + (b >> 4)) & ~0ULL / 0x11;
    // d = (c & 0x00ff...) + ((c >> 8) & 0x00ff...);
    const uint64_t d = (c + (c >> 8)) & ~0ULL / 0x101;
    t = (d >> 32) + (d >> 48);
    // Now do branchless select!
    s = 64;
    // if (rank > t) {s -= 32; rank -= t;}
    s -= ((t - rank) & 256) >> 3;
    rank -= (t & ((t - rank) >> 8));
    t = (d >> (s - 16)) & 0xff;
    // if (rank > t) {s -= 16; rank -= t;}
    s -= ((t - rank) & 256) >> 4;
    rank -= (t & ((t - rank) >> 8));
    t = (c >> (s - 8)) & 0xf;
    // if (rank > t) {s -= 8; rank -= t;}
    s -= ((t - rank) & 256) >> 5;
    rank -= (t & ((t - rank) >> 8));
    t = (b >> (s - 4)) & 0x7;
    // if (rank > t) {s -= 4; rank -= t;}
    s -= ((t - rank) & 256) >> 6;
    rank -= (t & ((t - rank) >> 8));
    t = (a >> (s - 2)) & 0x3;
    // if (rank > t) {s -= 2; rank -= t;}
    s -= ((t - rank) & 256) >> 7;
    rank -= (t & ((t - rank) >> 8));
    t = (n >> (s - 1)) & 0x1;
    // if (rank > t) s--;
    s -= ((t - rank) & 256) >> 8;
    return 65 - s;
}


/**
 * @reference   Check if a number has same number of set and unset bits
 *              https://www.geeksforgeeks.org/check-if-a-number-has-same-number-of-set-and-unset-bits/
 *
 * Given a number N, the task is to check whether the count of the set and unset bits in the given
 * number are same.
 *
 * @tags    #count-set-bits
 */


/**
 * @reference   Check if binary representations of two numbers are anagram
 *              https://www.geeksforgeeks.org/check-binary-representations-two-numbers-anagram/
 *
 * @tags    #count-set-bits
 */
inline constexpr auto AreBitAnagram(const unsigned a, const unsigned b) {
    return CountSetBits_BrianKernighan(a) == CountSetBits_BrianKernighan(b);
}


/**
 * @reference   Check if binary representation of a given number and its complement are anagram
 *              https://www.geeksforgeeks.org/check-binary-representation-given-number-complement-anagram/
 *
 * @tags    #count-set-bits
 */
inline constexpr auto AreNumberAndItsComplementAnagram(const unsigned long long number) {
    return CountSetBits_BrianKernighan(number) == BitsNumber<decltype(number)> / 2;
}


/**
 * @reference   Prime Number of Set Bits in Binary Representation
 *              https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/
 *
 * Given two integers left and right, return the count of numbers in the inclusive range [left, right]
 * having a prime number of set bits in their binary representation.
 * Recall that the number of set bits an integer has is the number of 1's present when written in
 * binary.
 *  For example, 21 written in binary is 10101, which has 3 set bits.
 *
 * @tags    #count-set-bits
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


/**
 * @reference   Count number of bits to be flipped to convert A to B
 *              https://www.geeksforgeeks.org/count-number-of-bits-to-be-flipped-to-convert-a-to-b/
 * @reference   Number of mismatching bits in the binary representation of two integers
 *              https://www.geeksforgeeks.org/number-of-mismatching-bits-in-the-binary-representation-of-two-integers/
 * @reference   Count number of bits to be flipped to convert A to B | Set-2
 *              https://www.geeksforgeeks.org/count-number-of-bits-to-be-flipped-to-convert-a-to-b-set-2/
 *
 * Given two numbers 'a' and 'b'. Write a program to count number of bits needed to be flipped to
 * convert 'a' to 'b'.
 *
 * @reference   Minimum Bit Flips to Convert Number
 *              https://leetcode.com/problems/minimum-bit-flips-to-convert-number/
 *
 * A bit flip of a number x is choosing a bit in the binary representation of x and flipping it from
 * either 0 to 1 or 1 to 0.
 *  For example, for x = 7, the binary representation is 111 and we may choose any bit (including any
 *  leading zeros not shown) and flip it. We can flip the first bit from the right to get 110, flip the
 *  second bit from the right to get 101, flip the fifth bit from the right (a leading zero) to get
 *  10111, etc.
 * Given two integers start and goal, return the minimum number of bit flips to convert start to goal.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 5.5.
 *
 * @reference   Hamming Distance
 *              https://leetcode.com/problems/hamming-distance/
 *
 * The Hamming distance between two integers is the number of positions at which the corresponding bits
 * are different.
 * Given two integers x and y, return the Hamming distance between them.
 *
 * @tags    #count-set-bits
 */
inline constexpr auto CountDiffBits(const unsigned a, const unsigned b) {
    return CountSetBits_BrianKernighan(a ^ b);
}


/**
 * @reference   Minimum Number of Operations to Make Array XOR Equal to K
 *              https://leetcode.com/problems/minimum-number-of-operations-to-make-array-xor-equal-to-k/
 *
 * You are given a 0-indexed integer array nums and a positive integer k.
 * You can apply the following operation on the array any number of times:
 *  Choose any element of the array and flip a bit in its binary representation. Flipping a bit means
 *  changing a 0 to 1 or vice versa.
 * Return the minimum number of operations required to make the bitwise XOR of all elements of the final
 * array equal to k.
 * Note that you can flip leading zero bits in the binary representation of elements. For example, for
 * the number (101)2 you can flip the fourth bit and obtain (1101)2.
 *
 * @tags    #count-set-bits
 */


/**
 * @reference   Minimum Flips to Make a OR b Equal to c
 *              https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/
 *
 * Given 3 positives numbers a, b and c. Return the minimum flips required in some bits of a and b to
 * make ( a OR b == c ). (bitwise OR operation).
 * Flip operation consists of change any single bit 1 to 0 or change the bit 0 to 1 in their binary
 * representation.
 *
 * @tags    #count-set-bits
 */
constexpr auto MinFlips(const unsigned a, const unsigned b, const unsigned c) {
    const auto diff = (a | b) ^ c;

    int result = 0;
    for (unsigned i = 1; i <= diff; i <<= 1) {
        if (diff & i) {
            if (c & i) {
                ++result;
            } else {
                result += static_cast<bool>(a & i) + static_cast<bool>(b & i);
            }
        }
    }

    return result;
}

constexpr auto MinFlips_Popcount(const unsigned a, const unsigned b, const unsigned c) {
    const auto diff = (a | b) ^ c;
    return std::popcount(diff) + std::popcount(a & b & diff);
}


/**
 * @reference   K-th Symbol in Grammar
 *              https://leetcode.com/problems/k-th-symbol-in-grammar/
 *
 * We build a table of n rows (1-indexed). We start by writing 0 in the 1st row. Now in every subsequent
 * row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1
 * with 10.
 *  For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the 3rd row is 0110.
 * Given two integer n and k, return the kth (1-indexed) symbol in the nth row of a table of n rows.
 *
 * @tags    #count-set-bits
 */
constexpr int KthGrammar(const int, const unsigned k) {
    return std::popcount(k - 1) % 2;
}


/**
 * @reference   Find the K-th Character in String Game I
 *              https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/
 *
 * Alice and Bob are playing a game. Initially, Alice has a string word = "a".
 * You are given a positive integer k.
 * Now Bob will ask Alice to perform the following operation forever:
 *  Generate a new string by changing each character in word to its next character in the English
 *  alphabet, and append it to the original word.
 * For example, performing the operation on "c" generates "cd" and performing the operation on "zb"
 * generates "zbac".
 * Return the value of the kth character in word, after enough operations have been done for word to
 * have at least k characters.
 *
 * @tags    #count-set-bits
 */
constexpr char KthCharInGame(const unsigned k) {
    return 'a' + std::popcount(k - 1);
}


/**
 * @reference   Find the K-th Character in String Game II
 *              https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/
 *
 * Alice and Bob are playing a game. Initially, Alice has a string word = "a".
 * You are given a positive integer k. You are also given an integer array operations, where
 * operations[i] represents the type of the ith operation.
 * Now Bob will ask Alice to perform all operations in sequence:
 *  If operations[i] == 0, append a copy of word to itself.
 *  If operations[i] == 1, generate a new string by changing each character in word to its next character
 *  in the English alphabet, and append it to the original word. For example, performing the operation on
 *  "c" generates "cd" and performing the operation on "zb" generates "zbac".
 * Return the value of the kth character in word after performing all the operations.
 * Note that the character 'z' can be changed to 'a' in the second type of operation.
 *
 * @tags    #count-set-bits
 */
char KthCharInGameWithOperations(unsigned long long k, const ArrayType &operations) {
    --k;

    int diff = 0;
    for (unsigned long long i = 0; k and i < operations.size(); ++i) {
        diff += k & 1 & operations[i];
        k >>= 1;
    }

    return 'a' + (diff % 26);
}


/**
 * @reference   Minimum Operations to Make the Integer Zero
 *              https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/
 *
 * You are given two integers num1 and num2.
 * In one operation, you can choose integer i in the range [0, 60] and subtract 2i + num2 from num1.
 * Return the integer denoting the minimum number of operations needed to make num1 equal to 0.
 * If it is impossible to make num1 equal to 0, return -1.
 *
 * @tags    #bit-tricks #count-set-bits
 */
auto MinOperationsToMakeZero(long long num1, const int num2) {
    for (int i = 1; i <= 60; ++i) {
        num1 -= num2;
        if (num1 < i) {
            break;
        }

        const auto minimum = std::popcount(static_cast<unsigned long long>(num1));
        if (i >= minimum) {
            return i;
        }
    }

    return -1;
}

} //namespace


constexpr auto LOWER = std::numeric_limits<uint32_t>::min();
constexpr auto UPPER = std::numeric_limits<uint32_t>::max();


SIMPLE_BENCHMARK(CountSetBits_BrianKernighan, Sample1, LOWER);
SIMPLE_BENCHMARK(CountSetBits_BrianKernighan, Sample2, UPPER);

SIMPLE_TEST(CountSetBits_BrianKernighan, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountSetBits_BrianKernighan, TestUPPER, BitsNumber<decltype(UPPER)>, UPPER);
SIMPLE_TEST(CountSetBits_BrianKernighan, TestSAMPLE1, 2, 6);
SIMPLE_TEST(CountSetBits_BrianKernighan, TestSAMPLE2, 3, 13);


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
SIMPLE_TEST(CountSetBits_MagicBinaries32, TestUPPER, BitsNumber<decltype(UPPER)>, UPPER);
SIMPLE_TEST(CountSetBits_MagicBinaries32, TestSAMPLE1, 2, 6);
SIMPLE_TEST(CountSetBits_MagicBinaries32, TestSAMPLE2, 3, 13);

MUTUAL_RANDOM_TEST(CountSetBits_BrianKernighan, CountSetBits_MagicBinaries32, LOWER, UPPER);


SIMPLE_BENCHMARK(CountSetBits_MagicBinariesUnsigned, Sample1, LOWER);
SIMPLE_BENCHMARK(CountSetBits_MagicBinariesUnsigned, Sample2, UPPER);

SIMPLE_TEST(CountSetBits_MagicBinariesUnsigned, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountSetBits_MagicBinariesUnsigned, TestUPPER, BitsNumber<decltype(UPPER)>, UPPER);
SIMPLE_TEST(CountSetBits_MagicBinariesUnsigned, TestSAMPLE1, 2, 6);
SIMPLE_TEST(CountSetBits_MagicBinariesUnsigned, TestSAMPLE2, 3, 13);

MUTUAL_RANDOM_TEST(CountSetBits_BrianKernighan, CountSetBits_MagicBinariesUnsigned, LOWER, UPPER);


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
SIMPLE_TEST(SelectPositionWithCountFromMSB, TestSAMPLE1, 14, 0x06FFFFFFFFFFFFFF, CHAR_BIT);
SIMPLE_TEST(SelectPositionWithCountFromMSB, TestSAMPLE2, 13, 0x13FFFFFFFFFFFFFF, CHAR_BIT);


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


THE_BENCHMARK(MinFlips, 2, 6, 5);

SIMPLE_TEST(MinFlips, TestSample1, 3, 2, 6, 5);
SIMPLE_TEST(MinFlips, TestSample2, 1, 4, 2, 7);
SIMPLE_TEST(MinFlips, TestSample3, 0, 1, 2, 3);


THE_BENCHMARK(MinFlips_Popcount, 2, 6, 5);

SIMPLE_TEST(MinFlips_Popcount, TestSample1, 3, 2, 6, 5);
SIMPLE_TEST(MinFlips_Popcount, TestSample2, 1, 4, 2, 7);
SIMPLE_TEST(MinFlips_Popcount, TestSample3, 0, 1, 2, 3);


THE_BENCHMARK(KthGrammar, 1, 1);

SIMPLE_TEST(KthGrammar, TestSample1, 0, 1, 1);
SIMPLE_TEST(KthGrammar, TestSample2, 0, 2, 1);
SIMPLE_TEST(KthGrammar, TestSample3, 1, 2, 2);


THE_BENCHMARK(KthCharInGame, 5);

SIMPLE_TEST(KthCharInGame, TestSample1, 'b', 5);
SIMPLE_TEST(KthCharInGame, TestSample2, 'c', 10);
SIMPLE_TEST(KthCharInGame, TestSample3, 'd', 8);
SIMPLE_TEST(KthCharInGame, TestSample4, 'd', 12);


const ArrayType SAMPLE1 = {0, 0, 0};
const ArrayType SAMPLE2 = {0, 1, 0, 1};
const ArrayType SAMPLE3 = {1, 0};


THE_BENCHMARK(KthCharInGameWithOperations, 5, SAMPLE1);

SIMPLE_TEST(KthCharInGameWithOperations, TestSample1, 'a', 5, SAMPLE1);
SIMPLE_TEST(KthCharInGameWithOperations, TestSample2, 'b', 10, SAMPLE2);
SIMPLE_TEST(KthCharInGameWithOperations, TestSample3, 'a', 3, SAMPLE3);


THE_BENCHMARK(MinOperationsToMakeZero, 3, -2);

SIMPLE_TEST(MinOperationsToMakeZero, TestSample1, 3, 3, -2);
SIMPLE_TEST(MinOperationsToMakeZero, TestSample2, -1, 5, 7);
SIMPLE_TEST(MinOperationsToMakeZero, TestSample3, 16, 112577768, -501662198);
