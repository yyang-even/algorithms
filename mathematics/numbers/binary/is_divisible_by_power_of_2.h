#pragma once


/** Check if n is divisible by power of 2 without using arithmetic operators
 *
 * @reference   https://www.geeksforgeeks.org/check-n-divisible-power-2-without-using-arithmetic-operators/
 *
 * Given two positive integers n and m. The problem is to check whether n
 * is divisible by 2^m or not.
 */
INT_BOOL IsDivisibleByPowerOf2Arithmetic(const unsigned n, const unsigned m) {
    return (n & ((1 << m) - 1)) == 0;
}


INT_BOOL IsDivisibleByPowerOf2Bitwise(const unsigned n, const unsigned m) {
    return ((n >> m) << m) == n;
}
