#include "common_header.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

/** Two City Scheduling
 *
 * @reference   https://leetcode.com/problems/two-city-scheduling/
 *
 * A company is planning to interview 2n people. Given the array costs where
 * costs[i] = [aCosti, bCosti], the cost of flying the ith person to city a is aCosti,
 * and the cost of flying the ith person to city b is bCosti.
 * Return the minimum cost to fly every person to a city such that exactly n people
 * arrive in each city.
 */
auto TwoCityScheduling(const ArrayType &costs) {
    std::vector<int> diffs;
    int result = 0;

    for (const auto &[a, b] : costs) {
        result += a;
        diffs.push_back(b - a);
    }

    std::sort(diffs.begin(), diffs.end());

    for (std::size_t i = 0; i < costs.size() / 2; ++i) {
        result += diffs[i];
    }

    return result;
}


auto TwoCityScheduling_SpaceO1(ArrayType costs) {
    std::sort(costs.begin(), costs.end(), [](const auto &one, const auto &another) {
        return (one.first - one.second) < (another.first - another.second);
    });

    const int N = costs.size() / 2;
    int result = 0;
    for (int i = 0; i < N; ++i) {
        result += costs[i].first + costs[i + N].second;
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {{10, 20}, {30, 200}, {400, 50}, {30, 20}};
const ArrayType SAMPLE2 = {{259, 770}, {448, 54}, {926, 667}, {184, 139}, {840, 118}, {577, 469}};
const ArrayType SAMPLE3 = {
    {515, 563}, {451, 713}, {537, 709}, {343, 819}, {855, 779}, {457, 60}, {650, 359}, {631, 42}};


THE_BENCHMARK(TwoCityScheduling, SAMPLE1);

SIMPLE_TEST(TwoCityScheduling, TestSAMPLE1, 110, SAMPLE1);
SIMPLE_TEST(TwoCityScheduling, TestSAMPLE2, 1859, SAMPLE2);
SIMPLE_TEST(TwoCityScheduling, TestSAMPLE3, 3086, SAMPLE3);


THE_BENCHMARK(TwoCityScheduling_SpaceO1, SAMPLE1);

SIMPLE_TEST(TwoCityScheduling_SpaceO1, TestSAMPLE1, 110, SAMPLE1);
SIMPLE_TEST(TwoCityScheduling_SpaceO1, TestSAMPLE2, 1859, SAMPLE2);
SIMPLE_TEST(TwoCityScheduling_SpaceO1, TestSAMPLE3, 3086, SAMPLE3);
