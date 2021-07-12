#include "common_header.h"


namespace {

/** Happy Number
 *
 * @reference   https://www.geeksforgeeks.org/happy-number/
 * @reference   Happy Numbers
 *              https://www.geeksforgeeks.org/happy-numbers/
 * @reference   Happy Number
 *              https://leetcode.com/problems/happy-number/
 *
 * Write an algorithm to determine if a number n is happy. A happy number is a number
 * defined by the following process:
 *  Starting with any positive integer, replace the number by the sum of the squares of
 *  its digits.
 *  Repeat the process until the number equals 1 (where it will stay), or it loops
 *  endlessly in a cycle which does not include 1.
 *  Those numbers for which this process ends in 1 are happy.
 * Return true if n is a happy number, and false if not.
 */
constexpr auto sumOfDigitSquares(int num) {
    int sum = 0;
    while (num) {
        const auto digit = num % 10;
        sum += digit * digit;
        num /= 10;
    }

    return sum;
}

auto isHappyNumber_Set(int n) {
    std::unordered_set<int> seen;
    seen.insert(n);

    while (true) {
        n = sumOfDigitSquares(n);
        if (n == 1 or n == 7) {
            return true;
        }
        if (not seen.insert(n).second) {
            return false;
        }
    }

    return false;
}


constexpr auto isHappyNumber_TwoPointers(const int n) {
    auto slow = n;
    auto fast = n;
    do {
        slow = sumOfDigitSquares(slow);
        fast = sumOfDigitSquares(sumOfDigitSquares(fast));
    } while (slow != fast);

    return slow == 1;
}


constexpr auto isHappyNumber_O1(int n) {
    while (n > 9) {
        n = sumOfDigitSquares(n);
    }

    return n == 1 or n == 7;
}

}//namespace


THE_BENCHMARK(isHappyNumber_Set, 19);

SIMPLE_TEST(isHappyNumber_Set, TestSAMPLE1, true, 1);
SIMPLE_TEST(isHappyNumber_Set, TestSAMPLE2, true, 7);
SIMPLE_TEST(isHappyNumber_Set, TestSAMPLE3, true, 10);
SIMPLE_TEST(isHappyNumber_Set, TestSAMPLE4, true, 19);
SIMPLE_TEST(isHappyNumber_Set, TestSAMPLE5, true, 100);
SIMPLE_TEST(isHappyNumber_Set, TestSAMPLE6, false, 2);
SIMPLE_TEST(isHappyNumber_Set, TestSAMPLE7, false, 20);


THE_BENCHMARK(isHappyNumber_TwoPointers, 19);

SIMPLE_TEST(isHappyNumber_TwoPointers, TestSAMPLE1, true, 1);
SIMPLE_TEST(isHappyNumber_TwoPointers, TestSAMPLE2, true, 7);
SIMPLE_TEST(isHappyNumber_TwoPointers, TestSAMPLE3, true, 10);
SIMPLE_TEST(isHappyNumber_TwoPointers, TestSAMPLE4, true, 19);
SIMPLE_TEST(isHappyNumber_TwoPointers, TestSAMPLE5, true, 100);
SIMPLE_TEST(isHappyNumber_TwoPointers, TestSAMPLE6, false, 2);
SIMPLE_TEST(isHappyNumber_TwoPointers, TestSAMPLE7, false, 20);


THE_BENCHMARK(isHappyNumber_O1, 19);

SIMPLE_TEST(isHappyNumber_O1, TestSAMPLE1, true, 1);
SIMPLE_TEST(isHappyNumber_O1, TestSAMPLE2, true, 7);
SIMPLE_TEST(isHappyNumber_O1, TestSAMPLE3, true, 10);
SIMPLE_TEST(isHappyNumber_O1, TestSAMPLE4, true, 19);
SIMPLE_TEST(isHappyNumber_O1, TestSAMPLE5, true, 100);
SIMPLE_TEST(isHappyNumber_O1, TestSAMPLE6, false, 2);
SIMPLE_TEST(isHappyNumber_O1, TestSAMPLE7, false, 20);
