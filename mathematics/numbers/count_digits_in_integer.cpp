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
 * Given an array nums of integers, return how many of them contain an even number of digits.
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
 * Given an array A of positive integers, let S be the sum of the digits of the minimal element of A.
 * Return 0 if S is odd, otherwise return 1.
 */


/**
 * @reference   Add Digits
 *              https://leetcode.com/problems/add-digits/
 *
 * Given an integer num, repeatedly add all its digits until the result has only one digit, and return
 * it.
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
 * Given an integer number n, return the difference between the product of its digits and the sum of its
 * digits.
 */


/**
 * @reference   Convert Integer to the Sum of Two No-Zero Integers
 *              https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/
 *
 * Given an integer n. No-Zero integer is a positive integer which doesn't contain any 0 in its decimal
 * representation. Return a list of two integers [A, B] where:
 *  A and B are No-Zero integers.
 *  A + B = n
 * It's guaranteed that there is at least one valid solution. If there are many valid solutions you can
 * return any of them.
 */


/**
 * @reference   Count Largest Group
 *              https://leetcode.com/problems/count-largest-group/
 *
 * You are given an integer n. Each number from 1 to n is grouped according to the sum of its digits.
 * Return the number of groups that have the largest size.
 * 1 <= n <= 10^4
 */


/**
 * @reference   Maximum Number of Balls in a Box
 *              https://leetcode.com/problems/maximum-number-of-balls-in-a-box/
 *
 * You are working in a ball factory where you have n balls numbered from lowLimit up to highLimit
 * inclusive (i.e., n == highLimit - lowLimit + 1), and an infinite number of boxes numbered from 1 to
 * infinity.
 * Your job at this factory is to put each ball in the box with a number equal to the sum of digits of
 * the ball's number. For example, the ball number 321 will be put in the box number 3 + 2 + 1 = 6 and
 * the ball number 10 will be put in the box number 1 + 0 = 1.
 * Given two integers lowLimit and highLimit, return the number of balls in the box with the most balls.
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


/**
 * @reference   Sum of Digits in Base K
 *              https://leetcode.com/problems/sum-of-digits-in-base-k/
 *
 * Given an integer n (in base 10) and a base k, return the sum of the digits of n after converting n
 * from base 10 to base k.
 * After converting, each digit should be interpreted as a base 10 number, and the sum should be
 * returned in base 10.
 */


/**
 * @reference   Sum of Digits of String After Convert
 *              https://leetcode.com/problems/sum-of-digits-of-string-after-convert/
 *
 * You are given a string s consisting of lowercase English letters, and an integer k.
 * First, convert s into an integer by replacing each letter with its position in the alphabet (i.e.,
 * replace 'a' with 1, 'b' with 2, ..., 'z' with 26). Then, transform the integer by replacing it with
 * the sum of its digits. Repeat the transform operation k times in total.
 * For example, if s = "zbax" and k = 2, then the resulting integer would be 8 by the following
 * operations:
 *  Convert: "zbax" ➝ "(26)(2)(1)(24)" ➝ "262124" ➝ 262124
 *  Transform #1: 262124 ➝ 2 + 6 + 2 + 1 + 2 + 4 ➝ 17
 *  Transform #2: 17 ➝ 1 + 7 ➝ 8
 * Return the resulting integer after performing the operations described above.
 */


/**
 * @reference   Count Integers With Even Digit Sum
 *              https://leetcode.com/problems/count-integers-with-even-digit-sum/
 *
 * Given a positive integer num, return the number of positive integers less than or equal to num whose
 * digit sums are even.
 * The digit sum of a positive integer is the sum of all its digits.
 */
inline constexpr auto CountEven(const int num) {
    const auto sum = DigitsSum(num);
    return (num - sum % 2) / 2;
}


