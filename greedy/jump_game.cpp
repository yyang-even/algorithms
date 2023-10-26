#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Jump Game
 *
 * @reference   https://leetcode.com/problems/jump-game/
 *
 * You are given an integer array nums. You are initially positioned at the array's first index, and
 * each element in the array represents your maximum jump length at that position.
 * Return true if you can reach the last index, or false otherwise.
 * 1 <= nums.length <= 10^4
 * 0 <= nums[i] <= 10^5
 */
auto JumpGame(const ArrayType &nums) {
    int end = nums.size() - 1;
    for (int i = nums.size() - 2; i >= 0; --i) {
        if (i + nums[i] >= end) {
            end = i;
        }
    }
    return end == 0;
}


auto JumpGame_Max(const ArrayType &nums) {
    std::size_t position = nums[0];
    for (std::size_t i = 1; i < nums.size(); ++i) {
        if (position < i) {
            return false;
        }
        position = std::max(position, nums[i] + i);
    }

    return position + 1 >= nums.size();
}


/**
 * @reference   Jump Game II
 *              https://leetcode.com/problems/jump-game-ii/
 *
 * You are given a 0-indexed array of integers nums of length n. You are initially positioned at
 * nums[0].
 * Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if
 * you are at nums[i], you can jump to any nums[i + j] where:
 *  0 <= j <= nums[i] and
 *  i + j < n
 * Return the minimum number of jumps to reach nums[n - 1]. The test cases are generated such that you
 * can reach nums[n - 1].
 */
auto MinJumpGame(const ArrayType &nums) {
    if (nums.size() == 1) {
        return 0;
    }

    int result = 1;
    std::size_t current_last = nums[0];
    std::size_t next_last = 0;
    for (std::size_t i = 1; i < nums.size(); ++i) {
        if (current_last + 1 >= nums.size()) {
            return result;
        }

        if (i > current_last) {
            ++result;
            current_last = next_last;
        }

        if (i + nums[i] > next_last) {
            next_last = i + nums[i];
        }
    }

    return result;
}


auto MinJumpGame_DP(const ArrayType &nums) {
    const int N = nums.size();
    std::vector mini(N, N);
    mini[0] = 0;
    for (int i = 0; i < N; ++i) {
        for (auto j = std::min(i + nums[i], N - 1); j > i; --j) {
            if (mini[j] <= mini[i] + 1) {
                break;
            }
            mini[j] = mini[i] + 1;
        }
    }

    return mini[N - 1];
}


/**
 * @reference   Jump Game III
 *              https://leetcode.com/problems/jump-game-iii/
 *
 * Given an array of non-negative integers arr, you are initially positioned at start index of the
 * array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach to
 * any index with value 0.
 * Notice that you can not jump outside of the array at any time.
 */
auto BiJumpGame(const ArrayType &nums, const int start) {
    const int N = nums.size();
    assert(start >= 0 and start < N);

    std::queue<int> q;
    q.push(start);
    std::vector visited(N, false);

    while (not q.empty()) {
        const auto i = q.front();
        q.pop();

        if (nums[i] == 0) {
            return true;
        }

        if (visited[i]) {
            continue;
        }
        visited[i] = true;

        if (i - nums[i] >= 0) {
            q.push(i - nums[i]);
        }
        if (i + nums[i] < N) {
            q.push(i + nums[i]);
        }
    }

    return false;
}


/**
 * @reference   Jump Game IV
 *              https://leetcode.com/problems/jump-game-iv/
 *
 * Given an array of integers arr, you are initially positioned at the first index of the array.
 * In one step you can jump from index i to index:
 *  i + 1 where: i + 1 < arr.length.
 *  i - 1 where: i - 1 >= 0.
 *  j where: arr[i] == arr[j] and i != j.
 * Return the minimum number of steps to reach the last index of the array.
 * Notice that you can not jump outside of the array at any time.
 */
