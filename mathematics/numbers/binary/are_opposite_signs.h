#pragma once


/** Detect if two integers have opposite signs
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Detect if two integers have opposite signs
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Detect if two integers have opposite signs
 *              https://www.geeksforgeeks.org/detect-if-two-integers-have-opposite-signs/
 *
 * Given two signed integers, write a function that returns true if the signs of given
 * integers are different, otherwise false. For example, the function should return
 * true -1 and +100, and should return false for -100 and -200. The function should
 * not use any of the arithmetic operators.
 */
static constexpr inline auto
AreOppositeSigns(const int x, const int y) {
    return (x ^ y) < 0;
}
