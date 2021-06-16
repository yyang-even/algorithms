#pragma once

#include "point.h"


struct Line {
    double slope = 0.0;
    double intercept = 0.0;
    bool infinite_slope = false;

    constexpr Line() = default;
    constexpr Line(const double s, const double i): slope(s), intercept(i) {}
    constexpr Line(const Point &a, const Point &b) {
        if (Equal(a.x, b.x)) {
            infinite_slope = true;
            intercept = a.x;
        } else {
            slope = Slope(a, b);
            intercept = b.y - slope * b.x;
        }
    }
};

static inline constexpr auto
operator==(const Line &a_line, const Line &another_line) {
    return a_line.infinite_slope == another_line.infinite_slope and
           Equal(a_line.intercept, another_line.intercept) and
           Equal(a_line.slope, another_line.slope);
}

static inline constexpr auto
operator!=(const Line &a_line, const Line &another_line) {
    return not(a_line == another_line);
}

static inline auto &operator<<(std::ostream &out, const Line &a_line) {
    return out << std::boolalpha << "(" <<
           (a_line.infinite_slope ? a_line.infinite_slope : a_line.slope) <<
           ", " << a_line.intercept << ")";
}

struct LineHashType {
    auto operator()(const Line &l) const {
        return (std::hash<bool>()(l.infinite_slope)) ^
               (std::hash<double>()(l.intercept)) ^
               (std::hash<double>()(l.slope));
    }
};


struct LineSegment {
    Point a{};
    Point b{};
};

static inline auto &operator<<(std::ostream &out, const LineSegment &a_line) {
    return out << "(" << a_line.a << " -> " << a_line.b << ")";
}

static inline constexpr auto
operator==(const LineSegment &lhs, const LineSegment &rhs) {
    return lhs.a == rhs.a and lhs.b == rhs.b;
}
