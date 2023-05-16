#include "common_header.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

/** Solving Questions With Brainpower
 *
 * @reference   https://leetcode.com/problems/solving-questions-with-brainpower/
 *
 * You are given a 0-indexed 2D integer array questions where questions[i] = [pointsi, brainpoweri].
 * The array describes the questions of an exam, where you have to process the questions in order (i.e.,
 * starting from question 0) and make a decision whether to solve or skip each question. Solving
 * question i will earn you pointsi points but you will be unable to solve each of the next brainpoweri
 * questions. If you skip question i, you get to make the decision on the next question.
 *  For example, given questions = [[3, 2], [4, 3], [4, 4], [2, 5]]:
 *      If question 0 is solved, you will earn 3 points but you will be unable to solve questions 1 and 2.
 *      If instead, question 0 is skipped and question 1 is solved, you will earn 4 points but you will
 *      be unable to solve questions 2 and 3.
 * Return the maximum points you can earn for the exam.
 */
auto MostPoints(const ArrayType &questions) {
    std::vector<long long> dp(questions.size() + 1);
    for (int i = questions.size() - 1; i >= 0; --i) {
        const auto &[point, brain_power] = questions[i];
        dp[i] =
            std::max(point + dp[std::min(questions.size(), brain_power + i + 1ul)], dp[i + 1]);
    }

    return dp[0];
}

} //namespace


const ArrayType SAMPLE1 = {{3, 2}, {4, 3}, {4, 4}, {2, 5}};
const ArrayType SAMPLE2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};


THE_BENCHMARK(MostPoints, SAMPLE1);

SIMPLE_TEST(MostPoints, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(MostPoints, TestSAMPLE2, 7, SAMPLE2);
