#include "common_header.h"


namespace {

/** Sum of Geometric Series
 *
 * @reference   Sum of the series 2^0 + 2^1 + 2^2 +…..+ 2^n
 *              https://www.geeksforgeeks.org/sum-of-the-series-20-21-22-2n/
 *
 * @tags    #geometric-progression #mersenne-number
 */
inline constexpr auto SumOfGeometricSeries(const unsigned N) {
    return (1 << (N + 1)) - 1;
}


/**
 * @reference   Find Kth Bit in Nth Binary String
 *              https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/
 *
 * Given two positive integers n and k, the binary string Sn is formed as follows:
 *  S1 = "0"
 *  Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1
 * Where + denotes the concatenation operation, reverse(x) returns the reversed string x, and invert(x)
 * inverts all the bits in x (0 changes to 1 and 1 changes to 0).
 * For example, the first four strings in the above sequence are:
 *  S1 = "0"
 *  S2 = "011"
 *  S3 = "0111001"
 *  S4 = "011100110110001"
 * Return the kth bit in Sn. It is guaranteed that k is valid for the given n.
 *
 * @tags    #geometric-progression #mersenne-number
 */


/**
 * @reference   Count Commas in Range
 *              https://leetcode.com/problems/count-commas-in-range/
 * @reference   Count Commas in Range II
 *              https://leetcode.com/problems/count-commas-in-range-ii/
 *
 * You are given an integer n.
 * Return the total number of commas used when writing all integers from [1, n] (inclusive) in standard
 * number formatting.
 * In standard formatting:
 *  A comma is inserted after every three digits from the right.
 *  Numbers with fewer than 4 digits contain no commas.
 *
 * @tags    #geometric-progression
 */

} //namespace


THE_BENCHMARK(SumOfGeometricSeries, 5);

SIMPLE_TEST(SumOfGeometricSeries, TestSAMPLE1, 31, 4);
SIMPLE_TEST(SumOfGeometricSeries, TestSAMPLE2, 1023, 9);
