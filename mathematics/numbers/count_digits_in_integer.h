#pragma once

static inline auto CountDigits_Iterative(int n) {
    auto count = 0;
    while (n) {
        n /= 10;
        ++count;
    }
    return count;
}
