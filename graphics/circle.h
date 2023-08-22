#pragma once


struct Circle {
    int x {};
    int y {};
    int r {};
};


static inline std::ostream &operator<<(std::ostream &out, const Circle &c) {
    return out << "(" << c.x << ", " << c.y << ": " << c.r << ")";
}

static inline constexpr auto Contains(const Circle &a_circle, const int x, const int y) {
    return (x - a_circle.x) * (x - a_circle.x) + (y - a_circle.y) * (y - a_circle.y) <=
           a_circle.r * a_circle.r;
}
