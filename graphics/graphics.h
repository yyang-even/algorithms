#pragma once

struct Point {
    int x;
    int y;
};


static inline std::ostream &operator <<(std::ostream &out, const Point &p) {
    return out << "(" << p.x << ", " << p.y << ")";
}
