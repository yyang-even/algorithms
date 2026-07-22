#pragma once


/**
 * @reference   Set all bits after the most significant bit
 *              https://www.geeksforgeeks.org/toggle-bits-significant-bit/
 *
 * @tags    #bit-tricks
 */
static inline constexpr auto SetAllBitsAfterMSB(uint32_t num) {
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;

    return num;
}
