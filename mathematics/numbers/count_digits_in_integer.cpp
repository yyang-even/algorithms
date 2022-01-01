#include "common_header.h"

#include "count_digits_in_integer.h"


namespace {

/** Program to count digits in an integer (4 Different Methods)
 *
 * @reference   https://www.geeksforgeeks.org/program-count-digits-integer-3-different-methods/
 * @reference   C program to Count the digits of a number
 *              https://www.geeksforgeeks.org/c-program-to-count-the-digits-of-a-number/
 */
inline constexpr auto CountDigits_Recursive(const int n) {
    if (not n) {
        return 0;
    }
    return 1 + CountDigits_Recursive(n / 10);
}


inline constexpr int CountDigits_Log(const int n) {
    if (not n) {
        return 0;
    }
    return std::floor(std::log10(n) + 1);
}


inline auto CountDigits_String(const int n) {
    assert(n > 0);

    const auto str_n = std::to_string(n);
    return str_n.size();
}


/**
 * @reference   Find Numbers with Even Number of Digits
 *              https://leetcode.com/problems/find-numbers-with-even-number-of-digits/
 *
 * Given an array nums of integers, return how many of them contain an even number of
 * digits.
 */


/**
 * @reference   TCS Coding Practice Question | Sum of Digits of a number
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-sum-of-digits-of-a-number/
 * @reference   C Program for Sum the digits of a given number
 *              https://www.geeksforgeeks.org/c-program-for-program-for-sum-the-digits-of-a-given-number/
 * @reference   Program for Sum of the digits of a given number
 *              https://www.geeksforgeeks.org/program-for-sum-of-the-digits-of-a-given-number/
 * @reference   Sum of digit of a number using recursion
 *              https://www.geeksforgeeks.org/sum-digit-number-using-recursion/
 */


/**
 * @reference   Sum of Digits in the Minimum Number
 *              https://bloggie.io/@rugved/leetcode-1085-sum-of-digits-in-the-minimum-number-java-solution
 *
 * Given an array A of positive integers, let S be the sum of the digits of the minimal
 * element of A. Return 0 if S is odd, otherwise return 1.
 */


/**
 * @reference   Add Digits
 *              https://leetcode.com/problems/add-digits/
 *
 * Given an integer num, repeatedly add all its digits until the result has only one
 * digit, and return it.
 */
inline constexpr auto DigitalRoot(const int number) {
    return number == 0 ? 0 : 1 + (number - 1) % 9;
}


/**
 * @reference   Program to calculate product of digits of a number
 *              https://www.geeksforgeeks.org/program-to-calculate-product-of-digits-of-a-number/
 */


/**
 * @reference   C Program to Print all digits of a given number
 *              https://www.geeksforgeeks.org/c-program-to-print-all-digits-of-a-given-number/
 */


/**
 * @reference   Subtract the Product and Sum of Digits of an Integer
 *              https://leetcode.com/problems/subtract-the-product-and-sum-of-digits-of-an-integer/
 *
 * Given an integer number n, return the difference between the product of its digits and
 * the sum of its digits.
 */


/**
 * @reference   Convert Integer to the Sum of Two No-Zero Integers
 *              https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/
 *
 * Given an integer n. No-Zero integer is a positive integer which doesn't contain any 0
 * in its decimal representation. Return a list of two integers [A, B] where:
 *  A and B are No-Zero integers.
 *  A + B = n
 * It's guaranteed that there is at least one valid solution. If there are many valid
 * solutions you can return any of them.
 */


/**
 * @reference   Count Largest Group
 *              https://leetcode.com/problems/count-largest-group/
 *
 * You are given an integer n. Each number from 1 to n is grouped according to the sum of
 * its digits. Return the number of groups that have the largest size.
 * 1 <= n <= 10^4
 */

}//namespace


THE_BENCHMARK(CountDigits_Iterative, 345289467);

SIMPLE_TEST(CountDigits_Iterative, TestSAMPLE1, 9, 345289467);
SIMPLE_TEST(CountDigits_Iterative, TestSAMPLE2, 0, 0);


THE_BENCHMARK(CountDigits_Recursive, 345289467);

SIMPLE_TEST(CountDigits_Recursive, TestSAMPLE1, 9, 345289467);
SIMPLE_TEST(CountDigits_Recursive, TestSAMPLE2, 0, 0);


THE_BENCHMARK(CountDigits_Log, 345289467);

SIMPLE_TEST(CountDigits_Log, TestSAMPLE1, 9, 345289467);
SIMPLE_TEST(CountDigits_Log, TestSAMPLE2, 0, 0);


THE_BENCHMARK(CountDigits_String, 345289467);

SIMPLE_TEST(CountDigits_String, TestSAMPLE1, 9, 345289467);


THE_BENCHMARK(DigitalRoot, 345289467);

SIMPLE_TEST(DigitalRoot, TestSAMPLE0, 0, 0);
SIMPLE_TEST(DigitalRoot, TestSAMPLE1, 2, 38);
SIMPLE_TEST(DigitalRoot, TestSAMPLE2, 9, 18);
