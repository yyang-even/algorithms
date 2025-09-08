#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Minimum Cost to Divide Array Into Subarrays
 *              https://leetcode.com/problems/minimum-cost-to-divide-array-into-subarrays/
 *
 * You are given two integer arrays, nums and cost, of the same size, and an integer k.
 * You can divide nums into subarrays. The cost of the ith subarray consisting of elements nums[l..r]
 * is:
 *  (nums[0] + nums[1] + ... + nums[r] + k * i) * (cost[l] + cost[l + 1] + ... + cost[r]).
 * Note that i represents the order of the subarray: 1 for the first subarray, 2 for the second, and so
 * on.
 * Return the minimum total cost possible from any valid division.
 *
 * @tags    #DP #prefix-sum
 */
long long subarray_cost(const ArrayType &prefix_nums,
                        const ArrayType &prefix_cost,
                        const int k,
                        const long long i,
                        const int left,
                        const int right) {
    return (prefix_nums[right] + k * i) * (prefix_cost[right + 1] - prefix_cost[left]);
}

auto MinCostDivideIntoSubarrays(ArrayType nums, ArrayType cost, const int k) {
    const int N = nums.size();

    for (int i = 1; i < N; ++i) {
        nums[i] += nums[i - 1];
        cost[i] += cost[i - 1];
    }
    cost.insert(cost.cbegin(), 0);

    std::vector dp(N + 1, std::vector(N, 0ll));

    const int right = N - 1;
    for (int i = N; i >= 1; --i) {
        for (int left = i - 1; left <= right; ++left) {
            long long total_cost = subarray_cost(nums, cost, k, i, left, right);
            for (int x = left; x < right; ++x) {
                total_cost = std::min(
                    total_cost, subarray_cost(nums, cost, k, i, left, x) + dp[i + 1][x + 1]);
            }
            dp[i][left] = total_cost;
        }
    }

    return dp[1][0];
}


long long subarray_cost(const ArrayType &prefix_nums,
                        const ArrayType &prefix_cost,
                        const long long k,
                        const int left,
                        const int right) {
    return (prefix_nums[right + 1] - prefix_nums[left] + k) *
           (prefix_cost.back() - prefix_cost[left]);
}

auto MinCostDivideIntoSubarrays_1D(ArrayType nums, ArrayType cost, const int k) {
    const int N = nums.size();
    for (int i = 1; i < N; ++i) {
        nums[i] += nums[i - 1];
        cost[i] += cost[i - 1];
    }
    nums.insert(nums.cbegin(), 0);
    cost.insert(cost.cbegin(), 0);

    std::vector dp(N + 1, LLONG_MAX);
    dp[N] = 0;

    for (int left = N - 1; left >= 0; --left) {
        for (int x = left; x < N; ++x) {
            dp[left] = std::min(dp[left], subarray_cost(nums, cost, k, left, x) + dp[x + 1]);
        }
    }

    return dp[0];
}


/**
 * @reference   Largest Sum of Averages
 *              https://leetcode.com/problems/largest-sum-of-averages/
 *
 * You are given an integer array nums and an integer k. You can partition the array into at most k
 * non-empty adjacent subarrays. The score of a partition is the sum of the averages of each subarray.
 * Note that the partition must use every integer in nums, and that the score is not necessarily an
 * integer.
 * Return the maximum score you can achieve of all the possible partitions. Answers within 10-6 of the
 * actual answer will be accepted.
 *
 * @tags    #DP #prefix-sum
 */
double LargestSumOfAverages(ArrayType nums, const int k) {
    const int N = nums.size();

    int sum = 0;
    for (int i = 0; i < N; ++i) {
        const auto next = nums[i];
        nums[i] = sum;
        sum += next;
    }
    nums.push_back(sum);

    std::vector dp(k, std::vector(N, 0.0));
    for (int i = 0; i < N; ++i) {
        const double total = nums.back() - nums[i];
        const auto length = N - i;
        dp[0][i] = total / length;
    }

    for (int x = 1; x < k; ++x) {
        for (int i = 0; i < N - 1; ++i) {
            for (int j = i + 1; j < N; ++j) {
                const double total = nums[j] - nums[i];
                const auto length = j - i;
                const auto average = total / length;
                dp[x][i] = std::max(dp[x][i], average + dp[x - 1][j]);
            }
        }
    }

    return dp[k - 1][0];
}

} //namespace


const ArrayType SAMPLE1N = {3, 1, 4};
const ArrayType SAMPLE1C = {4, 6, 6};

const ArrayType SAMPLE2N = {4, 8, 5, 1, 14, 2, 2, 12, 1};
const ArrayType SAMPLE2C = {7, 2, 8, 4, 2, 2, 1, 1, 2};


THE_BENCHMARK(MinCostDivideIntoSubarrays, SAMPLE1N, SAMPLE1C, 1);

SIMPLE_TEST(MinCostDivideIntoSubarrays, TestSAMPLE1, 110, SAMPLE1N, SAMPLE1C, 1);
SIMPLE_TEST(MinCostDivideIntoSubarrays, TestSAMPLE2, 985, SAMPLE2N, SAMPLE2C, 7);


THE_BENCHMARK(MinCostDivideIntoSubarrays_1D, SAMPLE1N, SAMPLE1C, 1);

SIMPLE_TEST(MinCostDivideIntoSubarrays_1D, TestSAMPLE1, 110, SAMPLE1N, SAMPLE1C, 1);
SIMPLE_TEST(MinCostDivideIntoSubarrays_1D, TestSAMPLE2, 985, SAMPLE2N, SAMPLE2C, 7);


const ArrayType SAMPLE1A = {9, 1, 2, 3, 9};
const ArrayType SAMPLE2A = {1, 2, 3, 4, 5, 6, 7};


THE_BENCHMARK(LargestSumOfAverages, SAMPLE1A, 3);

SIMPLE_DOUBLE_TEST(LargestSumOfAverages, TestSAMPLE1, 20.0, SAMPLE1A, 3);
SIMPLE_DOUBLE_TEST(LargestSumOfAverages, TestSAMPLE2, 20.5, SAMPLE2A, 4);
