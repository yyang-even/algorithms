#pragma once

#include "point.h"


static inline constexpr auto
TriangleArea(const double x1, const double y1,
             const double x2, const double y2,
             const double x3, const double y3) {
    return std::abs(0.5 * (x2 * y3 + x1 * y2 + x3 * y1 - x3 * y2 - x2 * y1 - x1 * y3));
}

static inline constexpr auto
TriangleArea(const Point &x, const Point &y, const Point &z) {
    return TriangleArea(x.x, x.y, y.x, y.y, z.x, z.y);
}
