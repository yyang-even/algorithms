#include "common_header.h"

#include "clear_bits_range.h"


namespace {

/** Inserting m into n such that m starts at bit j and ends at bit i.
 *
 * @reference   https://www.geeksforgeeks.org/insertion-m-n-m-starts-bit-j-ends-bit/
 * @reference   Inserting M into N such that m starts at bit j and ends at bit i | Set-2
 *              https://www.geeksforgeeks.org/inserting-m-into-n-such-that-m-starts-at-bit-j-and-ends-at-bit-i-set-2/
 * @reference   Set bits in N equals to M in the given range.
 *              https://www.geeksforgeeks.org/set-bits-n-equals-m-given-range/
 *
 * We are given two numbers n and m, and two-bit positions, i and j. Insert bits of m
 * into n starting from j to i. We can assume that the bits j through i have enough
 * space to fit all of m. That is, if m = 10011, you can assume that there are at least
 * 5 bits between j and i. You would not, for example, have j = 3 and i = 2, because m
 * could not fully fit between bit 3 and bit 2.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 5.1.
 */
auto InsertBits(const unsigned n, const unsigned m,
                const unsigned i, const unsigned j) {
    const auto cleared_n = ClearBitsRange(n, i + 1, j + 1);
    return cleared_n | (m << i);
}

}//namespace


THE_BENCHMARK(InsertBits, 1024, 19, 2, 6);

SIMPLE_TEST(InsertBits, TestSAMPLE1, 1100, 1024, 19, 2, 6);
SIMPLE_TEST(InsertBits, TestSAMPLE2, 7, 5, 3, 1, 2);
SIMPLE_TEST(InsertBits, TestSAMPLE3, 1217, 1201, 8, 3, 6);
SIMPLE_TEST(InsertBits, TestSAMPLE4, 9, 1, 2, 2, 4);
SIMPLE_TEST(InsertBits, TestSAMPLE5, 18, 2, 4, 2, 4);
