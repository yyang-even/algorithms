#pragma once


static inline constexpr auto Abs_Count(const int number) {
    if (number >= 0) {
        return number;
    }

    int result = 0;
    for (auto i = number; i++ < 0;) {
        ++result;
    }

    return result;
}
