#include "common_header.h"


namespace {

using ArrayType = std::vector<std::vector<int>>;

/**
 * @reference   Count Number of Trapezoids I
 *              https://leetcode.com/problems/count-number-of-trapezoids-i/
 *
 * You are given a 2D integer array points, where points[i] = [xi, yi] represents the coordinates of the
 * ith point on the Cartesian plane.
 * A horizontal trapezoid is a convex quadrilateral with at least one pair of horizontal sides (i.e.
 * parallel to the x-axis). Two lines are parallel if and only if they have the same slope.
 * Return the number of unique horizontal trapezoids that can be formed by choosing any four distinct
 * points from points.
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * @tags    #geometry #hash-table
 */
auto CountNumberOfHorizontalTrapezoids(const ArrayType &points) {
    std::unordered_map<int, int> counts;
    for (const auto &p : points) {
        ++counts[p[1]];
    }

    unsigned long long sum = 0;
    unsigned long long result = 0;
    for (const auto &[y, c] : counts) {
        const auto num_edges = c * (c - 1ull) / 2;
        result += num_edges * sum;
        sum += num_edges;
    }

    return result % LARGE_PRIME;
}

} //namespace


const ArrayType SAMPLE1 = {{1, 0}, {2, 0}, {3, 0}, {2, 2}, {3, 2}};
const ArrayType SAMPLE2 = {{0, 0}, {1, 0}, {0, 1}, {2, 1}};


THE_BENCHMARK(CountNumberOfHorizontalTrapezoids, SAMPLE1);

SIMPLE_TEST(CountNumberOfHorizontalTrapezoids, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(CountNumberOfHorizontalTrapezoids, TestSAMPLE2, 1, SAMPLE2);
