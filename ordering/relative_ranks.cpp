#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::vector<std::string>;

/** Relative Ranks
 *
 * @reference   https://leetcode.com/problems/relative-ranks/
 *
 * You are given an integer array score of size n, where score[i] is the score of the
 * ith athlete in a competition. All the scores are guaranteed to be unique. The
 * athletes are placed based on their scores, where the 1st place athlete has the
 * highest score, the 2nd place athlete has the 2nd highest score, and so on. The
 * placement of each athlete determines their rank:
 *  The 1st place athlete's rank is "Gold Medal".
 *  The 2nd place athlete's rank is "Silver Medal".
 *  The 3rd place athlete's rank is "Bronze Medal".
 *  For the 4th place to the nth place athlete, their rank is their placement number
 *      (i.e., the xth place athlete's rank is "x").
 * Return an array answer of size n where answer[i] is the rank of the ith athlete.
 */
auto RelativeRanks(const ArrayType &scores) {
    std::vector<std::pair<int, int>> scores_with_index;
    for (std::size_t i = 0; i < scores.size(); ++i) {
        scores_with_index.emplace_back(scores[i], i);
    }

    std::sort(scores_with_index.begin(), scores_with_index.end(),
    [](const auto lhs, const auto rhs) {
        return lhs.first > rhs.first;
    });

    OutputType result(scores.size(), "");
    for (std::size_t i = 0; i < scores_with_index.size(); ++i) {
        if (i == 0) {
            result[scores_with_index[i].second] = "Gold Medal";
        } else if (i == 1) {
            result[scores_with_index[i].second] = "Silver Medal";
        } else if (i == 2) {
            result[scores_with_index[i].second] = "Bronze Medal";
        } else {
            result[scores_with_index[i].second] = std::to_string(i + 1);
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {5, 4, 3, 2, 1};
const OutputType EXPECTED1 = {"Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"};

const ArrayType SAMPLE2 = {10, 3, 8, 9, 4};
const OutputType EXPECTED2 = {"Gold Medal", "5", "Bronze Medal", "Silver Medal", "4"};


THE_BENCHMARK(RelativeRanks, SAMPLE1);

SIMPLE_TEST(RelativeRanks, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(RelativeRanks, TestSAMPLE2, EXPECTED2, SAMPLE2);
