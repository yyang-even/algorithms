#pragma once

#include "point.h"


struct Line {
    double slope;
    double y_intercept;
};

static inline auto &operator<<(std::ostream &out, const Line &a_line) {
    return out << "(" << a_line.slope << ", " << a_line.y_intercept << ")";
}


struct LineSegment {
    Point a;
    Point b;
};

static inline auto &operator<<(std::ostream &out, const LineSegment &a_line) {
    return out << "(" << a_line.a << " -> " << a_line.b << ")";
}

static inline auto operator==(const LineSegment &lhs, const LineSegment &rhs) {
    return lhs.a == rhs.a and lhs.b == rhs.b;
}
