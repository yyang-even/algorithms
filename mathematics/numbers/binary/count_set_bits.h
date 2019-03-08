#pragma once

/**
 * Brian Kernighan’s Algorithm
 */
unsigned CountSetBitsBrianKernighan(unsigned n) {
    unsigned count = 0;
    while (n) {
        ++count;
        n &= (n - 1);
    }
    return count;
}
