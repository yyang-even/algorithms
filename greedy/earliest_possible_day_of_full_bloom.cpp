#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Earliest Possible Day of Full Bloom
 *
 * @reference   https://leetcode.com/problems/earliest-possible-day-of-full-bloom/
 *
 * You have n flower seeds. Every seed must be planted first before it can begin to grow, then bloom.
 * Planting a seed takes time and so does the growth of a seed. You are given two 0-indexed integer
 * arrays plantTime and growTime, of length n each:
 *  plantTime[i] is the number of full days it takes you to plant the ith seed. Every day, you can work
 *      on planting exactly one seed. You do not have to work on planting the same seed on consecutive
 *      days, but the planting of a seed is not complete until you have worked plantTime[i] days on
 *      planting it in total.
 *  growTime[i] is the number of full days it takes the ith seed to grow after being completely planted.
 *      After the last day of its growth, the flower blooms and stays bloomed forever.
 * From the beginning of day 0, you can plant the seeds in any order.
 * Return the earliest possible day where all seeds are blooming.
 */
auto EarliestPossibleDayOfFullBloom(const ArrayType &plantTime, const ArrayType &growTime) {
    ArrayType indices(plantTime.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(), [&growTime](const auto lhs, const auto rhs) {
        return growTime[lhs] > growTime[rhs];
    });

    int result = 0;
    int current_plant_time = 0;
    for (const auto i : indices) {
        current_plant_time += plantTime[i];
        result = std::max(result, current_plant_time + growTime[i]);
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1P = {1, 4, 3};
const ArrayType SAMPLE1G = {2, 3, 1};

const ArrayType SAMPLE2P = {1, 2, 3, 2};
const ArrayType SAMPLE2G = {2, 1, 2, 1};

const ArrayType SAMPLE3 = {1};


THE_BENCHMARK(EarliestPossibleDayOfFullBloom, SAMPLE1P, SAMPLE1G);

SIMPLE_TEST(EarliestPossibleDayOfFullBloom, TestSAMPLE1, 9, SAMPLE1P, SAMPLE1G);
SIMPLE_TEST(EarliestPossibleDayOfFullBloom, TestSAMPLE2, 9, SAMPLE2P, SAMPLE2G);
SIMPLE_TEST(EarliestPossibleDayOfFullBloom, TestSAMPLE3, 2, SAMPLE3, SAMPLE3);
