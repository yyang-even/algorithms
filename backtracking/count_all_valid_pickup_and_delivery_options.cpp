#include "common_header.h"


namespace {

using MemoType = std::vector<std::vector<int>>;

/** Count All Valid Pickup and Delivery Options
 *
 * @reference   https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/
 *
 * Given n orders, each order consist in pickup and delivery services.
 * Count all valid pickup/delivery possible sequences such that delivery(i) is always after of
 * pickup(i).
 * Since the answer may be too large, return it modulo 10^9 + 7.
 */
long CountWays_Memo(const int unpicked, const int undelivered, MemoType &memo) {
    if (unpicked == 0 and undelivered == 0) {
        return 1;
    }

    if (unpicked < 0 or undelivered < 0 or undelivered < unpicked) {
        return 0;
    }

    if (memo[unpicked][undelivered]) {
        return memo[unpicked][undelivered];
    }

    auto result = unpicked * CountWays_Memo(unpicked - 1, undelivered, memo) % LARGE_PRIME;
    result +=
        (undelivered - unpicked) * CountWays_Memo(unpicked, undelivered - 1, memo) % LARGE_PRIME;

    return memo[unpicked][undelivered] = result;
}

inline auto CountWays_Memo(const int n) {
    std::vector memo(n + 1, std::vector(n + 1, 0));
    return CountWays_Memo(n, n, memo);
}


constexpr auto CountWays_Permutations(const int n) {
    long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
        result *= (2 * i - 1);
        result %= LARGE_PRIME;
    }

    return result;
}

} //namespace


THE_BENCHMARK(CountWays_Memo, 3);

SIMPLE_TEST(CountWays_Memo, TestSAMPLE1, 1, 1);
SIMPLE_TEST(CountWays_Memo, TestSAMPLE2, 6, 2);
SIMPLE_TEST(CountWays_Memo, TestSAMPLE3, 90, 3);


THE_BENCHMARK(CountWays_Permutations, 3);

SIMPLE_TEST(CountWays_Permutations, TestSAMPLE1, 1, 1);
SIMPLE_TEST(CountWays_Permutations, TestSAMPLE2, 6, 2);
SIMPLE_TEST(CountWays_Permutations, TestSAMPLE3, 90, 3);