int JumpGame4(const ArrayType &nums) {
    std::unordered_map<int, std::vector<std::size_t>> occurrences;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        occurrences[nums[i]].push_back(i);
    }

    std::queue<std::size_t> q;
    q.push(0);
    std::vector<bool> seen(nums.size(), false);

    int result = 0;
    while (not q.empty()) {
        for (int size = q.size(); size > 0; --size) {
            const auto index = q.front();
            q.pop();

            if (index + 1 == nums.size()) {
                return result;
            }

            if (index > 0 and not seen[index - 1]) {
                q.push(index - 1);
                seen[index - 1] = true;
            }

            if (index + 1 < nums.size() and not seen[index + 1]) {
                q.push(index + 1);
                seen[index + 1] = true;
            }

            for (const auto i : occurrences[nums[index]]) {
                if (not seen[i]) {
                    q.push(i);
                    seen[i] = true;
                }
            }
            occurrences[nums[index]].clear();
        }

        ++result;
    }

    return -1;
}


/**
 * @reference   Jump Game V
 *              https://leetcode.com/problems/jump-game-v/
 * @reference   https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-1344-jump-game-v/
 *
 * Given an array of integers arr and an integer d. In one step you can jump from index i to index:
 *  i + x where: i + x < arr.length and 0 < x <= d.
 *  i - x where: i - x >= 0 and 0 < x <= d.
 * In addition, you can only jump from index i to index j if arr[i] > arr[j] and arr[i] > arr[k] for all
 * indices k between i and j (More formally min(i, j) < k < max(i, j)).
 * You can choose any index of the array and start jumping. Return the maximum number of indices you can
 * visit.
 * Notice that you can not jump outside of the array at any time.
 */
auto JumpGame5_Memo(const ArrayType &nums, const int d, const int i, ArrayType &memo) {
    if (memo[i]) {
        return memo[i];
    }

    const int size = nums.size();
    int result = 1;
    for (int j = i + 1; j <= std::min(size - 1, i + d) and nums[i] > nums[j]; ++j) {
        result = std::max(result, JumpGame5_Memo(nums, d, j, memo) + 1);
    }
    for (int j = i - 1; j >= std::max(0, i - d) and nums[i] > nums[j]; --j) {
        result = std::max(result, JumpGame5_Memo(nums, d, j, memo) + 1);
    }

    return memo[i] = result;
}

auto JumpGame5_Memo(const ArrayType &nums, const int d) {
    int result = 0;
    ArrayType memo(nums.size());
    for (std::size_t i = 0; i < nums.size(); ++i) {
        result = std::max(result, JumpGame5_Memo(nums, d, i, memo));
    }

    return result;
}


auto JumpGame5_DP(const ArrayType &nums, const int d) {
    std::vector<std::pair<int, int>> ordered_nums;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        ordered_nums.emplace_back(nums[i], i);
    }

    std::sort(ordered_nums.begin(), ordered_nums.end());

    const int size = nums.size();
    ArrayType dp(nums.size(), 1);
    for (const auto &[v, i] : ordered_nums) {
        for (int j = i + 1; j <= std::min(size - 1, i + d) and v > nums[j]; ++j) {
            dp[i] = std::max(dp[i], dp[j] + 1);
        }
        for (int j = i - 1; j >= std::max(0, i - d) and v > nums[j]; --j) {
            dp[i] = std::max(dp[i], dp[j] + 1);
        }
    }

    return *std::max_element(dp.cbegin(), dp.cend());
}


/**
 * @reference   Jump Game VI
 *              https://leetcode.com/problems/jump-game-vi/
 *
 * You are given a 0-indexed integer array nums and an integer k.
 * You are initially standing at index 0. In one move, you can jump at most k steps forward without
 * going outside the boundaries of the array. That is, you can jump from index i to any index in the
 * range [i + 1, min(n - 1, i + k)] inclusive.
 * You want to reach the last index of the array (index n - 1). Your score is the sum of all nums[j] for
 * each index j you visited in the array.
 * Return the maximum score you can get.
 */
