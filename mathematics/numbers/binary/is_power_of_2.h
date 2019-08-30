#pragma once

/** Compute the sign of an integer
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determining if an integer is a power of 2
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Program to find whether a no is power of two
 *              https://www.geeksforgeeks.org/program-to-find-whether-a-no-is-power-of-two/
 * @reference   C Program to find whether a no is power of two
 *              https://www.geeksforgeeks.org/c-program-to-find-whether-a-no-is-power-of-two/
 */
auto IsPowerOf2(const unsigned num) {
    return num && !(num & (num - 1));
}