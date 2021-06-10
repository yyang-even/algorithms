#pragma once


static inline constexpr auto
CountDigits_Iterative(int n) {
    auto count = 0;
    for (; n; n /= 10) {
        ++count;
    }
    return count;
}
