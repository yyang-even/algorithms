#pragma once

/** Russian Peasant (Multiply two numbers using bitwise operators)
 *
 * @reference   https://www.geeksforgeeks.org/russian-peasant-multiply-two-numbers-using-bitwise-operators/
 * @reference   Russian Peasant Multiplication
 *              http://mathforum.org/dr.math/faq/faq.peasant.html
 */
auto Multiply_RussianPeasant(unsigned lhs, unsigned rhs) {
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
