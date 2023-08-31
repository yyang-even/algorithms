#include "common_header.h"


namespace {

/** Integer Break
 *
 * @reference   https://leetcode.com/problems/integer-break/
 *
 * Given an integer n, break it into the sum of k positive integers, where k >= 2, and maximize the
 * product of those integers.
 * Return the maximum product you can get.
 *
 * @hint    All factors should be 2 or 3.
 */
constexpr auto IntBreak(const int n) {
    if (n == 2) {
        return 1;
    }

    if (n == 3) {
        return 2;
    }

    int num_3 = n / 3;
    int remainder = n % 3;
    if (remainder == 1) {
        remainder = 4;
        --num_3;
    } else if (remainder == 0) {
        remainder = 1;
    }

    return static_cast<int>(std::pow(3, num_3)) * remainder;
}

} //namespace


THE_BENCHMARK(IntBreak, 10);

SIMPLE_TEST(IntBreak, TestSAMPLE1, 36, 10);
SIMPLE_TEST(IntBreak, TestSAMPLE2, 1, 2);
