#include "common_header.h"


namespace {

using ArrayType = std::unordered_multiset<int>;

/** Numbers With Same Consecutive Differences
 *
 * @reference   https://leetcode.com/problems/numbers-with-same-consecutive-differences/
 *
 * Return all non-negative integers of length n such that the absolute difference between every two
 * consecutive digits is k.
 * Note that every number in the answer must not have leading zeros. For example, 01 has one leading
 * zero and is invalid.
 * You may return the answer in any order.
 * 2 <= n <= 9
 * 0 <= k <= 9
 */
auto NumWithSameConsecutiveDiffs(const int N, const int K, const int i, ArrayType &result) {
    if (N == 0) {
        result.insert(i);
        return;
    }

    const auto digit = i % 10;
    const auto differences = K ? std::vector {K, -K} : std::vector {K};
    for (const auto diff : differences) {
        const auto next = digit + diff;
        if (next >= 0 and next < 10) {
            NumWithSameConsecutiveDiffs(N - 1, K, i * 10 + next, result);
        }
    }
}

auto NumWithSameConsecutiveDiffs(const int N, const int K) {
    ArrayType result;
    if (N == 1) {
        result.insert(0);
    }

    for (int i = 1; i < 10; ++i) {
        NumWithSameConsecutiveDiffs(N - 1, K, i, result);
    }

    return result;
}

} //namespace


const ArrayType EXPECTED1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
const ArrayType EXPECTED2 = {181, 292, 707, 818, 929};
const ArrayType EXPECTED3 = {10, 12, 21, 23, 32, 34, 43, 45, 54, 56, 65, 67, 76, 78, 87, 89, 98};


THE_BENCHMARK(NumWithSameConsecutiveDiffs, 2, 1);

SIMPLE_TEST(NumWithSameConsecutiveDiffs, TestSAMPLE1, EXPECTED1, 1, 8);
SIMPLE_TEST(NumWithSameConsecutiveDiffs, TestSAMPLE2, EXPECTED2, 3, 7);
SIMPLE_TEST(NumWithSameConsecutiveDiffs, TestSAMPLE3, EXPECTED3, 2, 1);
