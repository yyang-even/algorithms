#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Counting Bits
 *
 * @reference   https://leetcode.com/problems/counting-bits/
 *
 * Given an integer n, return an array ans of length n + 1 such that for each i
 * (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
 * Follow up: It is very easy to come up with a solution with a runtime of O(n log n).
 * Can you do it in linear time O(n) and possibly in a single pass? Can you do it
 * without using any built-in function (i.e., like __builtin_popcount in C++)?
 */
auto CountNBits(const unsigned n) {
    ArrayType results = {0};
    for (unsigned i = 1; i <= n; ++i) {
        results.push_back(1 + results[i & (i - 1)]);
    }

    return results;
}

}//namespace


const ArrayType EXPECTED1 = {0, 1, 1, 2, 1, 2};

THE_BENCHMARK(CountNBits, 5);

SIMPLE_TEST(CountNBits, TestSAMPLE1, EXPECTED1, 5);
