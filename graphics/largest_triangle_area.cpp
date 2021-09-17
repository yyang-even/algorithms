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


/**
 * @reference   Valid Boomerang
 *              https://leetcode.com/problems/valid-boomerang/
 *
 * Given an array points where points[i] = [xi, yi] represents a point on the X-Y plane,
 * return true if these points are a boomerang. A boomerang is a set of three points
 * that are all distinct and not in a straight line.
 */
inline bool isBoomerang(const ArrayType &points) {
    assert(points.size() == 3);
    return TriangleArea(points[0], points[1], points[2]);
}

}//namespace


const ArrayType SAMPLE1 = {{0, 0}, {0, 1}, {1, 0}, {0, 2}, {2, 0}};
const ArrayType SAMPLE2 = {{1, 0}, {0, 0}, {0, 1}};


THE_BENCHMARK(LargestTriangleArea, SAMPLE1);

SIMPLE_TEST(LargestTriangleArea, TestSAMPLE1, 2.0, SAMPLE1);
SIMPLE_TEST(LargestTriangleArea, TestSAMPLE2, 0.5, SAMPLE2);


const ArrayType SAMPLE3 = {{1, 1}, {2, 3}, {3, 2}};
const ArrayType SAMPLE4 = {{1, 1}, {2, 2}, {3, 3}};


THE_BENCHMARK(isBoomerang, SAMPLE3);

SIMPLE_TEST(isBoomerang, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isBoomerang, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(isBoomerang, TestSAMPLE4, false, SAMPLE4);
