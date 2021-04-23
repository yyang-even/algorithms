#pragma once

/** Swapping values with XOR
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Swapping values with XOR
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   How to swap two numbers without using a temporary variable?
 *              https://www.geeksforgeeks.org/swap-two-numbers-without-using-temporary-variable/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.1.
 */
template <typename T>
static constexpr inline void Swap_Xor(T &a, T &b) {
    if (a != b) {
        a ^= b;
        b ^= a;
        a ^= b;
    }
}
