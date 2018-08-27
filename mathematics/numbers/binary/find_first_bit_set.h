#pragma once

/** Position of rightmost set bit
 *
 * @reference   https://www.geeksforgeeks.org/position-of-rightmost-set-bit/
 *
 * Write a one line C function to return position of first 1 from right to left,
 * in binary representation of an Integer.
 */
inline unsigned FindFirstBitSet(const unsigned num) {
    assert(num);

    return log2(num & (-num)) + 1;
}

