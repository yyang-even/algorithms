#pragma once

#include "set_all_bits_after_most_significant_bit.h"


/** Find most significant set bit of a number
 *
 * @reference   https://www.geeksforgeeks.org/find-significant-set-bit-number/
 * @reference   Highest power of 2 less than or equal to given number
 *              https://www.geeksforgeeks.org/highest-power-2-less-equal-given-number/
 *
 * Some people are standing in a queue. A selection process follows a rule where people
 * standing on even positions are selected. Of the selected people a queue is formed and
 * again out of these only people on even position are selected. This continues until we
 * are left with one person. Find out the position of that person in the original queue.
 * Print the position(original queue) of that person who is left.
 *
 * @reference   Highest power of 2 less than or equal to given Integer
 *              https://www.geeksforgeeks.org/highest-power-of-2-less-than-or-equal-to-given-integer/
 *
 * Given a number, find the most significant bit number which is set bit and which is in
 * power of two.
 */
static inline constexpr unsigned FindMSB(const unsigned num) {
    return (SetAllBitsAfterMSB(num) + 1ull) >> 1;
}
