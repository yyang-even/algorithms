#include "common_header.h"

#include "triangle.h"


namespace {

using ArrayType = std::vector<Point>;

/** Largest Triangle Area
 *
 * @reference   https://leetcode.com/problems/largest-triangle-area/
 *
 * Given an array of points on the X-Y plane points where points[i] = [xi, yi], return
 * the area of the largest triangle that can be formed by any three different points.
 * Answers within 10-5 of the actual answer will be accepted.
 */
auto LargestTriangleArea(const ArrayType &points) {
    double result = 0;

    for (std::size_t x = 0; x < points.size(); ++x) {
        for (std::size_t y = x + 1; y < points.size(); ++y) {
            for (std::size_t z = y + 1; z < points.size(); ++z) {
                result = std::max(result, TriangleArea(points[x], points[y], points[z]));
            }
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {{0, 0}, {0, 1}, {1, 0}, {0, 2}, {2, 0}};
const ArrayType SAMPLE2 = {{1, 0}, {0, 0}, {0, 1}};


THE_BENCHMARK(LargestTriangleArea, SAMPLE1);

SIMPLE_TEST(LargestTriangleArea, TestSAMPLE1, 2.0, SAMPLE1);
SIMPLE_TEST(LargestTriangleArea, TestSAMPLE2, 0.5, SAMPLE2);
