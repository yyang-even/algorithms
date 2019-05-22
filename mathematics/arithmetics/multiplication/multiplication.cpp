#include "common_header.h"

#include "multiplication.h"

namespace {

/** Multiply two integers without using multiplication, division and bitwise operators, and no loops
 *
 * @reference   https://www.geeksforgeeks.org/multiply-two-numbers-without-using-multiply-division-bitwise-operators-and-no-loops/
 *
 * By making use of recursion, we can multiply two integers with the given constraints.
 */
auto Multiply_Recursive_Helper(const int x, const int y) {
    if (y == 0) {
        return 0;
    } else if (y > 0) {
        return x + Multiply_Recursive_Helper(x, y - 1);
    } else {
        return -Multiply_Recursive_Helper(x, -y);
    }
}
auto Multiply_Recursive(int x, int y) {
    if (abs(x) < abs(y)) {
        std::swap(x, y);
    }
    return Multiply_Recursive_Helper(x, y);
}

}//namespace


SIMPLE_BENCHMARK(Multiply_Recursive, 3, 4);

SIMPLE_TEST(Multiply_Recursive, TestSAMPLE1, -55, 5, -11);
SIMPLE_TEST(Multiply_Recursive, TestSAMPLE2, -55, -5, 11);
SIMPLE_TEST(Multiply_Recursive, TestSAMPLE3, 55, 5, 11);
SIMPLE_TEST(Multiply_Recursive, TestSAMPLE4, 55, -5, -11);


SIMPLE_BENCHMARK(Multiply_RussianPeasant, 3, 4);

SIMPLE_TEST(Multiply_RussianPeasant, TestSAMPLE1, 55u, 5, 11);
SIMPLE_TEST(Multiply_RussianPeasant, TestSAMPLE2, 18u, 18, 1);
SIMPLE_TEST(Multiply_RussianPeasant, TestSAMPLE3, 240u, 12, 20);
SIMPLE_TEST(Multiply_RussianPeasant, TestSAMPLE4, 0u, 0, 20);
SIMPLE_TEST(Multiply_RussianPeasant, TestSAMPLE5, 0u, 5, 0);
SIMPLE_TEST(Multiply_RussianPeasant, TestSAMPLE6, 40u, 5, 8);
