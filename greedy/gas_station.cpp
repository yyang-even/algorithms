#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Gas Station
 *
 * @reference   https://leetcode.com/problems/gas-station/
 *
 * There are n gas stations along a circular route, where the amount of gas at the ith
 * station is gas[i].
 * You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from
 * the ith station to its next (i + 1)th station. You begin the journey with an empty
 * tank at one of the gas stations.
 * Given two integer arrays gas and cost, return the starting gas station's index if you
 * can travel around the circuit once in the clockwise direction, otherwise return -1. If
 * there exists a solution, it is guaranteed to be unique.
 */
auto GasStation(const ArrayType &gas, const ArrayType &cost) {
    int tank = 0;
    int total = 0;
    int result = -1;
    for (std::size_t i = 0; i < gas.size(); ++i) {
        const auto delta = gas[i] - cost[i];
        tank += delta;
        total += delta;
        if (tank < 0) {
            result = i + 1;
            tank = 0;
        }
    }

    return total < 0 ? -1 : result;
}

}//namespace


const ArrayType SAMPLE1G = {1, 2, 3, 4, 5};
const ArrayType SAMPLE1C = {3, 4, 5, 1, 2};

const ArrayType SAMPLE2G = {2, 3, 4};
const ArrayType SAMPLE2C = {3, 4, 3};


THE_BENCHMARK(GasStation, SAMPLE1G, SAMPLE1C);

SIMPLE_TEST(GasStation, TestSAMPLE1, 3, SAMPLE1G, SAMPLE1C);
SIMPLE_TEST(GasStation, TestSAMPLE2, -1, SAMPLE2G, SAMPLE2C);
