#pragma once

/** Set all bits after the most significant bit
 *
 * @reference   https://www.geeksforgeeks.org/toggle-bits-significant-bit/
 */
inline auto SetAllBitsAfterMSB(uint32_t num) {
    num |= num >> 1u;
    num |= num >> 2u;
    num |= num >> 4u;
    num |= num >> 8u;
    num |= num >> 16u;

    return num;
}
