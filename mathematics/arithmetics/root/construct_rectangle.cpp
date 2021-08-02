#include "common_header.h"


namespace {

/** Construct the Rectangle
 *
 * @reference   https://leetcode.com/problems/construct-the-rectangle/
 *
 * A web developer needs to know how to design a web page's size. So, given a specific
 * rectangular web page's area, your job by now is to design a rectangular web page,
 * whose length L and width W satisfy the following requirements:
 *  The area of the rectangular web page you designed must equal to the given target area.
 *  The width W should not be larger than the length L, which means L >= W.
 *  The difference between length L and width W should be as small as possible.
 * Return an array [L, W] where L and W are the length and width of the web page you
 * designed in sequence.
 */
auto ConstructRectangle(const int area) {
    for (int w = sqrt(area); w > 0; --w) {
        if (area % w == 0)
            return std::pair{area / w, w};
    }

    return std::pair{-1, -1};
}

}//namespace


const auto EXPECTED1 = std::pair(2, 2);
const auto EXPECTED2 = std::pair(37, 1);
const auto EXPECTED3 = std::pair(427, 286);

THE_BENCHMARK(ConstructRectangle, 122122);

SIMPLE_TEST(ConstructRectangle, TestSAMPLE1, EXPECTED1, 4);
SIMPLE_TEST(ConstructRectangle, TestSAMPLE2, EXPECTED2, 37);
SIMPLE_TEST(ConstructRectangle, TestSAMPLE3, EXPECTED3, 122122);
