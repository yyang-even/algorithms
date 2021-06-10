#include "common_header.h"

#include "calculate_xor_of_all_numbers_1_to_n.h"


namespace {

/** Check if n is divisible by power of 2 without using arithmetic operators
 *
 * @reference   https://www.geeksforgeeks.org/check-n-divisible-power-2-without-using-arithmetic-operators/
 *
 * Given two positive integers n and m. The problem is to check whether n is divisible
 * by 2^m or not.
 */
constexpr inline auto
IsDivisibleByPowerOf2_Arithmetic(const unsigned n, const unsigned m) {
    return not(n & ((1 << m) - 1));
}


constexpr inline auto
IsDivisibleByPowerOf2_Bitwise(const unsigned n, const unsigned m) {
    return ((n >> m) << m) == n;
}


/** Check if a number is divisible by 8 using bitwise operators
 *
 * @reference   https://www.geeksforgeeks.org/check-number-divisible-8-using-bitwise-operators/
 *
 * Given a number n, check if it is divisible by 8 using bitwise operators.
 */
constexpr inline auto IsDivisibleBy8(const unsigned num) {
    return IsDivisibleByPowerOf2_Bitwise(num, 3);
}


/** Multiples of 4 (An Interesting Method)
 *
 * @reference   https://www.geeksforgeeks.org/multiples-4-interesting-method/
 *
 * Given a number n, the task is to check whether this number is a multiple of 4 or not
 * without using +, -, * ,/ and % operators.
 */
constexpr inline auto IsMultipleOf4_Xor(const unsigned num) {
    if (num == 1) {
        return false;
    }
    return XorOfAllFrom1toN(num) == num;
}


constexpr inline auto IsMultipleOf4_Shift(const unsigned num) {
    return IsDivisibleByPowerOf2_Bitwise(num, 2);
}


/** Efficiently check whether n is a multiple of 4 or not
 *
 * @reference   https://www.geeksforgeeks.org/efficiently-check-whether-n-multiple-4-not/
 *
 * Given a number n. The problem is to efficiently check whether n is a multiple of 4 or
 * not without using arithmetic operators.
 */
constexpr inline auto IsMultipleOf4_Mask(const unsigned num) {
    return IsDivisibleByPowerOf2_Arithmetic(num, 2);
}


/** Check whether a given number is even or odd
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-given-number-even-odd/
 * @reference   Check a number is odd or even without modulus operator
 *              https://www.geeksforgeeks.org/3-ways-check-number-odd-even-without-using-modulus-operator-set-2-can-merge-httpswww-geeksforgeeks-orgcheck-whether-given-number-even-odd/
 * @reference   TCS Coding Practice Question | Check Odd or Even
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-check-odd-or-even/
 * @reference   Check if a Number is Odd or Even using Bitwise Operators
 *              https://www.geeksforgeeks.org/check-if-a-number-is-odd-or-even-using-bitwise-operators/
 *
 * Given a number, check whether it is even or odd.
 */
constexpr inline auto IsEven(const unsigned num) {
    return IsDivisibleByPowerOf2_Arithmetic(num, 1);
}


/**
 * @reference   Check if an Octal number is Even or Odd
 *              https://www.geeksforgeeks.org/check-if-an-octal-number-is-even-or-odd/
 */


/**
 * @reference   Check if a HexaDecimal number is Even or Odd
 *              https://www.geeksforgeeks.org/check-if-a-hexadecimal-number-is-even-or-odd/
 */

}//namespace


constexpr auto LOWER = std::numeric_limits<unsigned>::min();
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


THE_BENCHMARK(IsDivisibleByPowerOf2_Arithmetic, 8, 2);

SIMPLE_TEST(IsDivisibleByPowerOf2_Arithmetic, TestSample1, true, 0, 2);
SIMPLE_TEST(IsDivisibleByPowerOf2_Arithmetic, TestSample2, true, 8, 2);
SIMPLE_TEST(IsDivisibleByPowerOf2_Arithmetic, TestSample3, false, 14, 3);


THE_BENCHMARK(IsDivisibleByPowerOf2_Bitwise, 8, 2);

SIMPLE_TEST(IsDivisibleByPowerOf2_Bitwise, TestSample1, true, 0, 2);
SIMPLE_TEST(IsDivisibleByPowerOf2_Bitwise, TestSample2, true, 8, 2);
SIMPLE_TEST(IsDivisibleByPowerOf2_Bitwise, TestSample3, false, 14, 3);


THE_BENCHMARK(IsDivisibleBy8, 8);

SIMPLE_TEST(IsDivisibleBy8, TestSample1, true, 0);
SIMPLE_TEST(IsDivisibleBy8, TestSample2, true, 8);
SIMPLE_TEST(IsDivisibleBy8, TestSample3, false, 14);
SIMPLE_TEST(IsDivisibleBy8, TestSample4, false, 15);
SIMPLE_TEST(IsDivisibleBy8, TestSample5, true, 16);


THE_BENCHMARK(IsMultipleOf4_Xor, 4);

SIMPLE_TEST(IsMultipleOf4_Xor, TestSample1, true, 0);
SIMPLE_TEST(IsMultipleOf4_Xor, TestSample2, false, 1);
SIMPLE_TEST(IsMultipleOf4_Xor, TestSample3, true, 16);
SIMPLE_TEST(IsMultipleOf4_Xor, TestSample4, false, 14);


THE_BENCHMARK(IsMultipleOf4_Mask, 4);

SIMPLE_TEST(IsMultipleOf4_Mask, TestSample1, true, 0);
SIMPLE_TEST(IsMultipleOf4_Mask, TestSample2, false, 1);
SIMPLE_TEST(IsMultipleOf4_Mask, TestSample3, true, 16);
SIMPLE_TEST(IsMultipleOf4_Mask, TestSample4, false, 14);


THE_BENCHMARK(IsMultipleOf4_Shift, 4);

SIMPLE_TEST(IsMultipleOf4_Shift, TestSample1, true, 0);
SIMPLE_TEST(IsMultipleOf4_Shift, TestSample2, false, 1);
SIMPLE_TEST(IsMultipleOf4_Shift, TestSample3, true, 16);
SIMPLE_TEST(IsMultipleOf4_Shift, TestSample4, false, 14);

MUTUAL_RANDOM_TEST(IsMultipleOf4_Xor, IsMultipleOf4_Mask, LOWER, UPPER);
MUTUAL_RANDOM_TEST(IsMultipleOf4_Shift, IsMultipleOf4_Mask, LOWER, UPPER);


THE_BENCHMARK(IsEven, 8);

SIMPLE_TEST(IsEven, TestSample1, true, 0);
SIMPLE_TEST(IsEven, TestSample2, true, 2);
SIMPLE_TEST(IsEven, TestSample3, false, 5);
SIMPLE_TEST(IsEven, TestSample4, false, 101);
