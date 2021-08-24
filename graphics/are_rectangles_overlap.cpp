#include "common_header.h"

#include "point.h"
#include "rectangle.h"


namespace {

using RectangleType = std::tuple<int, int, int, int>;
using RectangleArray = std::vector<RectangleType>;

/** Find if two rectangles overlap
 *
 * @reference   https://www.geeksforgeeks.org/find-two-rectangles-overlap/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 13.
 *
 * Given two rectangles, find if the given two rectangles overlap or not. It may be
 * assumed that the rectangles are parallel to the coordinate axis.
 */
inline constexpr auto
areRectanglesOverlap(const Point &top_left_1, const Point &bottom_right_1,
                     const Point &top_left_2, const Point &bottom_right_2) {
    return not(top_left_1.x > bottom_right_2.x or top_left_2.x > bottom_right_1.x or
               top_left_1.y < bottom_right_2.y or top_left_2.y < bottom_right_1.y);
}


/**
 * @reference   Rectangle Overlap
 *              https://leetcode.com/problems/rectangle-overlap/
 *
 * An axis-aligned rectangle is represented as a list [x1, y1, x2, y2], where (x1, y1) is
 * the coordinate of its bottom-left corner, and (x2, y2) is the coordinate of its
 * top-right corner. Its top and bottom edges are parallel to the X-axis, and its left
 * and right edges are parallel to the Y-axis. Two rectangles overlap if the area of
 * their intersection is positive. To be clear, two rectangles that only touch at the
 * corner or edges do not overlap. Given two axis-aligned rectangles rec1 and rec2,
 * return true if they overlap, otherwise return false.
 */
inline constexpr auto
areRectanglesOverlap_Area(const Point &bottom_left_1, const Point &top_right_1,
                          const Point &bottom_left_2, const Point &top_right_2) {
    return (std::min(top_right_1.x, top_right_2.x) >
            std::max(bottom_left_1.x, bottom_left_2.x) and
            std::min(top_right_1.y, top_right_2.y) >
            std::max(bottom_left_1.y, bottom_left_2.y));
}


/**
 * @reference   Rectangle Area
 *              https://leetcode.com/problems/rectangle-area/
 *
 * Given the coordinates of two rectilinear rectangles in a 2D plane, return the total
 * area covered by the two rectangles. The first rectangle is defined by its bottom-left
 * corner (ax1, ay1) and its top-right corner (ax2, ay2). The second rectangle is defined
 * by its bottom-left corner (bx1, by1) and its top-right corner (bx2, by2).
 */
inline constexpr int
RectangleArea(const Rectangle &one, const Rectangle &another) {
    const auto left = std::max(one.left, another.left);
    const auto bottom = std::max(one.bottom, another.bottom);
    const auto right = std::min(one.right, another.right);
    const auto top = std::min(one.top, another.top);

    const auto area = Area(one) + Area(another);
    if (right > left and top > bottom) {
        return area - Area(left, top, right, bottom);
    }
    return area;
}


/**
 * @reference   Rectangle Area II
 *              https://leetcode.com/problems/rectangle-area-ii/
 *
 * We are given a list of (axis-aligned) rectangles. Each rectangle[i] = [xi1, yi1, xi2, yi2],
 * where (xi1, yi1) are the coordinates of the bottom-left corner, and (xi2, yi2) are
 * the coordinates of the top-right corner of the ith rectangle. Find the total area
 * covered by all rectangles in the plane. Since the answer may be too large, return it
 * modulo 10^9 + 7.
 * The total area covered by all rectangles will never exceed 2^63 - 1 and thus will fit
 * in a 64-bit signed integer.
 */
int RectangleArrayArea_SweepLine(const RectangleArray &rectangles) {
    std::map<int, std::vector<std::pair<int, int>>> groups;
    for (const auto [left, bottom, right, top] : rectangles) {
        groups[left].emplace_back(bottom, 1);
        groups[left].emplace_back(top, -1);
        groups[right].emplace_back(bottom, -1);
        groups[right].emplace_back(top, 1);
    }

    std::map<int, int> counts;
    long result = 0;
    long prev_x = 0;
    long height = 0;
    for (const auto &[x, a_group] : groups) {
        result += (x - prev_x) * height;

        for (const auto [y, type] : a_group) {
            counts[y] += type;
        }

        height = 0;
        int start = 0, current = 0;
        for (const auto [y, count_opens] : counts) {
            if (current == 0) {
                start = y;
            }
            current += count_opens;
            if (current == 0) {
                height += y - start;
            }
        }

        prev_x = x;
    }

    return result % LARGE_PRIME;
}

}//namespace


