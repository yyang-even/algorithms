#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Two Furthest Houses With Different Colors
 *
 * @reference   https://leetcode.com/problems/two-furthest-houses-with-different-colors/
 *
 * There are n houses evenly lined up on the street, and each house is beautifully painted.
 * You are given a 0-indexed integer array colors of length n, where colors[i] represents
 * the color of the ith house.
 * Return the maximum distance between two houses with different colors.
 * The distance between the ith and jth houses is abs(i - j), where abs(x) is the absolute
 * value of x.
 * Test data are generated such that at least two houses have different colors.
 */
auto FurthestHousesWithDiffColors(const ArrayType &colors) {
    std::size_t i = colors.size() - 1;
    while (colors[i] == colors.front()) {
        --i;
    }

    std::size_t j = 0;
    while (colors[j] == colors.back()) {
        ++j;
    }

    return std::max(i, colors.size() - 1 - j);
}

}//namespace


const ArrayType SAMPLE1 = {1, 1, 1, 6, 1, 1, 1};
const ArrayType SAMPLE2 = {1, 8, 3, 8, 3};
const ArrayType SAMPLE3 = {0, 1};


THE_BENCHMARK(FurthestHousesWithDiffColors, SAMPLE1);

SIMPLE_TEST(FurthestHousesWithDiffColors, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(FurthestHousesWithDiffColors, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(FurthestHousesWithDiffColors, TestSAMPLE3, 1, SAMPLE3);
