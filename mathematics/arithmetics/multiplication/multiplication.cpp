#include "common_header.h"

#include "mathematics/arithmetics/subtract/negate.h"
#include "mathematics/numbers/binary/abs.h"
#include "multiplication.h"


namespace {

/** Multiply two integers without using multiplication, division and bitwise operators, and no loops
 *
 * @reference   https://www.geeksforgeeks.org/multiply-two-numbers-without-using-multiply-division-bitwise-operators-and-no-loops/
 * @reference   Product of 2 Numbers using Recursion
 *              https://www.geeksforgeeks.org/product-2-numbers-using-recursion/
 * @reference   Product of 2 numbers using recursion | Set 2
 *              https://www.geeksforgeeks.org/product-of-2-numbers-using-recursion-set-2/
 *
 * By making use of recursion, we can multiply two integers with the given constraints.
 */
inline constexpr auto Multiply_Recursive_Helper(const int x, const int y) {
    if (y == 0) {
        return 0;
    } else if (y > 0) {
        return x + Multiply_Recursive_Helper(x, y - 1);
    } else {
        return -Multiply_Recursive_Helper(x, -y);
    }
}

inline constexpr auto Multiply_Recursive(int x, int y) {
    if (abs(x) < abs(y)) {
        std::swap(x, y);
    }
    return Multiply_Recursive_Helper(x, y);
}


constexpr int Multiply_Plus(const int x, const int y) {
    const auto abs_x = Abs_Count(x);
    const auto abs_y = Abs_Count(y);

    auto counter = y;
    auto delta = x;
    if (abs_x < abs_y) {
        std::swap(counter, delta);
    }

    int sum = 0;
    const auto abs_counter = Abs_Count(counter);
    for (int i = 0; i++ < abs_counter;) {
        sum += delta;
    }

    return counter < 0 ? Negate(sum) : sum;
}


/** Multiply any Number with 4 using Bitwise Operator
 *
 * @reference   https://www.geeksforgeeks.org/multiply-number-4-using-bitwise-operator/
 * @reference   Multiplication with a power of 2
 *              https://www.geeksforgeeks.org/multiplication-power-2/
 */

} //namespace


THE_BENCHMARK(Multiply_Recursive, 3, 4);

SIMPLE_TEST(Multiply_Recursive, TestSAMPLE1, -55, 5, -11);
SIMPLE_TEST(Multiply_Recursive, TestSAMPLE2, -55, -5, 11);
SIMPLE_TEST(Multiply_Recursive, TestSAMPLE3, 55, 5, 11);
SIMPLE_TEST(Multiply_Recursive, TestSAMPLE4, 55, -5, -11);


THE_BENCHMARK(Multiply_RussianPeasant, 3, 4);

SIMPLE_TEST(Multiply_RussianPeasant, TestSAMPLE1, 55, 5, 11);
SIMPLE_TEST(Multiply_RussianPeasant, TestSAMPLE2, 18, 18, 1);
SIMPLE_TEST(Multiply_RussianPeasant, TestSAMPLE3, 240, 12, 20);
SIMPLE_TEST(Multiply_RussianPeasant, TestSAMPLE4, 0, 0, 20);
SIMPLE_TEST(Multiply_RussianPeasant, TestSAMPLE5, 0, 5, 0);
SIMPLE_TEST(Multiply_RussianPeasant, TestSAMPLE6, 40, 5, 8);


THE_BENCHMARK(Multiply_Plus, 3, 4);

SIMPLE_TEST(Multiply_Plus, TestSAMPLE1, -55, 5, -11);
SIMPLE_TEST(Multiply_Plus, TestSAMPLE2, -55, -5, 11);
SIMPLE_TEST(Multiply_Plus, TestSAMPLE3, 55, 5, 11);
SIMPLE_TEST(Multiply_Plus, TestSAMPLE4, 55, -5, -11);
