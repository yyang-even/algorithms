#include "common_header.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

inline void
draw_circle_pixel(ArrayType &results, const int x_centre, const int y_centre,
                  const int x, const int y) {
    results.emplace_back(x_centre + x, y_centre + y);
}

/** Mid-Point Circle Drawing Algorithm
 *
 * @reference   https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
 * @reference   Draw a circle without floating point arithmetic
 *              https://www.geeksforgeeks.org/draw-circle-without-floating-point-arithmetic/
 */
auto DrawCircle_MidPoint(const int x_centre, const int y_centre, const int radius) {
    int x = 0;
    int y = radius;

    ArrayType results;
    for (auto p = 1 - radius; y >= x;) {
        draw_circle_pixel(results, x_centre, y_centre, x++, y);

        if (p <= 0) {
            p += 2 * x + 1;
        } else {
            p += 2 * x - 2 * --y + 1;
        }
    }

    return results;
}


/**
 * @reference   Bresenham’s circle drawing algorithm
 *              https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
 */
auto DrawCircle_Bresenham(const int x_centre, const int y_centre, const int radius) {
    int x = 0;
    int y = radius;

    ArrayType results;
    for (auto d = 3 - 2 * radius; y >= x;) {
        draw_circle_pixel(results, x_centre, y_centre, x++, y);

        if (d > 0) {
            d += 4 * (x - --y) + 10;
        } else {
            d += 4 * x + 6;
        }
    }

    return results;
}


/** Eighth of a Circle
 *
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 13.
 */
auto DrawCircle_SQRT(const int x_centre, const int y_centre, const int radius) {
    double x = 0;
    double y = radius;

    ArrayType results;
    for (; y >= x; ++x) {
        y = std::sqrt(radius * radius - x * x);
        draw_circle_pixel(results, x_centre, y_centre, x + 0.5, y + 0.5);
    }

    return results;
}

}//namespace


const ArrayType EXPECTED1 = {{0, 3}, {1, 3}, {2, 2}};
const ArrayType EXPECTED2 = {{4, 6}, {5, 6}};


THE_BENCHMARK(DrawCircle_MidPoint, 0, 0, 3);

SIMPLE_TEST(DrawCircle_MidPoint, TestSAMPLE1, EXPECTED1, 0, 0, 3);
SIMPLE_TEST(DrawCircle_MidPoint, TestSAMPLE2, EXPECTED2, 4, 4, 2);


THE_BENCHMARK(DrawCircle_Bresenham, 0, 0, 3);

SIMPLE_TEST(DrawCircle_Bresenham, TestSAMPLE1, EXPECTED1, 0, 0, 3);
SIMPLE_TEST(DrawCircle_Bresenham, TestSAMPLE2, EXPECTED2, 4, 4, 2);


THE_BENCHMARK(DrawCircle_SQRT, 0, 0, 3);

SIMPLE_TEST(DrawCircle_SQRT, TestSAMPLE1, EXPECTED1, 0, 0, 3);
SIMPLE_TEST(DrawCircle_SQRT, TestSAMPLE2, EXPECTED2, 4, 4, 2);
