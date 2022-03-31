#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using MemoType = std::vector<std::vector<int>>;

/** Split Array Largest Sum
 *
 * @reference   https://leetcode.com/problems/split-array-largest-sum/
 *
 * Given an array nums which consists of non-negative integers and an integer m, you can
 * split the array into m non-empty continuous subarrays.
 * Write an algorithm to minimize the largest sum among these m subarrays.
 */
auto
SplitArrayLargestSum_Memo(const ArrayType &prefix_sums, const int start, const int m,
                          MemoType &memo) {
    const int N = prefix_sums.size() - 1;

    if (memo[start][m] != -1) {
        return memo[start][m];
    }

    if (m == 1) {
        return memo[start][m] = prefix_sums[N] - prefix_sums[start];
    }

    auto result = INT_MAX;
    for (auto i = start; i <= N - m; ++i) {
        const auto current_sum = prefix_sums[i + 1] - prefix_sums[start];
        const auto current_result = std::max(current_sum,
                                             SplitArrayLargestSum_Memo(prefix_sums, i + 1, m - 1, memo));

        result = std::min(result, current_result);

        if (current_sum >= result) {
            break;
        }
    }

    return memo[start][m] = result;
}

auto SplitArrayLargestSum_Memo(const ArrayType &nums, const int m) {
    ArrayType prefix_sums(nums.size() + 1);
    for (std::size_t i = 0; i < nums.size(); ++i) {
        prefix_sums[i + 1] = prefix_sums[i] + nums[i];
    }

    MemoType memo(nums.size(), std::vector(m + 1, -1));
    return SplitArrayLargestSum_Memo(prefix_sums, 0, m, memo);
}


auto MinSubarraysRequired(const ArrayType &nums, const int max_sum) {
    int sum = 0;
    int result = 1;
    for (const auto n : nums) {
        if (sum + n <= max_sum) {
            sum += n;
        } else {
            sum = n;
            ++result;
        }
    }

    return result;
}

auto SplitArrayLargestSum_BinarySearch(const ArrayType &nums, const int m) {
    const auto total_sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
    const auto maximum = *std::max_element(nums.cbegin(), nums.cend());

    auto left = maximum;
    auto right = total_sum;
    int result = 0;
    while (left <= right) {
        const auto mid = (left + right) / 2;

        if (MinSubarraysRequired(nums, mid) <= m) {
            right = mid - 1;
            result = mid;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {7, 2, 5, 10, 8};
const ArrayType SAMPLE2 = {1, 2, 3, 4, 5};
const ArrayType SAMPLE3 = {1, 4, 4};


THE_BENCHMARK(SplitArrayLargestSum_Memo, SAMPLE1, 2);

SIMPLE_TEST(SplitArrayLargestSum_Memo, TestSAMPLE1, 18, SAMPLE1, 2);
SIMPLE_TEST(SplitArrayLargestSum_Memo, TestSAMPLE2, 9, SAMPLE2, 2);
SIMPLE_TEST(SplitArrayLargestSum_Memo, TestSAMPLE3, 4, SAMPLE3, 3);


THE_BENCHMARK(SplitArrayLargestSum_BinarySearch, SAMPLE1, 2);

SIMPLE_TEST(SplitArrayLargestSum_BinarySearch, TestSAMPLE1, 18, SAMPLE1, 2);
SIMPLE_TEST(SplitArrayLargestSum_BinarySearch, TestSAMPLE2, 9, SAMPLE2, 2);
SIMPLE_TEST(SplitArrayLargestSum_BinarySearch, TestSAMPLE3, 4, SAMPLE3, 3);
