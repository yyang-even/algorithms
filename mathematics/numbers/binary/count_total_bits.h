#pragma once


/** Count total bits in a number
 *
 * @reference   https://www.geeksforgeeks.org/count-total-bits-number/
 *
 * Given a positive number n, count total bit in it.
 */
static constexpr inline auto CountTotalBits_Log(const unsigned num) {
    return num ? static_cast<unsigned>(log2(num)) + 1 : 0;
}


static constexpr inline auto CountTotalBits_Loop(unsigned num) {
    unsigned count = 0;
    for (; num; num >>= 1) {
        ++count;
    }
    return count;
}
