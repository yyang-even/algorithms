#pragma once


/** Write a program to reverse digits of a number
 *
 * @reference   https://www.geeksforgeeks.org/write-a-program-to-reverse-digits-of-a-number/
 */
static inline constexpr auto ReverseDigits(int number, const int base) {
    int reversed_number = 0;
    for (; number; number /= base) {
        reversed_number = reversed_number * base + number % base;
    }

    return reversed_number;
}
