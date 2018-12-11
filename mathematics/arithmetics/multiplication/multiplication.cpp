#include "common_header.h"

/** Multiply two integers without using multiplication, division and bitwise operators, and no loops
 *
 * @reference   https://www.geeksforgeeks.org/multiply-two-numbers-without-using-multiply-division-bitwise-operators-and-no-loops/
 *
 * By making use of recursion, we can multiply two integers with the given constraints.
 */
auto MultiplyHelper(const int x, const int y) {
    if (y == 0) {
        return 0;
    } else if (y > 0) {
        return x + MultiplyHelper(x, y - 1);
    } else {
        return -MultiplyHelper(x, -y);
    }
}
auto Multiply(int x, int y) {
    if (abs(x) < abs(y)) {
        std::swap(x, y);
    }
    return MultiplyHelper(x, y);
}


SIMPLE_BENCHMARK(MultiplyHelper, 3, 4);

SIMPLE_TEST(MultiplyHelper, TestSAMPLE1, -55, 5, -11);
SIMPLE_TEST(MultiplyHelper, TestSAMPLE2, -55, -5, 11);
SIMPLE_TEST(MultiplyHelper, TestSAMPLE3, 55, 5, 11);
SIMPLE_TEST(MultiplyHelper, TestSAMPLE4, 55, -5, -11);