/**
 * @reference   Calculate Digit Sum of a String
 *              https://leetcode.com/problems/calculate-digit-sum-of-a-string/
 *
 * You are given a string s consisting of digits and an integer k.
 * A round can be completed if the length of s is greater than k. In one round, do the following:
 *  Divide s into consecutive groups of size k such that the first k characters are in the first group,
 *      the next k characters are in the second group, and so on. Note that the size of the last group
 *      can be smaller than k.
 *  Replace each group of s with a string representing the sum of all its digits. For example, "346" is
 *      replaced with "13" because 3 + 4 + 6 = 13.
 *  Merge consecutive groups together to form a new string. If the length of the string is greater than
 *      k, repeat from step 1.
 * Return s after all rounds have been completed.
 */


/**
 * @reference   Partitioning Into Minimum Number Of Deci-Binary Numbers
 *              https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/
 *
 * A decimal number is called deci-binary if each of its digits is either 0 or 1 without any leading
 * zeros. For example, 101 and 1100 are deci-binary, while 112 and 3001 are not.
 * Given a string n that represents a positive decimal integer, return the minimum number of positive
 * deci-binary numbers needed so that they sum up to n.
 *
 * @hint    Just return the max digit
 */


/**
 * @reference   Reordered Power of 2
 *              https://leetcode.com/problems/reordered-power-of-2/
 *
 * You are given an integer n. We reorder the digits in any order (including the original order) such
 * that the leading digit is not zero.
 * Return true if and only if we can do this so that the resulting number is a power of two.
 * 1 <= n <= 10^9
 */
auto toDigits(unsigned n) {
    std::vector<int> digits;
    while (n) {
        digits.push_back(n % 10);
        n /= 10;
    }

    std::sort(digits.begin(), digits.end(), std::greater<int> {});
    return digits;
}

auto build() {
    std::vector<std::vector<int>> power_of_2s;
    for (int i = 0; i < 32; ++i) {
        const auto n = 1u << i;
        power_of_2s.push_back(toDigits(n));
    }

    return power_of_2s;
}

bool ReorderedPowerOf2_Sort(const int n) {
    static const auto power_of_2s = build();

    const auto digits = toDigits(n);
    for (const auto &power : power_of_2s) {
        if (digits.size() == power.size() and
            std::equal(digits.cbegin(), digits.cend(), power.cbegin())) {
            return true;
        }
    }

    return false;
}


constexpr auto mask(unsigned n) {
    unsigned result = 0;
    for (; n; n /= 10) {
        result += std::pow(10, n % 10);
    }

    return result;
}

constexpr auto ReorderedPowerOf2_Mask(const int n) {
    const auto m = mask(n);
    for (int i = 0; i < 32; ++i) {
        if (mask(1 << i) == m) {
            return true;
        }
    }

    return false;
}


/**
 * @reference   Max Pair Sum in an Array
 *              https://leetcode.com/problems/max-pair-sum-in-an-array/
 *
 * You are given a 0-indexed integer array nums. You have to find the maximum sum of a pair of numbers
 * from nums such that the maximum digit in both numbers are equal.
 * Return the maximum sum or -1 if no such pair exists.
 */

} //namespace


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


THE_BENCHMARK(CountEven, 4);

SIMPLE_TEST(CountEven, TestSAMPLE1, 2, 4);
SIMPLE_TEST(CountEven, TestSAMPLE2, 14, 30);


THE_BENCHMARK(ReorderedPowerOf2_Sort, 10);

SIMPLE_TEST(ReorderedPowerOf2_Sort, TestSAMPLE1, false, 10);
SIMPLE_TEST(ReorderedPowerOf2_Sort, TestSAMPLE2, true, 1);


THE_BENCHMARK(ReorderedPowerOf2_Mask, 10);

SIMPLE_TEST(ReorderedPowerOf2_Mask, TestSAMPLE1, false, 10);
SIMPLE_TEST(ReorderedPowerOf2_Mask, TestSAMPLE2, true, 1);
