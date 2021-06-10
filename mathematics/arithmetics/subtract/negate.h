#pragma once


/** Implement *, – and / operations using only + arithmetic operator
 *
 * @reference   https://www.geeksforgeeks.org/implement-and-operations-using-only-arithmetic-operator/
 *
 * Given two numbers, perform multiplication, subtraction and division operations on
 * them, using '+' arithmetic operator only.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 7.4.
 */
static inline constexpr auto Negate(int number) {
    int result = 0;
    const int step = number < 0 ? 1 : -1;
    for (; number; number += step) {
        result += step;
    }

    return result;
}
