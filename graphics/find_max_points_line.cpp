#include "common_header.h"

#include "line.h"


namespace {

using ArrayType = std::vector<Point>;

/** Max Points on a Line
 *
 * @reference   https://leetcode.com/problems/max-points-on-a-line/
 *
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y
 * plane, return the maximum number of points that lie on the same straight line.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 7.6.
 *
 * Given a two-dimensional graph with points on it, find a line which passes the most
 * number of points.
 */
int MaxPointsLine(const ArrayType &points) {
    if (points.size() < 3) {
        return points.size();
    }

    int best_count = 0;
    for (auto outer_iter = points.cbegin(); outer_iter != points.cend(); ++outer_iter) {
        std::unordered_map<Line, int, LineHashType> line_points_map;
        int current_best = 0;
        for (auto inner_iter = std::next(outer_iter);
             inner_iter != points.cend();
             ++inner_iter) {
            const auto a_line = Line(*outer_iter, *inner_iter);
            const auto new_count = ++(line_points_map[a_line]);
            if (new_count > current_best) {
                current_best = new_count;
            }
        }

        if (current_best > best_count) {
            best_count = current_best;
        }
    }

    return best_count + 1;
}


/**
 * @reference   Check If It Is a Straight Line
 *              https://leetcode.com/problems/check-if-it-is-a-straight-line/
 *
 * You are given an array coordinates, coordinates[i] = [x, y], where [x, y] represents
 * the coordinate of a point. Check if these points make a straight line in the XY plane.
 * coordinates contains no duplicate point.
 */
inline constexpr auto
isCollinear(const Point &p1, const Point &p2, const Point &p3) {
    return (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) == 0;
}

auto isStraightLine(const ArrayType &points) {
    for (std::size_t i = 2; i < points.size(); ++i) {
        if (not isCollinear(points.front(), points[i - 1], points[i])) {
            return false;
        }
    }

    return true;
}


auto isStraightLine_Another(const ArrayType &points) {
    const auto &p0 = points[0];
    const int dY = points[1].y - p0.y;
    const int dX = points[1].x - p0.x;
    for (std::size_t i = 2; i < points.size(); ++i) {
        const auto &p = points[i];
        if (dX * (p.y - p0.y) != dY * (p.x - p0.x)) {
            return false;
        }
    }

    return true;
}

}//namespace


const ArrayType SAMPLE1 = {{1, 1}, {2, 2}, {3, 3}};
const ArrayType SAMPLE2 = {{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}, {5, 0}};


THE_BENCHMARK(MaxPointsLine, SAMPLE1);

SIMPLE_TEST(MaxPointsLine, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(MaxPointsLine, TestSAMPLE2, 5, SAMPLE2);


const ArrayType SAMPLE3 = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};
const ArrayType SAMPLE4 = {{1, 1}, {2, 2}, {3, 4}, {4, 5}, {5, 6}, {7, 7}};


THE_BENCHMARK(isStraightLine, SAMPLE1);

SIMPLE_TEST(isStraightLine, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isStraightLine, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(isStraightLine, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(isStraightLine, TestSAMPLE4, false, SAMPLE4);


THE_BENCHMARK(isStraightLine_Another, SAMPLE1);

SIMPLE_TEST(isStraightLine_Another, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isStraightLine_Another, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(isStraightLine_Another, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(isStraightLine_Another, TestSAMPLE4, false, SAMPLE4);
