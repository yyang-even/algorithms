#pragma once

/** Set all bits after the most significant bit
 *
 * @reference   https://www.geeksforgeeks.org/toggle-bits-significant-bit/
 */
inline unsigned SetAllBitsAfterMSB(unsigned num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    num |= num >> 1u;
    num |= num >> 2u;
    num |= num >> 4u;
    num |= num >> 8u;
    num |= num >> 16u;

    return num;
}
