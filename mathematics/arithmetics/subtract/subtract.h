#pragma once


static inline constexpr auto
Subtract_Bits(const int x, const int y) {
    return x + ~y + 1;
}
