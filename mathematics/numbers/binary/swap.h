#pragma once

/** Swapping values with XOR
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Swapping values with XOR
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   How to swap two numbers without using a temporary variable?
 *              https://www.geeksforgeeks.org/swap-two-numbers-without-using-temporary-variable/
 */
template <typename T>
void Swap_Xor(T &a, T &b) {
    if (a != b) {
        a ^= b;
        b ^= a;
        a ^= b;
    }
}
