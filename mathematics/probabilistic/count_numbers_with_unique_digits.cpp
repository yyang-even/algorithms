#include "common_header.h"


namespace {

/** Count Numbers with Unique Digits
 *
 * @reference   https://leetcode.com/problems/count-numbers-with-unique-digits/
 *
 * Given an integer n, return the count of all numbers with unique digits, x, where 0 <= x < 10^n.
 */
constexpr auto CountNumWithUniqueDigitsOf(const int digit) {
    assert(digit >= 2);

    int choice = 9;
    auto result = choice;
    for (int i = 2; i <= digit; ++i) {
        result *= choice--;
    }

    return result;
}

constexpr auto CountNumWithUniqueDigits(const int n) {
    if (n == 0) {
        return 1;
    }

    int result = 10;
    if (n == 1) {
        return result;
    }

    for (int i = 2; i <= n; ++i) {
        result += CountNumWithUniqueDigitsOf(i);
    }

    return result;
}

} //namespace


THE_BENCHMARK(CountNumWithUniqueDigits, 2);

SIMPLE_TEST(CountNumWithUniqueDigits, TestSAMPLE1, 91, 2);
SIMPLE_TEST(CountNumWithUniqueDigits, TestSAMPLE2, 1, 0);
