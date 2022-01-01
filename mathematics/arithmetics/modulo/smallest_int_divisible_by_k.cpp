#include "common_header.h"


namespace {

/** Smallest Integer Divisible by K
 *
 * @reference   https://leetcode.com/problems/smallest-integer-divisible-by-k/
 *
 * Given a positive integer k, you need to find the length of the smallest positive
 * integer n such that n is divisible by k, and n only contains the digit 1. Return
 * the length of n. If there is no such n, return -1. Note: n may not fit in a 64-bit
 * signed integer.
 */
constexpr auto SmallestIntDivisibleBy(const int K) {
    if (K % 2 == 0 or K % 5 == 0) {
        return -1;
    }

    int remainder = 0;
    for (int length = 1; length <= K; ++length) {
        remainder = (remainder * 10 + 1) % K;
        if (remainder == 0) {
            return length;
        }
    }

    return -1;
}

}//namespace


THE_BENCHMARK(SmallestIntDivisibleBy, 3);

SIMPLE_TEST(SmallestIntDivisibleBy, TestSAMPLE1, 1, 1);
SIMPLE_TEST(SmallestIntDivisibleBy, TestSAMPLE2, -1, 2);
SIMPLE_TEST(SmallestIntDivisibleBy, TestSAMPLE3, 3, 3);
