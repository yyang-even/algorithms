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

}//namespace


const ArrayType SAMPLE1 = {{1, 1}, {2, 2}, {3, 3}};
const ArrayType SAMPLE2 = {{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}, {5, 0}};


THE_BENCHMARK(MaxPointsLine, SAMPLE1);

SIMPLE_TEST(MaxPointsLine, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(MaxPointsLine, TestSAMPLE2, 5, SAMPLE2);
