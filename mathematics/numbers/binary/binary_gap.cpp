#include "common_header.h"


namespace {

/** Binary Gap
 *
 * @reference   https://leetcode.com/problems/binary-gap/
 *
 * Given a positive integer n, find and return the longest distance between any two
 * adjacent 1's in the binary representation of n. If there are no two adjacent 1's,
 * return 0. Two 1's are adjacent if there are only 0's separating them (possibly no
 * 0's). The distance between two 1's is the absolute difference between their bit
 * positions. For example, the two 1's in "1001" have a distance of 3.
 */
constexpr auto BinaryGap(const unsigned n) {
    int prev = -1;
    int result = 0;
    for (int i = 0; (1u << i) <= n; ++i) {
        if (n & (1u << i)) {
            if (prev != -1) {
                result = std::max(result, i - prev);
            }
            prev = i;
        }
    }

    return result;
}

}//namespace


THE_BENCHMARK(BinaryGap, 22);

SIMPLE_TEST(BinaryGap, TestSAMPLE1, 2, 22);
SIMPLE_TEST(BinaryGap, TestSAMPLE2, 2, 5);
SIMPLE_TEST(BinaryGap, TestSAMPLE3, 1, 6);
SIMPLE_TEST(BinaryGap, TestSAMPLE4, 0, 8);
SIMPLE_TEST(BinaryGap, TestSAMPLE5, 0, 1);
