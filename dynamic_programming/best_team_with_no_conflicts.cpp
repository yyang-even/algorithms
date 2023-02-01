#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Best Team With No Conflicts
 *
 * @reference   https://leetcode.com/problems/best-team-with-no-conflicts/
 *
 * You are the manager of a basketball team. For the upcoming tournament, you want to choose the team
 * with the highest overall score. The score of the team is the sum of scores of all the players in the
 * team.
 * However, the basketball team is not allowed to have conflicts. A conflict exists if a younger player
 * has a strictly higher score than an older player. A conflict does not occur between players of the
 * same age.
 * Given two lists, scores and ages, where each scores[i] and ages[i] represents the score and age of
 * the ith player, respectively, return the highest overall score of all possible basketball teams.
 */
auto BestTeamWithNoConflicts(const ArrayType &scores, const ArrayType &ages) {
    std::vector<std::pair<int, int>> players;
    for (std::size_t i = 0; i < scores.size(); ++i) {
        players.emplace_back(ages[i], scores[i]);
    }
    std::sort(players.begin(), players.end(), std::greater<>());

    int result = 0;
    ArrayType dp(scores.size());
    for (std::size_t i = 0; i < players.size(); ++i) {
        const auto s = players[i].second;
        dp[i] = s;

        for (std::size_t j = 0; j < i; ++j) {
            if (players[j].second >= s) {
                dp[i] = std::max(dp[i], dp[j] + s);
            }
        }

        result = std::max(result, dp[i]);
    }
    return result;
}

} //namespace


const ArrayType SAMPLE1S = {1, 3, 5, 10, 15};
const ArrayType SAMPLE1A = {1, 2, 3, 4, 5};

const ArrayType SAMPLE2S = {4, 5, 6, 5};
const ArrayType SAMPLE2A = {2, 1, 2, 1};

const ArrayType SAMPLE3S = {1, 2, 3, 5};
const ArrayType SAMPLE3A = {8, 9, 10, 1};


THE_BENCHMARK(BestTeamWithNoConflicts, SAMPLE1S, SAMPLE1A);

SIMPLE_TEST(BestTeamWithNoConflicts, TestSAMPLE1, 34, SAMPLE1S, SAMPLE1A);
SIMPLE_TEST(BestTeamWithNoConflicts, TestSAMPLE2, 16, SAMPLE2S, SAMPLE2A);
SIMPLE_TEST(BestTeamWithNoConflicts, TestSAMPLE3, 6, SAMPLE3S, SAMPLE3A);
