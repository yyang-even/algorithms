#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Minimum Difficulty of a Job Schedule
 *
 * @reference   https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/
 *
 * You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the ith job, you
 * have to finish all the jobs j where 0 <= j < i).
 * You have to finish at least one task every day. The difficulty of a job schedule is the sum of
 * difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a job
 * done on that day.
 * You are given an integer array jobDifficulty and an integer d. The difficulty of the ith job is
 * jobDifficulty[i].
 * Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return
 * -1.
 */
int MinDifficultyOfAJobSchedule_Memo(const int i,
                                     const ArrayType &jobDifficulty,
                                     const int d,
                                     std::vector<std::vector<int>> &memo) {
    const int N = jobDifficulty.size();

    if (d == 0 and i == N) {
        return 0;
    }

    if (d == 0 or i == N) {
        return INT_MAX;
    }

    if (memo[i][d] != -1) {
        return memo[i][d];
    }

    int maximum = jobDifficulty[i];
    int result = INT_MAX;
    for (int x = i; x < N; ++x) {
        maximum = std::max(maximum, jobDifficulty[x]);
        const auto sub_result =
            MinDifficultyOfAJobSchedule_Memo(x + 1, jobDifficulty, d - 1, memo);
        if (sub_result != INT_MAX) {
            result = std::min(result, sub_result + maximum);
        }
    }

    return memo[i][d] = result;
}

auto MinDifficultyOfAJobSchedule_Memo(const ArrayType &jobDifficulty, const int d) {
    const int N = jobDifficulty.size();
    if (N < d) {
        return -1;
    }

    std::vector memo(N, std::vector(d + 1, -1));
    return MinDifficultyOfAJobSchedule_Memo(0, jobDifficulty, d, memo);
}


auto MinDifficultyOfAJobSchedule_DP(const ArrayType &jobDifficulty, const int d) {
    const int N = jobDifficulty.size();
    const int MAXIMUM = 1e9;

    if (N < d) {
        return -1;
    }

    std::vector dp(N + 1, MAXIMUM);
    dp[N] = 0;

    for (int x = 1; x <= d; ++x) {
        for (int i = 0; i <= N - x; ++i) {
            int current_max = 0;
            dp[i] = MAXIMUM;
            for (auto j = i; j <= N - x; ++j) {
                current_max = std::max(current_max, jobDifficulty[j]);
                dp[i] = std::min(dp[i], current_max + dp[j + 1]);
            }
        }
    }

    return dp[0];
}

} //namespace


const ArrayType SAMPLE1 = {6, 5, 4, 3, 2, 1};
const ArrayType SAMPLE2 = {9, 9, 9};
const ArrayType SAMPLE3 = {1, 1, 1};


THE_BENCHMARK(MinDifficultyOfAJobSchedule_Memo, SAMPLE1, 2);

SIMPLE_TEST(MinDifficultyOfAJobSchedule_Memo, TestSAMPLE1, 7, SAMPLE1, 2);
SIMPLE_TEST(MinDifficultyOfAJobSchedule_Memo, TestSAMPLE2, -1, SAMPLE2, 4);
SIMPLE_TEST(MinDifficultyOfAJobSchedule_Memo, TestSAMPLE3, 3, SAMPLE3, 3);


THE_BENCHMARK(MinDifficultyOfAJobSchedule_DP, SAMPLE1, 2);

SIMPLE_TEST(MinDifficultyOfAJobSchedule_DP, TestSAMPLE1, 7, SAMPLE1, 2);
SIMPLE_TEST(MinDifficultyOfAJobSchedule_DP, TestSAMPLE2, -1, SAMPLE2, 4);
SIMPLE_TEST(MinDifficultyOfAJobSchedule_DP, TestSAMPLE3, 3, SAMPLE3, 3);
