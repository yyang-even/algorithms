#pragma once


/** Russian Peasant (Multiply two numbers using bitwise operators)
 *
 * @reference   https://www.geeksforgeeks.org/russian-peasant-multiply-two-numbers-using-bitwise-operators/
 * @reference   Russian Peasant Multiplication
 *              http://mathforum.org/dr.math/faq/faq.peasant.html
 * @reference   Multiplication of two numbers with shift operator
 *              https://www.geeksforgeeks.org/multiplication-two-numbers-shift-operator/
 */
static constexpr inline auto
Multiply_RussianPeasant(unsigned lhs, unsigned rhs) {
    if (not rhs) {
        return rhs;
    }

    unsigned result = 0;
    while (rhs) {
        if (rhs & 1) {
            result += lhs;
        }

        lhs <<= 1;
        rhs >>= 1;
    }

    return result ? result : lhs;
}
