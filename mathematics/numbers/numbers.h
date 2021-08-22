#pragma once


constexpr double epsilon = 1e-5;


static inline constexpr auto
CloseEnough(const double one, const double another) {
    return std::abs(one - another) < epsilon;
}
