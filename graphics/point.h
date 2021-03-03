#pragma once


struct Point {
    double x;
    double y;
};

static inline std::ostream &operator <<(std::ostream &out, const Point &p) {
    return out << "(" << p.x << ", " << p.y << ")";
}

static inline auto operator==(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x and lhs.y == rhs.y;
}


/** Program to find slope of a line
 *
 * @reference   https://www.geeksforgeeks.org/program-find-slope-line/
 *
 * Given two co-ordinates, find the slope of a straight line.
 */
static inline auto Slope(const Point &a_point, const Point &another_point) {
    assert(a_point.x != another_point.x);

    return (another_point.y - a_point.y) / (another_point.x - a_point.x);
}
