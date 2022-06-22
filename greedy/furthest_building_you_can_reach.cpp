#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Furthest Building You Can Reach
 *
 * @reference   https://leetcode.com/problems/furthest-building-you-can-reach/
 *
 * You are given an integer array heights representing the heights of buildings, some bricks, and
 * some ladders.
 * You start your journey from building 0 and move to the next building by possibly using bricks
 * or ladders.
 * While moving from building i to building i+1 (0-indexed),
 *  If the current building's height is greater than or equal to the next building's height, you
 *      do not need a ladder or bricks.
 *  If the current building's height is less than the next building's height, you can either use
 *      one ladder or (h[i+1] - h[i]) bricks.
 * Return the furthest building index (0-indexed) you can reach if you use the given ladders and
 * bricks optimally.
 */
auto FurthestBuildingCanReach(const ArrayType &heights, int bricks, const std::size_t ladders) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

    for (std::size_t i = 0; i < heights.size() - 1; ++i) {
        const auto diff = heights[i + 1] - heights[i];

        if (diff > 0) {
            min_heap.push(diff);
        }

        if (min_heap.size() > ladders) {
            bricks -= min_heap.top();
            min_heap.pop();
        }

        if (bricks < 0) {
            return i;
        }
    }

    return heights.size() - 1;
}

} //namespace


const ArrayType SAMPLE1 = {4, 2, 7, 6, 9, 14, 12};
const ArrayType SAMPLE2 = {4, 12, 2, 7, 3, 18, 20, 3, 19};
const ArrayType SAMPLE3 = {14, 3, 19, 3};


THE_BENCHMARK(FurthestBuildingCanReach, SAMPLE1, 5, 1);

SIMPLE_TEST(FurthestBuildingCanReach, TestSAMPLE1, 4, SAMPLE1, 5, 1);
SIMPLE_TEST(FurthestBuildingCanReach, TestSAMPLE2, 7, SAMPLE2, 10, 2);
SIMPLE_TEST(FurthestBuildingCanReach, TestSAMPLE3, 3, SAMPLE3, 17, 0);
