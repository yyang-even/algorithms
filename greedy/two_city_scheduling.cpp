#include "common_header.h"


namespace {

using PairArray = std::vector<std::pair<int, int>>;
using ArrayType = std::vector<int>;

/** Two City Scheduling
 *
 * @reference   https://leetcode.com/problems/two-city-scheduling/
 *
 * A company is planning to interview 2n people. Given the array costs where costs[i] = [aCosti,
 * bCosti], the cost of flying the ith person to city a is aCosti, and the cost of flying the ith person
 * to city b is bCosti.
 * Return the minimum cost to fly every person to a city such that exactly n people arrive in each city.
 */
auto TwoCityScheduling(const PairArray &costs) {
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


auto TwoCityScheduling_SpaceO1(PairArray costs) {
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


/**
 * @reference   Maximum Bags With Full Capacity of Rocks
 *              https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/
 *
 * You have n bags numbered from 0 to n - 1. You are given two 0-indexed integer arrays capacity and
 * rocks. The ith bag can hold a maximum of capacity[i] rocks and currently contains rocks[i] rocks. You
 * are also given an integer additionalRocks, the number of additional rocks you can place in any of the
 * bags.
 * Return the maximum number of bags that could have full capacity after placing the additional rocks in
 * some bags.
 */
auto MaximumBags(const ArrayType &capacity, const ArrayType &rocks, int additionalRocks) {
    ArrayType diffs;
    for (std::size_t i = 0; i < rocks.size(); ++i) {
        diffs.push_back(capacity[i] - rocks[i]);
    }

    std::sort(diffs.begin(), diffs.end());

    std::size_t i = 0;
    for (i = 0; i < diffs.size() and additionalRocks >= diffs[i]; ++i) {
        additionalRocks -= diffs[i];
    }

    return i;
}

} //namespace


const PairArray SAMPLE1 = {{10, 20}, {30, 200}, {400, 50}, {30, 20}};
const PairArray SAMPLE2 = {{259, 770}, {448, 54}, {926, 667}, {184, 139}, {840, 118}, {577, 469}};
const PairArray SAMPLE3 = {
    {515, 563}, {451, 713}, {537, 709}, {343, 819}, {855, 779}, {457, 60}, {650, 359}, {631, 42}};


THE_BENCHMARK(TwoCityScheduling, SAMPLE1);

SIMPLE_TEST(TwoCityScheduling, TestSAMPLE1, 110, SAMPLE1);
SIMPLE_TEST(TwoCityScheduling, TestSAMPLE2, 1859, SAMPLE2);
SIMPLE_TEST(TwoCityScheduling, TestSAMPLE3, 3086, SAMPLE3);


THE_BENCHMARK(TwoCityScheduling_SpaceO1, SAMPLE1);

SIMPLE_TEST(TwoCityScheduling_SpaceO1, TestSAMPLE1, 110, SAMPLE1);
SIMPLE_TEST(TwoCityScheduling_SpaceO1, TestSAMPLE2, 1859, SAMPLE2);
SIMPLE_TEST(TwoCityScheduling_SpaceO1, TestSAMPLE3, 3086, SAMPLE3);


const ArrayType SAMPLE1C = {2, 3, 4, 5};
const ArrayType SAMPLE1R = {1, 2, 4, 4};

const ArrayType SAMPLE2C = {10, 2, 2};
const ArrayType SAMPLE2R = {2, 2, 0};

const ArrayType SAMPLE3C = {91, 54, 63, 99, 24, 45, 78};
const ArrayType SAMPLE3R = {35, 32, 45, 98, 6, 1, 25};


THE_BENCHMARK(MaximumBags, SAMPLE1C, SAMPLE1R, 2);

SIMPLE_TEST(MaximumBags, TestSAMPLE1, 3, SAMPLE1C, SAMPLE1R, 2);
SIMPLE_TEST(MaximumBags, TestSAMPLE2, 3, SAMPLE2C, SAMPLE2R, 100);
SIMPLE_TEST(MaximumBags, TestSAMPLE3, 1, SAMPLE3C, SAMPLE3R, 17);
