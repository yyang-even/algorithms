#include "common_header.h"

#include "mathematics/arithmetics/modulo/modulo.h"

namespace {

typedef int InputType;

/** Multiply the given number by 2 such that it is divisible by 10
 *
 * @reference   https://www.geeksforgeeks.org/multiply-the-given-number-by-2-such-that-it-is-divisible-by-10/
 *
 * Given a number, the only operation allowed is to multiply the number by 2.
 * Calculate the minimum number of operations to make the number divisible by 10.
 * NOTE: If it is not possible to convert then print -1.
 */

INT_BOOL isDivisibleBy5_Mod(const InputType n) {
    return n % 5 == 0;
}


INT_BOOL isDivisibleBy5_LastDigit(const InputType n) {
    const auto last_digit = n % 10;
    return (last_digit == 0) or (last_digit == 5) or (last_digit == -5);
}


/** Is divisible by 5
 *
 * @reference   Check if a number is multiple of 5 without using / and % operators
 *              https://www.geeksforgeeks.org/check-if-a-number-is-multiple-of-5-without-using-and-operators/
 *
 * Given a positive number n, write a function isMultipleof5(int n)
 * that returns true if n is multiple of 5, otherwise false.
 * You are not allowed to use % and / operators.
*/
/** Repeatedly subtract 5 from n
 *
 * @reference   Check if a number is multiple of 5 without using / and % operators
 *              https://www.geeksforgeeks.org/check-if-a-number-is-multiple-of-5-without-using-and-operators/
 */
INT_BOOL isDivisibleBy5_Subtraction(InputType n) {
    if (n < 0) {
        n = -n;
    }
    while (n > 0) {
        n -= 5;
    }

    if (n == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}


/** Convert to string and check the last character
 *
 * @reference   Check if a number is multiple of 5 without using / and % operators
 *              https://www.geeksforgeeks.org/check-if-a-number-is-multiple-of-5-without-using-and-operators/
 */
INT_BOOL isDivisibleBy5_ToString(const InputType n) {
    const auto str_n = std::to_string(n);
    if (str_n.back() == '0' || str_n.back() == '5') {
        return TRUE;
    } else {
        return FALSE;
    }
}


/** Set last digit as 0 and use floating point trick
 *
 * @reference   Check if a number is multiple of 5 without using / and % operators
 *              https://www.geeksforgeeks.org/check-if-a-number-is-multiple-of-5-without-using-and-operators/
 *
 * A number n can be a multiple of 5 in two cases. When last digit of n is 5 or 10.
 * If last bit in binary equivalent of n is set (which can be the case when last digit is 5)
 * then we multiply by 2 using n<<=1 to make sure that if the number is multiple of 5 then
 * we have the last digit as 0. Once we do that, our work is to just check if the last digit
 * is 0 or not, which we can do using float and integer comparison trick.
 */
INT_BOOL isDivisibleBy5_Float(const InputType n) {
    //Make it unsigned to prevent integer overflow error
    unsigned positive_n = n;
    if (n < 0) {
        positive_n = -n;
    }
    if (positive_n & 1) {
        positive_n <<= 1;
    }

    //Use static_cast<unsigned> instead of std::floor() to avoid float accuracy issue
    const auto x = static_cast<unsigned>(static_cast<double>(positive_n) * 0.1) * 10;

    if (x == positive_n) {
        return TRUE;
    } else {
        return FALSE;
    }
}


INT_BOOL isDivisibleBy5_LastDigitStrict(const InputType n) {
    const auto last_digit = Mod10_Float(n);
    return (last_digit == 0) or (last_digit == 5) or (last_digit == -5);
}

}//namespace


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();
constexpr InputType SAMPLE1 = -4;
constexpr InputType SAMPLE2 = -40;
constexpr InputType SAMPLE3 = 189;
constexpr InputType SAMPLE4 = 2600;


SIMPLE_BENCHMARK(isDivisibleBy5_Mod, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5_Mod, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5_Mod, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5_Mod, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5_Mod, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5_Mod, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy5_Mod, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy5_Mod, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5_Mod, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5_Mod, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5_Mod, TestSAMPLE4, TRUE, SAMPLE4);


SIMPLE_BENCHMARK(isDivisibleBy5_LastDigit, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5_LastDigit, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5_LastDigit, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5_LastDigit, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5_LastDigit, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5_LastDigit, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy5_LastDigit, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy5_LastDigit, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5_LastDigit, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5_LastDigit, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5_LastDigit, TestSAMPLE4, TRUE, SAMPLE4);
SIMPLE_TEST(isDivisibleBy5_LastDigit, TestSAMPLE5, TRUE, -970991465);

MUTUAL_RANDOM_TEST(isDivisibleBy5_Mod, isDivisibleBy5_LastDigit, LOWER, UPPER);


SIMPLE_BENCHMARK(isDivisibleBy5_Subtraction, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5_Subtraction, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5_Subtraction, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5_Subtraction, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5_Subtraction, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5_Subtraction, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy5_Subtraction, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy5_Subtraction, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5_Subtraction, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5_Subtraction, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5_Subtraction, TestSAMPLE4, TRUE, SAMPLE4);


SIMPLE_BENCHMARK(isDivisibleBy5_ToString, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5_ToString, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5_ToString, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5_ToString, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5_ToString, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5_ToString, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy5_ToString, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy5_ToString, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5_ToString, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5_ToString, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5_ToString, TestSAMPLE4, TRUE, SAMPLE4);


SIMPLE_BENCHMARK(isDivisibleBy5_Float, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5_Float, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5_Float, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5_Float, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5_Float, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5_Float, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy5_Float, TestLOWERPlusOne, FALSE, LOWER + 1);
SIMPLE_TEST(isDivisibleBy5_Float, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy5_Float, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5_Float, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5_Float, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5_Float, TestSAMPLE4, TRUE, SAMPLE4);
SIMPLE_TEST(isDivisibleBy5_Float, TestSAMPLE5, TRUE, -1082066345);

MUTUAL_RANDOM_TEST(isDivisibleBy5_Mod, isDivisibleBy5_Subtraction, LOWER, UPPER);
MUTUAL_RANDOM_TEST(isDivisibleBy5_Mod, isDivisibleBy5_ToString, LOWER, UPPER);
MUTUAL_RANDOM_TEST(isDivisibleBy5_Mod, isDivisibleBy5_Float, LOWER, UPPER);


SIMPLE_BENCHMARK(isDivisibleBy5_LastDigitStrict, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5_LastDigitStrict, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5_LastDigitStrict, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5_LastDigitStrict, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5_LastDigitStrict, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestLOWERPlusOne, FALSE, LOWER + 1);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestSAMPLE4, TRUE, SAMPLE4);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestSAMPLE5, TRUE, -1082066345);

MUTUAL_RANDOM_TEST(isDivisibleBy5_Mod, isDivisibleBy5_LastDigitStrict, LOWER, UPPER);
