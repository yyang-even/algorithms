#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

using MemoType = MatrixType;

/** K Inverse Pairs Array
 *
 * @reference   https://leetcode.com/problems/k-inverse-pairs-array/
 *
 * For an integer array nums, an inverse pair is a pair of integers [i, j] where
 * 0 <= i < j < nums.length and nums[i] > nums[j].
 * Given two integers n and k, return the number of different arrays consist of numbers
 * from 1 to n such that there are exactly k inverse pairs. Since the answer can be
 * huge, return it modulo 10^9 + 7.
 */
auto KInversePairsArray_Memo(const int n, const int k, MemoType &memo) {
    if (n == 0) {
        return 0;
    }
    if (k == 0) {
        return 1;
    }
    if (memo[n][k] != -1) {
        return memo[n][k];
    }
    int inverse_count = 0;
    for (int i = 0; i <= std::min(k, n - 1); ++i) {
        inverse_count += (KInversePairsArray_Memo(n - 1, k - i, memo)) % LARGE_PRIME;
    }
    memo[n][k] = inverse_count;
    return inverse_count;
}

inline auto KInversePairsArray_Memo(const int n, const int k) {
    MemoType memo(n + 1, MemoType::value_type(k + 1, -1));
    return KInversePairsArray_Memo(n, k, memo);
}


constexpr auto KInversePairsArray_DP(const int n, const int k) {
    int dp[n + 1][k + 1] = {};

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            if (j == 0) {
                dp[i][j] = 1;
            } else {
                for (int p = 0; p <= std::min(j, i - 1); ++p) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - p]) % LARGE_PRIME;
                }
            }
        }
    }

    return dp[n][k];
}


constexpr auto KInversePairsArray_DP_SpaceOptimized(const int n, const int k) {
    int buffer1[k + 1] = {};
    int buffer2[k + 1] = {};

    int *dp = buffer1;
    int *temp = buffer2;
    for (int i = 1; i <= n; ++i) {
        temp[0] = 1;
        for (int j = 1; j <= k ; ++j) {
            const int val = (dp[j] + LARGE_PRIME - ((j - i) >= 0 ? dp[j - i] : 0)) % LARGE_PRIME;
            temp[j] = (temp[j - 1] + val) % LARGE_PRIME;
        }
        std::swap(dp, temp);
    }
    return ((dp[k] + LARGE_PRIME - (k > 0 ? dp[k - 1] : 0)) % LARGE_PRIME);
}

}//namespace


THE_BENCHMARK(KInversePairsArray_Memo, 3, 1);

SIMPLE_TEST(KInversePairsArray_Memo, TestSAMPLE1, 2, 3, 1);
SIMPLE_TEST(KInversePairsArray_Memo, TestSAMPLE2, 1, 3, 0);


THE_BENCHMARK(KInversePairsArray_DP, 3, 1);

SIMPLE_TEST(KInversePairsArray_DP, TestSAMPLE1, 2, 3, 1);
SIMPLE_TEST(KInversePairsArray_DP, TestSAMPLE2, 1, 3, 0);


THE_BENCHMARK(KInversePairsArray_DP_SpaceOptimized, 3, 1);

SIMPLE_TEST(KInversePairsArray_DP_SpaceOptimized, TestSAMPLE1, 2, 3, 1);
SIMPLE_TEST(KInversePairsArray_DP_SpaceOptimized, TestSAMPLE2, 1, 3, 0);