constexpr Point SAMPLE_P1 = {0, 10};
constexpr Point SAMPLE_P2 = {10, 0};
constexpr Point SAMPLE_P3 = {5, 5};
constexpr Point SAMPLE_P4 = {15, 0};
constexpr Point SAMPLE_P5 = {10, 5};


THE_BENCHMARK(areRectanglesOverlap, SAMPLE_P1, SAMPLE_P2, SAMPLE_P3, SAMPLE_P4);

SIMPLE_TEST(areRectanglesOverlap, TestSAMPLE1, true,
            SAMPLE_P1, SAMPLE_P2, SAMPLE_P3, SAMPLE_P4);
SIMPLE_TEST(areRectanglesOverlap, TestSAMPLE2, false,
            SAMPLE_P1, SAMPLE_P3, SAMPLE_P5, SAMPLE_P4);


constexpr Point SAMPLE_P6 = {0, 0};
constexpr Point SAMPLE_P7 = {2, 2};
constexpr Point SAMPLE_P8 = {1, 1};
constexpr Point SAMPLE_P9 = {3, 3};
constexpr Point SAMPLE_P10 = {1, 0};
constexpr Point SAMPLE_P11 = {2, 1};


THE_BENCHMARK(areRectanglesOverlap_Area, SAMPLE_P1, SAMPLE_P2, SAMPLE_P3, SAMPLE_P4);

SIMPLE_TEST(areRectanglesOverlap_Area, TestSAMPLE1, true,
            SAMPLE_P6, SAMPLE_P7, SAMPLE_P8, SAMPLE_P9);
SIMPLE_TEST(areRectanglesOverlap_Area, TestSAMPLE2, false,
            SAMPLE_P6, SAMPLE_P8, SAMPLE_P10, SAMPLE_P11);
SIMPLE_TEST(areRectanglesOverlap_Area, TestSAMPLE3, false,
            SAMPLE_P6, SAMPLE_P8, SAMPLE_P7, SAMPLE_P9);


constexpr Rectangle SAMPLE_R1 = {-3, 4, 3, 0};
constexpr Rectangle SAMPLE_R2 = {0, 2, 9, -1};
constexpr Rectangle SAMPLE_R3 = {-2, 2, 2, -2};


THE_BENCHMARK(RectangleArea, SAMPLE_R1, SAMPLE_R2);

SIMPLE_TEST(RectangleArea, TestSAMPLE1, 45, SAMPLE_R1, SAMPLE_R2);
SIMPLE_TEST(RectangleArea, TestSAMPLE2, 16, SAMPLE_R3, SAMPLE_R3);


const RectangleArray SAMPLE1 = {
    {0, 0, 2, 2},
    {1, 0, 2, 3},
    {1, 0, 3, 1}
};

const RectangleArray SAMPLE2 = {
    {0, 0, 1000000000, 1000000000}
};


THE_BENCHMARK(RectangleArrayArea_SweepLine, SAMPLE1);

SIMPLE_TEST(RectangleArrayArea_SweepLine, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(RectangleArrayArea_SweepLine, TestSAMPLE2, 49, SAMPLE2);
