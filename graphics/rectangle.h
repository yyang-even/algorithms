#pragma once

#include "point.h"


struct Rectangle {
    double left;
    double top;
    double right;
    double bottom;
};

using Square = Rectangle;

static inline auto CreateSquare(const double left, const double bottom,
                                const double size) {
    return Rectangle{left, bottom + size, left + size, bottom};
}

static inline std::ostream &operator <<(std::ostream &out, const Rectangle &s) {
    return out << "(left: " << s.left << ", top: " << s.top << ", right: " <<
           s.right << ", bottom: " << s.bottom << ")";
}


auto Middle(const Rectangle &a_square) {
    return Point{(a_square.left + a_square.right) / 2.0,
                 (a_square.top + a_square.bottom) / 2.0};
}


/** Check if a point lies on or inside a rectangle
 *
 * @reference   Check if a point lies on or inside a rectangle | Set-2
 *              https://www.geeksforgeeks.org/check-if-a-point-lies-on-or-inside-a-rectangle-set-2/
 *
 * Given coordinates of bottom-left and top-right corners of a rectangle. Check if a
 * point (x, y) lies inside this rectangle or not.
 */
static inline auto Contains(const Rectangle &a_square, const Point &a_point) {
    return a_square.left <= a_point.x and a_point.x <= a_square.right and
           a_square.bottom <= a_point.y and a_point.y <= a_square.top;
}


static inline auto isSquare(const Square &s) {
    return (s.right - s.left) == (s.top - s.bottom);
}
