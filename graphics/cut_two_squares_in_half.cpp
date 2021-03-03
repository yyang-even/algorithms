#include "common_header.h"

#include "line.h"
#include "rectangle.h"


namespace {

/** Cut two squares in half with one line
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 7.3.
 *
 * Given two squares on a two-dimensional plane, find a line that would cut these two
 * squares in half. Assume that the top and the bottom sides of the square run parallel
 * to the x-axis.
 */
auto IntersectPoints(const Point &a_middle, const Square &a_square,
                     const Point &another_middle) {
    assert(Contains(a_square, a_middle));
    assert(isSquare(a_square));

    if (a_middle.x == another_middle.x)
        return std::make_pair(Point{a_middle.x, a_square.top}, Point{a_middle.x, a_square.bottom});

    const auto abs_slope = std::abs(Slope(a_middle, another_middle));

    if (abs_slope == 1) {
        return std::make_pair(Point{a_square.left, a_square.bottom}, Point{a_square.right, a_square.top});
    } else if (abs_slope < 1) {
        const auto diff = abs_slope * (a_square.right - a_square.left) / 2.0;
        return std::make_pair(Point{a_square.left, a_middle.y - diff}, Point{a_square.right, a_middle.y + diff});
    } else {
        const auto diff = (a_square.top - a_square.bottom) / 2 / abs_slope;
        return std::make_pair(Point{a_middle.x - diff, a_square.bottom}, Point{a_middle.x + diff, a_square.top});
    }
}

auto CutTwoSquaresWithOneLine(const Square &a_square, const Square &another_square) {
    const auto a_middle = Middle(a_square);
    const auto another_middle = Middle(another_square);

    const auto an_intersect_points_pair =
        IntersectPoints(a_middle, a_square, another_middle);
    const auto another_intersect_points_pair =
        IntersectPoints(another_middle, another_square, a_middle);

    const Point *start = &(an_intersect_points_pair.first);
    const auto *end = start;
    const std::vector<const Point *> points = {&(an_intersect_points_pair.second),
                                               &(another_intersect_points_pair.first),
                                               &(another_intersect_points_pair.second)
                                              };

    for (const auto *a_point : points) {
        if (a_point->x < start->x or (a_point->x == start->x and a_point->y < start->y)) {
            start = a_point;
        } else if (a_point->x > end->x or (a_point->x == end->x and a_point->y > end->y)) {
            end = a_point;
        }
    }

    return LineSegment{*start, *end};
}

}//namespace


const auto SAMPLE1 = CreateSquare(0, 0, 2);
const LineSegment EXPECTED1 = {{1, 0}, {1, 2}};
const auto SAMPLE2 = CreateSquare(0, -1, 2);
const LineSegment EXPECTED2 = {{1, -1}, {1, 2}};
const auto SAMPLE3 = CreateSquare(2, 2, 2);
const LineSegment EXPECTED3 = {{0, 0}, {4, 4}};
const auto SAMPLE4 = CreateSquare(0, 0, 8);
const auto SAMPLE5 = CreateSquare(6, 4, 4);
const LineSegment EXPECTED4 = {{0, 2}, {10, 7}};
const auto SAMPLE6 = CreateSquare(4, 6, 4);
const LineSegment EXPECTED5 = {{2, 0}, {7, 10}};


THE_BENCHMARK(CutTwoSquaresWithOneLine, SAMPLE1, SAMPLE1);

SIMPLE_TEST(CutTwoSquaresWithOneLine, TestSAMPLE1, EXPECTED1, SAMPLE1, SAMPLE1);
SIMPLE_TEST(CutTwoSquaresWithOneLine, TestSAMPLE2, EXPECTED2, SAMPLE1, SAMPLE2);
SIMPLE_TEST(CutTwoSquaresWithOneLine, TestSAMPLE3, EXPECTED2, SAMPLE2, SAMPLE1);
SIMPLE_TEST(CutTwoSquaresWithOneLine, TestSAMPLE4, EXPECTED3, SAMPLE1, SAMPLE3);
SIMPLE_TEST(CutTwoSquaresWithOneLine, TestSAMPLE5, EXPECTED3, SAMPLE3, SAMPLE1);
SIMPLE_TEST(CutTwoSquaresWithOneLine, TestSAMPLE6, EXPECTED4, SAMPLE4, SAMPLE5);
SIMPLE_TEST(CutTwoSquaresWithOneLine, TestSAMPLE7, EXPECTED4, SAMPLE5, SAMPLE4);
SIMPLE_TEST(CutTwoSquaresWithOneLine, TestSAMPLE8, EXPECTED5, SAMPLE4, SAMPLE6);
SIMPLE_TEST(CutTwoSquaresWithOneLine, TestSAMPLE9, EXPECTED5, SAMPLE6, SAMPLE4);
