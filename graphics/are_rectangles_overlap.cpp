#include "common_header.h"

#include "graphics.h"


namespace {

/** Find if two rectangles overlap
 *
 * @reference   https://www.geeksforgeeks.org/find-two-rectangles-overlap/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 13.
 *
 * Given two rectangles, find if the given two rectangles overlap or not.
 * It may be assumed that the rectangles are parallel to the coordinate axis.
 */
auto areRectanglesOverlap(const Point &top_left_1, const Point &bottom_right_1,
                          const Point &top_left_2, const Point &bottom_right_2) {
    return top_left_1.x <= bottom_right_2.x and top_left_2.x <= bottom_right_1.x and
           top_left_1.y >= bottom_right_2.y and top_left_2.y >= bottom_right_1.y;
}

}//namespace


const Point SAMPLE_P1 = {0, 10};
const Point SAMPLE_P2 = {10, 0};
const Point SAMPLE_P3 = {5, 5};
const Point SAMPLE_P4 = {15, 0};
const Point SAMPLE_P5 = {10, 5};


THE_BENCHMARK(areRectanglesOverlap, SAMPLE_P1, SAMPLE_P2, SAMPLE_P3, SAMPLE_P4);

SIMPLE_TEST(areRectanglesOverlap, TestSAMPLE1, true, SAMPLE_P1, SAMPLE_P2, SAMPLE_P3,
            SAMPLE_P4);
SIMPLE_TEST(areRectanglesOverlap, TestSAMPLE2, false, SAMPLE_P1, SAMPLE_P3, SAMPLE_P5,
            SAMPLE_P4);
