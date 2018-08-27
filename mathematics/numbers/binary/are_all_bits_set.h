#pragma once

#include "common_header.h"

/** Check if all bits of a number are set
 *
 * @reference   https://www.geeksforgeeks.org/check-bits-number-set/
 *
 * Given a number n. The problem is to check whether every bit in the binary
 * representation of the given number is set or not. Here 0 <= n.
 */
INT_BOOL AreAllBitsSet(const unsigned num) {
    if (num == 0) {
        return FALSE;
    }
    return not(num & (num + 1));
}
