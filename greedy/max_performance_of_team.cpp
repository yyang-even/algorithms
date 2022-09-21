#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Maximum Performance of a Team
 *
 * @reference   https://leetcode.com/problems/maximum-performance-of-a-team/
 *
 * You are given two integers n and k and two integer arrays speed and efficiency both of length n.
 * There are n engineers numbered from 1 to n. speed[i] and efficiency[i] represent the speed and
 * efficiency of the ith engineer respectively.
 * Choose at most k different engineers out of the n engineers to form a team with the maximum
 * performance.
 * The performance of a team is the sum of their engineers' speeds multiplied by the minimum efficiency
 * among their engineers.
 * Return the maximum performance of this team. Since the answer can be a huge number, return it modulo
 * 10^9 + 7.
 */
int MaxPerformanceOfTeam(const int n,
                         const ArrayType &speed,
                         const ArrayType &efficiency,
                         const std::size_t k) {
    std::vector<std::pair<int, int>> efficiency_speed;
    for (int i = 0; i < n; ++i) {
        efficiency_speed.emplace_back(efficiency[i], speed[i]);
    }

    std::sort(
        efficiency_speed.begin(), efficiency_speed.end(), std::greater<std::pair<int, int>> {});

    long sum_speed = 0;
    long result = 0;
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    for (const auto &[e, s] : efficiency_speed) {
        min_heap.push(s);
        sum_speed += s;

        if (min_heap.size() > k) {
            sum_speed -= min_heap.top();
            min_heap.pop();
        }

        result = std::max(result, sum_speed * e);
    }

    return result % LARGE_PRIME;
}

} //namespace


const ArrayType SAMPLE1S = {2, 10, 3, 1, 5, 8};
const ArrayType SAMPLE1E = {5, 4, 3, 9, 7, 2};


THE_BENCHMARK(MaxPerformanceOfTeam, 6, SAMPLE1S, SAMPLE1E, 2);

SIMPLE_TEST(MaxPerformanceOfTeam, TestSAMPLE1, 60, 6, SAMPLE1S, SAMPLE1E, 2);
SIMPLE_TEST(MaxPerformanceOfTeam, TestSAMPLE2, 68, 6, SAMPLE1S, SAMPLE1E, 3);
SIMPLE_TEST(MaxPerformanceOfTeam, TestSAMPLE3, 72, 6, SAMPLE1S, SAMPLE1E, 4);
