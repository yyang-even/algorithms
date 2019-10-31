#pragma once


/** Count total bits in a number
 *
 * @reference   https://www.geeksforgeeks.org/count-total-bits-number/
 *
 * Given a positive number n, count total bit in it.
 */
auto CountTotalBits_Log(const unsigned num) {
    assert(num);
    return static_cast<unsigned>(log2(num)) + 1;
}


auto CountTotalBits_Loop(unsigned num) {
    unsigned count = 0;
    for (; num; num >>= 1) {
        ++count;
    }
    return count;
}
