#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Maximum Xor Product
 *              https://leetcode.com/problems/maximum-xor-product/
 *
 * Given three integers a, b, and n, return the maximum value of (a XOR x) * (b XOR x) where 0 <= x <
 * 2^n.
 * Since the answer may be too large, return it modulo 10^9 + 7.
 * Note that XOR is the bitwise XOR operation.
 *
 * @tags    #greedy #bit-tricks
 */
int MaxXorProduct(unsigned long long a, unsigned long long b, const unsigned n) {
    if (n) {
        for (auto mask = 1ull << (n - 1); mask > 0; mask >>= 1) {
            if ((std::min(a, b) & mask) == 0) {
                a ^= mask;
                b ^= mask;
            }
        }
    }

    return ((a % LARGE_PRIME) * (b % LARGE_PRIME)) % LARGE_PRIME;
}

} //namespace


THE_BENCHMARK(MaxXorProduct, 12, 5, 4);

SIMPLE_TEST(MaxXorProduct, TestSAMPLE1, 98, 12, 5, 4);
SIMPLE_TEST(MaxXorProduct, TestSAMPLE2, 930, 6, 7, 5);
SIMPLE_TEST(MaxXorProduct, TestSAMPLE3, 12, 1, 6, 3);
SIMPLE_TEST(MaxXorProduct, TestSAMPLE4, 231850918, 53449611838892, 712958946092406, 6);
