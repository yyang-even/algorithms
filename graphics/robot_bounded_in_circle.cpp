#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

/** Robot Bounded In Circle
 *
 * @reference   https://leetcode.com/problems/robot-bounded-in-circle/
 *
 * On an infinite plane, a robot initially stands at (0, 0) and faces north. The robot can
 * receive one of three instructions:
 *  "G": go straight 1 unit;
 *  "L": turn 90 degrees to the left;
 *  "R": turn 90 degrees to the right.
 * The robot performs the instructions given in order, and repeats them forever. Return
 * true if and only if there exists a circle in the plane such that the robot never leaves
 * the circle.
 */
auto BoundedInCircle(const std::string_view instructions) {
    const auto init_direction = 2;

    int x = 0;
    int y = 0;
    int d = init_direction;
    for (const auto i : instructions) {
        if (i == 'R') {
            d = (d + 1) % 4;
        } else if (i == 'L') {
            d = (d + 3) % 4;
        } else {
            const auto [delta_x, delta_y] = DIRECTIONS[d];
            x += delta_x;
            y += delta_y;
        }
    }

    return (x == 0 and y == 0) or d != init_direction;
}

}//namespace


THE_BENCHMARK(BoundedInCircle, "GGLLGG");

SIMPLE_TEST(BoundedInCircle, TestSAMPLE1, true, "GGLLGG");
SIMPLE_TEST(BoundedInCircle, TestSAMPLE2, false, "GG");
SIMPLE_TEST(BoundedInCircle, TestSAMPLE3, true, "GL");
SIMPLE_TEST(BoundedInCircle, TestSAMPLE4, false, "GGRGRGGGRR");
