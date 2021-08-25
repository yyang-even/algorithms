#include "common_header.h"

#include "perfect_square.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Check if a number is perfect square without finding square root
 *
 * @reference   https://www.geeksforgeeks.org/check-if-a-number-is-perfect-square-without-finding-square-root/
 *
 * @reference   Valid Perfect Square
 *              https://leetcode.com/problems/valid-perfect-square/
 *
 * Given a positive integer num, write a function which returns True if num is a perfect
 * square else False.
 * Follow up: Do not use any built-in library function such as sqrt.
 */
constexpr auto IsPerfectSquare_Multiply(const unsigned x) {
    for (unsigned i = 1, square = 1; square <= x; square = i * i) {
        if (square == x) {
            return true;
        }
        ++i;
    }

    return false;
}


/** Check perfect square using addition/subtraction
 *
 * @reference   https://www.geeksforgeeks.org/check-number-is-perfect-square-using-additionsubtraction/
 *
 * Addition of first n odd numbers is always perfect square
 */
constexpr auto IsPerfectSquare_Sum(const unsigned x) {
    for (unsigned sum = 0, i = 1; sum < x; i += 2) {
        sum += i;
        if (sum == x) {
            return true;
        }
    }

    return false;
}


/**
 * @reference   Check if a given number is a Perfect square using Binary Search
 *              https://www.geeksforgeeks.org/check-if-a-given-number-is-a-perfect-square-using-binary-search/
 */


/** Check if count of divisors is even or odd
 *
 * @reference   https://www.geeksforgeeks.org/check-if-total-number-of-divisors-are-even-or-odd/
 * @reference   C Program to Check if count of divisors is even or odd
 *              https://www.geeksforgeeks.org/c-program-for-check-if-count-of-divisors-is-even-or-odd/
 *
 * Given a number "n", find its total number of divisors are even or odd.
 */
inline constexpr auto isCountOfDivisorsOdd(const unsigned N) {
    return IsPerfectSquare(N);
}


/** Number of perfect squares between two given numbers
 *
 * @reference   https://www.geeksforgeeks.org/find-number-perfect-squares-two-given-numbers/
 *
 * Given two given numbers a and b where 1<=a<=b, find the number of perfect
 * squares between a and b (a and b inclusive).
 *
 * @reference   Count Open Lockers
 *              John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 14.
 *
 * Suppose you are in a hallway lined with 100 closed lockers. You begin by opening all
 * 100 lockers. Next, you close every second locker. Then you go to every third locker
 * and close it if it is open or open it if it's closed --- call this toggling the
 * lockers. You continue toggling every nth locker on pass number n. After your hundredth
 * pass of the hallway, in which you toggle only locker number 100, how many lockers are
 * open?
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 6.6.
 */
inline constexpr auto
CountPerfectSquares(const unsigned a, const unsigned b) {
    assert(a <= b);

    return std::floor(std::sqrt(b)) - std::ceil(std::sqrt(a)) + 1;
}


/**
 * @reference   Print all perfect squares from the given range
 *              https://www.geeksforgeeks.org/print-all-perfect-squares-from-the-given-range/
 */
auto AllPerfectSquares(const unsigned a, const unsigned b) {
    assert(a <= b);
    ArrayType results;

    unsigned diff = std::ceil(std::sqrt(a));
    auto perfect_square = diff * diff;
    for (diff = diff * 2 + 1; perfect_square >= a and perfect_square <= b; diff += 2) {
        results.push_back(perfect_square);
        perfect_square += diff;
    }

    return results;
}


/**
 * @reference   Sum of Square Numbers
 *              https://leetcode.com/problems/sum-of-square-numbers/
 *
 * Given a non-negative integer c, decide whether there're two integers a and b such that
 * a^2 + b^2 = c.
 */
inline constexpr auto hasSquareSum(const int c) {
    for (long i = 0; i * i <= c; ++i) {
        if (IsPerfectSquare(c - i * i)) {
            return true;
        }
    }

    return false;
}


