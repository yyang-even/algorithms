#pragma once


/** Turn off the rightmost set bit
 *
 * @reference   https://www.geeksforgeeks.org/turn-off-the-rightmost-set-bit/
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 */
static constexpr inline auto ClearRightmostBit(const unsigned num) {
    return num & (num - 1);
}
