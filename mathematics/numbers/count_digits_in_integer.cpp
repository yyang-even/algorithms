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
inline constexpr auto DigitalRoot(const int num) {
    return 1 + (num - 1) % 9;
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


/**
 * @reference   Maximum Number of Balls in a Box
 *              https://leetcode.com/problems/maximum-number-of-balls-in-a-box/
 *
 * You are working in a ball factory where you have n balls numbered from lowLimit up to
 * highLimit inclusive (i.e., n == highLimit - lowLimit + 1), and an infinite number of
 * boxes numbered from 1 to infinity.
 * Your job at this factory is to put each ball in the box with a number equal to the sum
 * of digits of the ball's number. For example, the ball number 321 will be put in the box
 * number 3 + 2 + 1 = 6 and the ball number 10 will be put in the box number 1 + 0 = 1.
 * Given two integers lowLimit and highLimit, return the number of balls in the box with
 * the most balls.
 * 1 <= lowLimit <= highLimit <= 10^5
 */
constexpr auto DigitsSum(int n) {
    int sum = 0;
    for (; n; n /= 10) {
        sum += (n % 10);
    }

    return sum;
}

constexpr auto MaxBallsInBox(const int lowLimit, const int highLimit) {
    auto index = DigitsSum(lowLimit);
    int boxes[5 * 9 + 1] = {};
    ++boxes[index];

    for (auto i = lowLimit + 1; i <= highLimit; ++i) {
        for (auto n = i; n % 10 == 0; n /= 10) {
            index -= 9;
        }

        ++boxes[++index];
    }

    return *std::max_element(std::cbegin(boxes), std::cend(boxes));
}

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


THE_BENCHMARK(MaxBallsInBox, 1, 10);

SIMPLE_TEST(MaxBallsInBox, TestSAMPLE1, 2, 1, 10);
SIMPLE_TEST(MaxBallsInBox, TestSAMPLE2, 2, 5, 15);
SIMPLE_TEST(MaxBallsInBox, TestSAMPLE3, 2, 19, 28);
