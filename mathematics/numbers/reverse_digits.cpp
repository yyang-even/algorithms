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
 * @reference   Reverse Integer
 *              https://leetcode.com/problems/reverse-integer/
 *
 * Given a signed 32-bit integer x, return x with its digits reversed. If reversing x
 * causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1],
 * then return 0.
 */
constexpr auto ReverseDigits_UltraSafe(int32_t number) {
    int32_t result = 0;
    for (; number; number /= 10) {
        const auto digit = number % 10;
        if (result > INT_MAX / 10 or (result == INT_MAX / 10 and digit > 7)) {
            return 0;
        }
        if (result < INT_MIN / 10 or (result == INT_MIN / 10 and digit < -8)) {
            return 0;
        }

        result = result * 10 + digit;
    }

    return result;
}


constexpr auto ReverseDigits_Safe(int32_t number) {
    int32_t reversed_number = 0;
    for (; number; number /= 10) {
        const auto previous_reversed_number = reversed_number;
        const auto digit = number % 10;
        reversed_number = reversed_number * 10 + digit; // undefined behavior

        if ((reversed_number - digit) / 10 != previous_reversed_number) {
            return 0;
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
SIMPLE_TEST(ReverseDigits_Safe, TestSAMPLE3, 0, 1000000045);
SIMPLE_TEST(ReverseDigits_Safe, TestSAMPLE4, 0, 1563847412);
SIMPLE_TEST(ReverseDigits_Safe, TestSAMPLE5, 0, -2147483648);
SIMPLE_TEST(ReverseDigits_Safe, TestSAMPLE6, 0, 1056389759);
SIMPLE_TEST(ReverseDigits_Safe, TestSAMPLE7, -321, -123);


THE_BENCHMARK(ReverseDigits_UltraSafe, 12345);

SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE1, 54321, 12345);
SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE2, 6789, 9876);
SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE3, 0, 1000000045);
SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE4, 0, 1563847412);
SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE5, 0, -2147483648);
SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE6, 0, 1056389759);
SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE7, -321, -123);
