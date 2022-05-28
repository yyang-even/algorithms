#include "common_header.h"

#include "reverse_digits.h"


namespace {

inline constexpr auto ReverseDigits_Iterative(const int number) {
    return ReverseDigits(number, 10);
}

inline constexpr int ReverseDigits_Recursive(const int number, int &reversed_number) {
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
 * Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the
 * value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1], then return 0.
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


/**
 * @reference   Reverse a number using stack
 *              https://www.geeksforgeeks.org/reverse-number-using-stack/
 *
 * @note    This solution is not very efficient.
 */


/**
 * @reference   A Number After a Double Reversal
 *              https://leetcode.com/problems/a-number-after-a-double-reversal/
 *
 * Reversing an integer means to reverse all its digits.
 *  For example, reversing 2021 gives 1202. Reversing 12300 gives 321 as the leading zeros are
 *  not retained.
 * Given an integer num, reverse num to get reversed1, then reverse reversed1 to get reversed2.
 * Return true if reversed2 equals num. Otherwise return false.
 */
inline constexpr auto isSameAfterDoubleReversal(const int num) {
    return not num or num % 10;
}

} //namespace


THE_BENCHMARK(ReverseDigits_Iterative, 12345);

SIMPLE_TEST(ReverseDigits_Iterative, TestSAMPLE1, 54321, 12345);
SIMPLE_TEST(ReverseDigits_Iterative, TestSAMPLE2, 6789, 9876);


THE_BENCHMARK(ReverseDigits_Recursive, 12345);

SIMPLE_TEST(ReverseDigits_Recursive, TestSAMPLE1, 54321, 12345);
SIMPLE_TEST(ReverseDigits_Recursive, TestSAMPLE2, 6789, 9876);


THE_BENCHMARK(ReverseDigits_UltraSafe, 12345);

SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE1, 54321, 12345);
SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE2, 6789, 9876);
SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE3, 0, 1000000045);
SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE4, 0, 1563847412);
SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE5, 0, -2147483648);
SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE6, 0, 1056389759);
SIMPLE_TEST(ReverseDigits_UltraSafe, TestSAMPLE7, -321, -123);


THE_BENCHMARK(isSameAfterDoubleReversal, 526);

SIMPLE_TEST(isSameAfterDoubleReversal, TestSAMPLE1, true, 526);
SIMPLE_TEST(isSameAfterDoubleReversal, TestSAMPLE2, false, 1800);
SIMPLE_TEST(isSameAfterDoubleReversal, TestSAMPLE3, true, 0);
