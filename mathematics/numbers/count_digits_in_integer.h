#pragma once


constexpr static inline auto CountDigits_Iterative(int n) {
    auto count = 0;
    for (; n; n /= 10) {
        ++count;
    }
    return count;
}
