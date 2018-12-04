#pragma once

/** Compute the sign of an integer
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determining if an integer is a power of 2
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 *              Program to find whether a no is power of two
 *              https://www.geeksforgeeks.org/program-to-find-whether-a-no-is-power-of-two/
 */
INT_BOOL IsPowerOf2(const unsigned num) {
    return num && !(num & (num - 1));
}
