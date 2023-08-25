#include "common_header.h"


namespace {

/** Integer Replacement
 *
 * @reference   https://leetcode.com/problems/integer-replacement/
 *
 * Given a positive integer n, you can apply one of the following operations:
 *  If n is even, replace n with n / 2.
 *  If n is odd, replace n with either n + 1 or n - 1.
 * Return the minimum number of operations needed for n to become 1.
 */
constexpr auto IntReplacement(unsigned n) {
    int result = 0;
    while (n != 1) {
        ++result;

        if ((n & 1) == 0) {
            n >>= 1;
        } else if (n == 3 or std::popcount(n + 1) > std::popcount(n - 1)) {
            --n;
        } else {
            ++n;
        }
    }

    return result;
}

} //namespace


THE_BENCHMARK(IntReplacement, 1234);

SIMPLE_TEST(IntReplacement, TestSAMPLE1, 3, 8);
SIMPLE_TEST(IntReplacement, TestSAMPLE2, 4, 7);
SIMPLE_TEST(IntReplacement, TestSAMPLE3, 2, 4);
SIMPLE_TEST(IntReplacement, TestSAMPLE4, 17, 65535);
SIMPLE_TEST(IntReplacement, TestSAMPLE5, 14, 1234);
