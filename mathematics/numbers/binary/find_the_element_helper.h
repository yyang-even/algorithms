#pragma once


template <typename T>
static constexpr inline void
divideElement(const T elem, const T lsb, T &x, T &y) {
    if (elem & lsb) {
        x ^= elem;
    } else {
        y ^= elem;
    }
}
