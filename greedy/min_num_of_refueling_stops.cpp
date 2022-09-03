#include "common_header.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

/** Minimum Number of Refueling Stops
 *
 * @reference   https://leetcode.com/problems/minimum-number-of-refueling-stops/
 *
 * A car travels from a starting position to a destination which is target miles east of the starting
 * position.
 * There are gas stations along the way. The gas stations are represented as an array stations where
 * stations[i] = [positioni, fueli] indicates that the ith gas station is positioni miles east of the
 * starting position and has fueli liters of gas.
 * The car starts with an infinite tank of gas, which initially has startFuel liters of fuel in it. It
 * uses one liter of gas per one mile that it drives. When the car reaches a gas station, it may stop
 * and refuel, transferring all the gas from the station into the car.
 * Return the minimum number of refueling stops the car must make in order to reach its destination. If
 * it cannot reach the destination, return -1.
 * Note that if the car reaches a gas station with 0 fuel left, the car can still refuel there. If the
 * car reaches the destination with 0 fuel left, it is still considered to have arrived.
 */
int MinNumOfRefuelingStops_DP(const int target, const int start_fuel, const ArrayType &stations) {
    long dp[stations.size() + 1] = {start_fuel};

    for (std::size_t i = 0; i < stations.size(); ++i) {
        for (int t = i; t >= 0; --t) {
            if (dp[t] >= stations[i].first) {
                dp[t + 1] = std::max(dp[t + 1], dp[t] + stations[i].second);
            }
        }
    }

    for (std::size_t i = 0; i <= stations.size(); ++i) {
        if (dp[i] >= target) {
            return i;
        }
    }

    return -1;
}


auto MinNumOfRefuelingStops_OneGreedy(const int target, int tank, const ArrayType &stations) {
    int result = 0;
    int prev = 0;
    std::priority_queue<int> max_heap;

    for (const auto &[location, capacity] : stations) {
        tank -= location - prev;
        while (not max_heap.empty() and tank < 0) {
            tank += max_heap.top();
            max_heap.pop();
            ++result;
        }
        if (tank < 0) {
            return -1;
        }

        max_heap.push(capacity);
        prev = location;
    }

    tank -= target - prev;
    while (not max_heap.empty() and tank < 0) {
        tank += max_heap.top();
        max_heap.pop();
        ++result;
    }
    if (tank < 0) {
        return -1;
    }

    return result;
}


auto MinNumOfRefuelingStops(const int target, const int start_fuel, const ArrayType &stations) {
    int result = 0;
    std::priority_queue<int> max_heap;
    std::size_t i = 0;

    for (auto reach = start_fuel; reach < target;) {
        for (; i < stations.size() and reach >= stations[i].first; ++i) {
            max_heap.push(stations[i].second);
        }

        if (max_heap.empty()) {
            return -1;
        }

        reach += max_heap.top();
        ++result;
        max_heap.pop();
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {};
const ArrayType SAMPLE2 = {{10, 100}};
const ArrayType SAMPLE3 = {{10, 60}, {20, 30}, {30, 30}, {60, 40}};
const ArrayType SAMPLE4 = {{13, 21},
                           {26, 115},
                           {100, 47},
                           {225, 99},
                           {299, 141},
                           {444, 198},
                           {608, 190},
                           {636, 157},
                           {647, 255},
                           {841, 123}};


THE_BENCHMARK(MinNumOfRefuelingStops_DP, 1000, 299, SAMPLE4);

SIMPLE_TEST(MinNumOfRefuelingStops_DP, TestSAMPLE1, 0, 1, 1, SAMPLE1);
SIMPLE_TEST(MinNumOfRefuelingStops_DP, TestSAMPLE2, -1, 100, 1, SAMPLE2);
SIMPLE_TEST(MinNumOfRefuelingStops_DP, TestSAMPLE3, 2, 100, 10, SAMPLE3);
SIMPLE_TEST(MinNumOfRefuelingStops_DP, TestSAMPLE4, 4, 1000, 299, SAMPLE4);


THE_BENCHMARK(MinNumOfRefuelingStops_OneGreedy, 1000, 299, SAMPLE4);

SIMPLE_TEST(MinNumOfRefuelingStops_OneGreedy, TestSAMPLE1, 0, 1, 1, SAMPLE1);
SIMPLE_TEST(MinNumOfRefuelingStops_OneGreedy, TestSAMPLE2, -1, 100, 1, SAMPLE2);
SIMPLE_TEST(MinNumOfRefuelingStops_OneGreedy, TestSAMPLE3, 2, 100, 10, SAMPLE3);
SIMPLE_TEST(MinNumOfRefuelingStops_OneGreedy, TestSAMPLE4, 4, 1000, 299, SAMPLE4);


THE_BENCHMARK(MinNumOfRefuelingStops, 1000, 299, SAMPLE4);

SIMPLE_TEST(MinNumOfRefuelingStops, TestSAMPLE1, 0, 1, 1, SAMPLE1);
SIMPLE_TEST(MinNumOfRefuelingStops, TestSAMPLE2, -1, 100, 1, SAMPLE2);
SIMPLE_TEST(MinNumOfRefuelingStops, TestSAMPLE3, 2, 100, 10, SAMPLE3);
SIMPLE_TEST(MinNumOfRefuelingStops, TestSAMPLE4, 4, 1000, 299, SAMPLE4);
