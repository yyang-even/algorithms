#pragma once


struct Point {
    double x{};
    double y{};
};

static inline constexpr auto Equal(const double x, const double y) {
    return std::abs(x - y) < std::numeric_limits<double>::epsilon();
}

static inline std::ostream &operator <<(std::ostream &out, const Point &p) {
    return out << "(" << p.x << ", " << p.y << ")";
}

static inline constexpr auto operator==(const Point &lhs, const Point &rhs) {
    return Equal(lhs.x, rhs.x) and Equal(lhs.y, rhs.y);
}
