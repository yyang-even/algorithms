#pragma once


/**
 * Brian Kernighan’s Algorithm
 *
 * @tags    #bit-tricks
 */
static inline constexpr unsigned CountSetBits_BrianKernighan(unsigned n) {
    unsigned count = 0;
    while (n) {
        ++count;
        n &= (n - 1);
    }
    return count;
}
