#include "common_header.h"

#include "reverse_digits.h"


namespace {

inline constexpr auto ReverseDigits_Iterative(const int number) {
    return ReverseDigits(number, 10);
}

inline constexpr int
ReverseDigits_Recursive(const int number, int &reversed_number) {
    if (number) {
        const auto base = ReverseDigits_Recursive(number / 10, reversed_number);
        reversed_number += (number % 10) * base;
        return base * 10;
    }

    return 1;
}

inline constexpr auto ReverseDigits_Recursive(const int number) {
    int reversed_number = 0;
    ReverseDigits_Recursive(number, reversed_number);
    return reversed_number;
}


/**
 * @reference   Reverse digits of an integer with overflow handled
 *              https://www.geeksforgeeks.org/reverse-digits-integer-overflow-handled/
 */
constexpr auto ReverseDigits_Safe(int number) {
    int reversed_number = 0;
    for (; number; number /= 10) {
        const auto previous_reversed_number = reversed_number;
        const auto digit = number % 10;
        reversed_number = reversed_number * 10 + digit;

        if ((reversed_number - digit) / 10 != previous_reversed_number) {
            return -1;
        }
    }

    return reversed_number;
}


/**
 * @reference   Reverse a number using stack
 *              https://www.geeksforgeeks.org/reverse-number-using-stack/
 *
 * @note    This solution is not very efficient.
 */

}//namespace


THE_BENCHMARK(ReverseDigits_Iterative, 12345);

SIMPLE_TEST(ReverseDigits_Iterative, TestSAMPLE1, 54321, 12345);
SIMPLE_TEST(ReverseDigits_Iterative, TestSAMPLE2, 6789, 9876);


THE_BENCHMARK(ReverseDigits_Recursive, 12345);

SIMPLE_TEST(ReverseDigits_Recursive, TestSAMPLE1, 54321, 12345);
SIMPLE_TEST(ReverseDigits_Recursive, TestSAMPLE2, 6789, 9876);


THE_BENCHMARK(ReverseDigits_Safe, 12345);

SIMPLE_TEST(ReverseDigits_Safe, TestSAMPLE1, 54321, 12345);
SIMPLE_TEST(ReverseDigits_Safe, TestSAMPLE2, 6789, 9876);
SIMPLE_TEST(ReverseDigits_Safe, TestSAMPLE3, -1, 1000000045);
