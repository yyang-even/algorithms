#include "common_header.h"

#include "circle.h"


namespace {

using ArrayType = std::vector<Circle>;

/** Count Lattice Points Inside a Circle
 *
 * @reference   https://leetcode.com/problems/count-lattice-points-inside-a-circle/
 *
 * Given a 2D integer array circles where circles[i] = [xi, yi, ri] represents the center (xi, yi) and
 * radius ri of the ith circle drawn on a grid, return the number of lattice points that are present
 * inside at least one circle.
 * Note:
 *  A lattice point is a point with integer coordinates.
 *  Points that lie on the circumference of a circle are also considered to be inside it.
 * 1 <= xi, yi <= 100
 * 1 <= ri <= min(xi, yi)
 */
void CountLatticePoints(const Circle &a_circle, std::set<std::pair<int, int>> &points) {
    for (auto i = a_circle.x - a_circle.r; i <= a_circle.x + a_circle.r; ++i) {
        for (auto j = a_circle.y - a_circle.r; j <= a_circle.y + a_circle.r; ++j) {
            if (points.find({i, j}) == points.cend()) {
                if (Contains(a_circle, i, j)) {
                    points.emplace(i, j);
                }
            }
        }
    }
}

auto CountLatticePoints(const ArrayType &circles) {
    std::set<std::pair<int, int>> points;

    for (const auto &c : circles) {
        CountLatticePoints(c, points);
    }

    return points.size();
}

} //namespace


const ArrayType SAMPLE1 = {{2, 2, 1}};
const ArrayType SAMPLE2 = {{2, 2, 2}, {3, 4, 1}};


THE_BENCHMARK(CountLatticePoints, SAMPLE1);

SIMPLE_TEST(CountLatticePoints, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(CountLatticePoints, TestSAMPLE2, 16, SAMPLE2);
