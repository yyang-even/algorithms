#include "common_header.h"

#include "perfect_square.h"


namespace {

/** Check if a number is perfect square without finding square root
 *
 * @reference   https://www.geeksforgeeks.org/check-if-a-number-is-perfect-square-without-finding-square-root/
 */
auto IsPerfectSquare_Multiply(const unsigned x) {
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
auto IsPerfectSquare_Sum(const unsigned x) {
    for (unsigned sum = 0, i = 1; sum < x; i += 2) {
        sum += i;
        if (sum == x) {
            return true;
        }
    }

    return false;
}

}//namespace


SIMPLE_BENCHMARK(IsPerfectSquare, 2500);

SIMPLE_TEST(IsPerfectSquare, TestSAMPLE1, true, 2500);
SIMPLE_TEST(IsPerfectSquare, TestSAMPLE2, false, 2555);


SIMPLE_BENCHMARK(IsPerfectSquare_Multiply, 2500);

SIMPLE_TEST(IsPerfectSquare_Multiply, TestSAMPLE1, true, 2500);
SIMPLE_TEST(IsPerfectSquare_Multiply, TestSAMPLE2, false, 2555);


SIMPLE_BENCHMARK(IsPerfectSquare_Sum, 2500);

SIMPLE_TEST(IsPerfectSquare_Sum, TestSAMPLE1, true, 2500);
SIMPLE_TEST(IsPerfectSquare_Sum, TestSAMPLE2, false, 2555);