auto JumpGame6_MonotonicQueue(const ArrayType &nums, const std::size_t k) {
    std::deque<std::size_t> q = {0};
    int dp[nums.size()] = {nums[0]};

    for (std::size_t i = 1; i < nums.size(); ++i) {
        dp[i] = nums[i] + dp[q.front()];
        while (not q.empty() and dp[i] >= dp[q.back()]) {
            q.pop_back();
        }
        while (not q.empty() and i - q.front() >= k) {
            q.pop_front();
        }
        q.push_back(i);
    }

    return dp[nums.size() - 1];
}


auto JumpGame6_PriorityQueue(const ArrayType &nums, const std::size_t k) {
    std::priority_queue<std::pair<int, std::size_t>> heap;
    heap.emplace(nums[0], 0);

    int result = nums[0];
    for (std::size_t i = 1; i < nums.size(); ++i) {
        while (not heap.empty() and heap.top().second + k < i) {
            heap.pop();
        }
        result = heap.top().first + nums[i];
        heap.emplace(result, i);
    }

    return result;
}


/**
 * @reference   Jump Game VII
 *              https://leetcode.com/problems/jump-game-vii/
 *
 * You are given a 0-indexed binary string s and two integers minJump and maxJump. In the beginning, you
 * are standing at index 0, which is equal to '0'. You can move from index i to index j if the following
 * conditions are fulfilled:
 *  i + minJump <= j <= min(i + maxJump, s.length - 1), and
 *  s[j] == '0'.
 * Return true if you can reach index s.length - 1 in s, or false otherwise.
 * s[i] is either '0' or '1'.
 */
auto JumpGame7_DP(const std::string_view s,
                  const std::size_t min_jump,
                  const std::size_t max_jump) {
    bool dp[s.size()] = {true};
    int number_jumpable_to_i = 0;
    for (std::size_t i = 1; i < s.size(); ++i) {
        if (i >= min_jump) {
            number_jumpable_to_i += dp[i - min_jump];
        }
        if (i > max_jump) {
            number_jumpable_to_i -= dp[i - max_jump - 1];
        }
        dp[i] = number_jumpable_to_i > 0 and s[i] == '0';
    }

    return dp[s.size() - 1];
}


auto JumpGame7_BFS(const std::string_view s,
                   const std::size_t min_jump,
                   const std::size_t max_jump) {
    if (s.back() == '1') {
        return false;
    }

    std::queue<std::size_t> q;
    q.push(0);

    std::size_t farthest = 0;
    while (!q.empty()) {

        const auto curr = q.front();
        q.pop();
        const auto start = curr + min_jump;
        const auto end = curr + max_jump;

        if (end >= s.size() - 1 and start < s.size()) {
            return true;
        } else if (start >= s.size()) {
            return false;
        }

        for (auto i = std::max(farthest, start); i <= end; ++i) {
            if (s[i] == '0') {
                q.push(i);
            }
        }

        farthest = end;
    }

    return false;
}


/**
 * @reference   Maximum Number of Jumps to Reach the Last Index
 *              https://leetcode.com/problems/maximum-number-of-jumps-to-reach-the-last-index/
 *
 * You are given a 0-indexed array nums of n integers and an integer target.
 * You are initially positioned at index 0. In one step, you can jump from index i to any index j such
 * that:
 *  0 <= i < j < n
 *  -target <= nums[j] - nums[i] <= target
 * Return the maximum number of jumps you can make to reach index n - 1.
 * If there is no way to reach index n - 1, return -1.
 */
auto MaximumJumps(const ArrayType &nums, const int target) {
    std::vector dp(nums.size(), -1);
    dp[0] = 0;

    for (std::size_t i = 0; i < nums.size(); ++i) {
        if (dp[i] != -1) {
            for (auto j = i + 1; j < nums.size(); ++j) {
                if (std::abs(nums[i] - nums[j]) <= target) {
                    dp[j] = std::max(dp[j], dp[i] + 1);
                }
            }
        }
    }

    return dp.back();
}

} //namespace