inline constexpr auto hasSquareSum_Fermat(int c) {
    for (int i = 2; i * i <= c; ++i) {
        int count = 0;
        if (c % i == 0) {
            while (c % i == 0) {
                ++count;
                c /= i;
            }
            if (i % 4 == 3 and count % 2 != 0) {
                return false;
            }
        }
    }

    return c % 4 != 3;
}

}//namespace


THE_BENCHMARK(IsPerfectSquare, 2500);

SIMPLE_TEST(IsPerfectSquare, TestSAMPLE1, true, 2500);
SIMPLE_TEST(IsPerfectSquare, TestSAMPLE2, false, 2555);


THE_BENCHMARK(IsPerfectSquare_Multiply, 2500);

SIMPLE_TEST(IsPerfectSquare_Multiply, TestSAMPLE1, true, 2500);
SIMPLE_TEST(IsPerfectSquare_Multiply, TestSAMPLE2, false, 2555);


THE_BENCHMARK(IsPerfectSquare_Sum, 2500);

SIMPLE_TEST(IsPerfectSquare_Sum, TestSAMPLE1, true, 2500);
SIMPLE_TEST(IsPerfectSquare_Sum, TestSAMPLE2, false, 2555);


THE_BENCHMARK(isCountOfDivisorsOdd, 100);

SIMPLE_TEST(isCountOfDivisorsOdd, TestSAMPLE1, false, 10);
SIMPLE_TEST(isCountOfDivisorsOdd, TestSAMPLE2, true, 100);
SIMPLE_TEST(isCountOfDivisorsOdd, TestSAMPLE3, false, 125);


const ArrayType EXPECTED1 = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
const ArrayType EXPECTED2 = {4};
const ArrayType EXPECTED3 = {9, 16, 25};
const ArrayType EXPECTED4 = {4, 9, 16};


THE_BENCHMARK(CountPerfectSquares, 1, 100);

SIMPLE_TEST(CountPerfectSquares, TestSAMPLE1, EXPECTED1.size(), 1, 100);
SIMPLE_TEST(CountPerfectSquares, TestSAMPLE2, EXPECTED2.size(), 3, 8);
SIMPLE_TEST(CountPerfectSquares, TestSAMPLE3, EXPECTED3.size(), 9, 25);
SIMPLE_TEST(CountPerfectSquares, TestSAMPLE4, EXPECTED4.size(), 2, 24);


THE_BENCHMARK(AllPerfectSquares, 1, 100);

SIMPLE_TEST(AllPerfectSquares, TestSAMPLE1, EXPECTED1, 1, 100);
SIMPLE_TEST(AllPerfectSquares, TestSAMPLE2, EXPECTED2, 3, 8);
SIMPLE_TEST(AllPerfectSquares, TestSAMPLE3, EXPECTED3, 9, 25);
SIMPLE_TEST(AllPerfectSquares, TestSAMPLE4, EXPECTED4, 2, 24);


THE_BENCHMARK(hasSquareSum, 100);

SIMPLE_TEST(hasSquareSum, TestSAMPLE1, true, 5);
SIMPLE_TEST(hasSquareSum, TestSAMPLE2, false, 3);
SIMPLE_TEST(hasSquareSum, TestSAMPLE3, true, 4);
SIMPLE_TEST(hasSquareSum, TestSAMPLE4, true, 2);
SIMPLE_TEST(hasSquareSum, TestSAMPLE5, true, 1);


THE_BENCHMARK(hasSquareSum_Fermat, 100);

SIMPLE_TEST(hasSquareSum_Fermat, TestSAMPLE1, true, 5);
SIMPLE_TEST(hasSquareSum_Fermat, TestSAMPLE2, false, 3);
SIMPLE_TEST(hasSquareSum_Fermat, TestSAMPLE3, true, 4);
SIMPLE_TEST(hasSquareSum_Fermat, TestSAMPLE4, true, 2);
SIMPLE_TEST(hasSquareSum_Fermat, TestSAMPLE5, true, 1);
