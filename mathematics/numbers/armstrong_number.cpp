#include "common_header.h"


namespace {

/** Armstrong Number
 *
 * @reference   https://leetcode.ca/2019-01-07-1134-Armstrong-Number/
 *
 * The k-digit number N is an Armstrong number if and only if the k-th power of each
 * digit sums to N. Given a positive integer N, return true if and only if it is an
 * Armstrong number.
 * 1 <= N <= 10^8
 *
 * @reference   Program for Armstrong Numbers
 *              https://www.geeksforgeeks.org/program-for-armstrong-numbers/
 * @reference   C/C++ program for Armstrong Numbers
 *              https://www.geeksforgeeks.org/c-c-program-for-armstrong-numbers/
 * @reference   C Program to check Armstrong Number
 *              https://www.geeksforgeeks.org/c-program-to-check-armstrong-number/
 */
auto isArmstrong(const int number) {
    const int k = std::log10(number) + 1;

    int sum = 0;
    for (auto i = number; i; i /= 10) {
        sum += std::pow(i % 10, k);
    }

    return sum == number;
}

}//namespace


THE_BENCHMARK(isArmstrong, 153);

SIMPLE_TEST(isArmstrong, TestSAMPLE1, true, 153);
SIMPLE_TEST(isArmstrong, TestSAMPLE2, false, 120);
SIMPLE_TEST(isArmstrong, TestSAMPLE3, false, 1253);
SIMPLE_TEST(isArmstrong, TestSAMPLE4, true, 1634);