const ArrayType SAMPLE1 = {2, 3, 1, 1, 4};
const ArrayType SAMPLE2 = {3, 2, 1, 0, 4};
const ArrayType SAMPLE3 = {1, 1, 1, 0};
const ArrayType SAMPLE4 = {0};


THE_BENCHMARK(JumpGame, SAMPLE1);

SIMPLE_TEST(JumpGame, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(JumpGame, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(JumpGame, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(JumpGame, TestSAMPLE4, true, SAMPLE4);


THE_BENCHMARK(JumpGame_Max, SAMPLE1);

SIMPLE_TEST(JumpGame_Max, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(JumpGame_Max, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(JumpGame_Max, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(JumpGame_Max, TestSAMPLE4, true, SAMPLE4);


const ArrayType SAMPLE5 = {2, 3, 0, 1, 4};
const ArrayType SAMPLE6 = {1, 1, 2, 1, 1};


THE_BENCHMARK(MinJumpGame_DP, SAMPLE1);

SIMPLE_TEST(MinJumpGame_DP, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(MinJumpGame_DP, TestSAMPLE4, 0, SAMPLE4);
SIMPLE_TEST(MinJumpGame_DP, TestSAMPLE5, 2, SAMPLE5);
SIMPLE_TEST(MinJumpGame_DP, TestSAMPLE6, 3, SAMPLE6);


THE_BENCHMARK(MinJumpGame, SAMPLE1);

SIMPLE_TEST(MinJumpGame, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(MinJumpGame, TestSAMPLE4, 0, SAMPLE4);
SIMPLE_TEST(MinJumpGame, TestSAMPLE5, 2, SAMPLE5);
SIMPLE_TEST(MinJumpGame, TestSAMPLE6, 3, SAMPLE6);


const ArrayType SAMPLE1B = {4, 2, 3, 0, 3, 1, 2};
const ArrayType SAMPLE2B = {3, 0, 2, 1, 2};


THE_BENCHMARK(BiJumpGame, SAMPLE1B, 5);

SIMPLE_TEST(BiJumpGame, TestSAMPLE1, true, SAMPLE1B, 5);
SIMPLE_TEST(BiJumpGame, TestSAMPLE2, true, SAMPLE1B, 0);
SIMPLE_TEST(BiJumpGame, TestSAMPLE3, false, SAMPLE2B, 2);


const ArrayType SAMPLE1F = {100, -23, -23, 404, 100, 23, 23, 23, 3, 404};
const ArrayType SAMPLE2F = {7};
const ArrayType SAMPLE3F = {7, 6, 9, 6, 9, 6, 9, 7};
const ArrayType SAMPLE4F = {6, 1, 9};
const ArrayType SAMPLE5F = {11, 22, 7, 7, 7, 7, 7, 7, 7, 22, 13};


THE_BENCHMARK(JumpGame4, SAMPLE1F);

SIMPLE_TEST(JumpGame4, TestSAMPLE1, 3, SAMPLE1F);
SIMPLE_TEST(JumpGame4, TestSAMPLE2, 0, SAMPLE2F);
SIMPLE_TEST(JumpGame4, TestSAMPLE3, 1, SAMPLE3F);
SIMPLE_TEST(JumpGame4, TestSAMPLE4, 2, SAMPLE4F);
SIMPLE_TEST(JumpGame4, TestSAMPLE5, 3, SAMPLE5F);


const ArrayType SAMPLE1I = {6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12};
const ArrayType SAMPLE2I = {3, 3, 3, 3, 3};
const ArrayType SAMPLE3I = {7, 6, 5, 4, 3, 2, 1};
const ArrayType SAMPLE4I = {7, 1, 7, 1, 7, 1};
const ArrayType SAMPLE5I = {66};


THE_BENCHMARK(JumpGame5_Memo, SAMPLE1I, 2);

SIMPLE_TEST(JumpGame5_Memo, TestSAMPLE1, 4, SAMPLE1I, 2);
SIMPLE_TEST(JumpGame5_Memo, TestSAMPLE2, 1, SAMPLE2I, 3);
SIMPLE_TEST(JumpGame5_Memo, TestSAMPLE3, 7, SAMPLE3I, 1);
SIMPLE_TEST(JumpGame5_Memo, TestSAMPLE4, 2, SAMPLE4I, 2);
SIMPLE_TEST(JumpGame5_Memo, TestSAMPLE5, 1, SAMPLE5I, 1);


THE_BENCHMARK(JumpGame5_DP, SAMPLE1I, 2);

SIMPLE_TEST(JumpGame5_DP, TestSAMPLE1, 4, SAMPLE1I, 2);
SIMPLE_TEST(JumpGame5_DP, TestSAMPLE2, 1, SAMPLE2I, 3);
SIMPLE_TEST(JumpGame5_DP, TestSAMPLE3, 7, SAMPLE3I, 1);
SIMPLE_TEST(JumpGame5_DP, TestSAMPLE4, 2, SAMPLE4I, 2);
SIMPLE_TEST(JumpGame5_DP, TestSAMPLE5, 1, SAMPLE5I, 1);


const ArrayType SAMPLE1S = {1, -1, -2, 4, -7, 3};
const ArrayType SAMPLE2S = {10, -5, -2, 4, 0, 3};
const ArrayType SAMPLE3S = {1, -5, -20, 4, -1, 3, -6, -3};


THE_BENCHMARK(JumpGame6_MonotonicQueue, SAMPLE1S, 2);

SIMPLE_TEST(JumpGame6_MonotonicQueue, TestSAMPLE1, 7, SAMPLE1S, 2);
SIMPLE_TEST(JumpGame6_MonotonicQueue, TestSAMPLE2, 17, SAMPLE2S, 3);
SIMPLE_TEST(JumpGame6_MonotonicQueue, TestSAMPLE3, 0, SAMPLE3S, 2);


THE_BENCHMARK(JumpGame6_PriorityQueue, SAMPLE1S, 2);

SIMPLE_TEST(JumpGame6_PriorityQueue, TestSAMPLE1, 7, SAMPLE1S, 2);
SIMPLE_TEST(JumpGame6_PriorityQueue, TestSAMPLE2, 17, SAMPLE2S, 3);
SIMPLE_TEST(JumpGame6_PriorityQueue, TestSAMPLE3, 0, SAMPLE3S, 2);


THE_BENCHMARK(JumpGame7_DP, "011010", 2, 3);

SIMPLE_TEST(JumpGame7_DP, TestSAMPLE1, true, "011010", 2, 3);
SIMPLE_TEST(JumpGame7_DP, TestSAMPLE2, false, "01101110", 2, 3);


THE_BENCHMARK(JumpGame7_BFS, "011010", 2, 3);

SIMPLE_TEST(JumpGame7_BFS, TestSAMPLE1, true, "011010", 2, 3);
SIMPLE_TEST(JumpGame7_BFS, TestSAMPLE2, false, "01101110", 2, 3);


const ArrayType SAMPLE1M = {1, 3, 6, 4, 1, 2};
const ArrayType SAMPLE2M = {0, 2, 1, 3};


THE_BENCHMARK(MaximumJumps, SAMPLE1M, 2);

SIMPLE_TEST(MaximumJumps, TestSAMPLE1, 3, SAMPLE1M, 2);
SIMPLE_TEST(MaximumJumps, TestSAMPLE2, 5, SAMPLE1M, 3);
SIMPLE_TEST(MaximumJumps, TestSAMPLE3, -1, SAMPLE1M, 0);
SIMPLE_TEST(MaximumJumps, TestSAMPLE4, -1, SAMPLE2M, 1);
