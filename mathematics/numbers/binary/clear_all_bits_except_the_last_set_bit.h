#pragma once


/** Getting lowest set bit of a number
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 */
static inline constexpr auto
ClearAllBitsExceptTheLastSetBit(const unsigned num) {
    return num & (-num);
}
