#include "common_header.h"

#include "mathematics/arithmetics/modulo/modulo.h"

typedef int InputType;

INT_BOOL isDivisibleBy5Mod(const InputType n) {
    return n % 5 == 0;
}

INT_BOOL isDivisibleBy5LastDigit(const InputType n) {
    const auto last_digit = n % 10;
    return (last_digit == 0) or (last_digit == 5) or (last_digit == -5);
}

/** Is divisible by 5
 *
 * @reference   Check if a number is multiple of 5 without using / and % operators
 *              http://www.geeksforgeeks.org/check-if-a-number-is-multiple-of-5-without-using-and-operators/
 *
 * Given a positive number n, write a function isMultipleof5(int n)
 * that returns true if n is multiple of 5, otherwise false.
 * You are not allowed to use % and / operators.
*/
/** Repeatedly subtract 5 from n
 *
 * @reference   Check if a number is multiple of 5 without using / and % operators
 *              http://www.geeksforgeeks.org/check-if-a-number-is-multiple-of-5-without-using-and-operators/
 */
INT_BOOL isDivisibleBy5Subtraction(InputType n) {
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
 *              http://www.geeksforgeeks.org/check-if-a-number-is-multiple-of-5-without-using-and-operators/
 */
INT_BOOL isDivisibleBy5ToString(const InputType n) {
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
 *              http://www.geeksforgeeks.org/check-if-a-number-is-multiple-of-5-without-using-and-operators/
 *
 * A number n can be a multiple of 5 in two cases. When last digit of n is 5 or 10.
 * If last bit in binary equivalent of n is set (which can be the case when last digit is 5)
 * then we multiply by 2 using n<<=1 to make sure that if the number is multiple of 5 then
 * we have the last digit as 0. Once we do that, our work is to just check if the last digit
 * is 0 or not, which we can do using float and integer comparison trick.
 */
INT_BOOL isDivisibleBy5Float(const InputType n) {
    //Make it unsigned to prevent integer overflow error
    unsigned positive_n = n;
    if (n < 0) {
        positive_n = -n;
    }
    if (positive_n & 1) {
        positive_n <<= 1;
    }

    //Use static_cast<InputType> instead of std::floor() to avoid float accuracy issue
    const auto x = static_cast<InputType>(static_cast<double>(positive_n) * 0.1) * 10;

    if (x == positive_n) {
        return TRUE;
    } else {
        return FALSE;
    }
}

INT_BOOL isDivisibleBy5LastDigitStrict(const InputType n) {
    const auto last_digit = Mod10Float(n);
    return (last_digit == 0) or (last_digit == 5) or (last_digit == -5);
}

const InputType LOWER = INT_MIN;
const InputType UPPER = INT_MAX;
const InputType SAMPLE1 = -4;
const InputType SAMPLE2 = -40;
const InputType SAMPLE3 = 189;
const InputType SAMPLE4 = 2600;

SIMPLE_BENCHMARK(isDivisibleBy5Mod, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5Mod, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5Mod, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5Mod, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5Mod, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5Mod, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy5Mod, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy5Mod, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5Mod, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5Mod, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5Mod, TestSAMPLE4, TRUE, SAMPLE4);

SIMPLE_BENCHMARK(isDivisibleBy5LastDigit, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5LastDigit, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5LastDigit, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5LastDigit, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5LastDigit, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5LastDigit, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy5LastDigit, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy5LastDigit, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5LastDigit, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5LastDigit, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5LastDigit, TestSAMPLE4, TRUE, SAMPLE4);
SIMPLE_TEST(isDivisibleBy5LastDigit, TestSAMPLE5, TRUE, -970991465);

MUTUAL_RANDOM_TEST(isDivisibleBy5Mod, isDivisibleBy5LastDigit, LOWER, UPPER);

SIMPLE_BENCHMARK(isDivisibleBy5Subtraction, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5Subtraction, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5Subtraction, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5Subtraction, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5Subtraction, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5Subtraction, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy5Subtraction, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy5Subtraction, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5Subtraction, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5Subtraction, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5Subtraction, TestSAMPLE4, TRUE, SAMPLE4);

SIMPLE_BENCHMARK(isDivisibleBy5ToString, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5ToString, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5ToString, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5ToString, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5ToString, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5ToString, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy5ToString, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy5ToString, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5ToString, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5ToString, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5ToString, TestSAMPLE4, TRUE, SAMPLE4);

SIMPLE_BENCHMARK(isDivisibleBy5Float, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5Float, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5Float, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5Float, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5Float, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5Float, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy5Float, TestLOWERPlusOne, FALSE, LOWER + 1);
SIMPLE_TEST(isDivisibleBy5Float, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy5Float, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5Float, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5Float, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5Float, TestSAMPLE4, TRUE, SAMPLE4);
SIMPLE_TEST(isDivisibleBy5Float, TestSAMPLE5, TRUE, -1082066345);

MUTUAL_RANDOM_TEST(isDivisibleBy5Mod, isDivisibleBy5Subtraction, LOWER, UPPER);
MUTUAL_RANDOM_TEST(isDivisibleBy5Mod, isDivisibleBy5ToString, LOWER, UPPER);
MUTUAL_RANDOM_TEST(isDivisibleBy5Mod, isDivisibleBy5Float, LOWER, UPPER);

SIMPLE_BENCHMARK(isDivisibleBy5LastDigitStrict, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5LastDigitStrict, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5LastDigitStrict, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5LastDigitStrict, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5LastDigitStrict, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5LastDigitStrict, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy5LastDigitStrict, TestLOWERPlusOne, FALSE, LOWER + 1);
SIMPLE_TEST(isDivisibleBy5LastDigitStrict, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy5LastDigitStrict, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5LastDigitStrict, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5LastDigitStrict, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5LastDigitStrict, TestSAMPLE4, TRUE, SAMPLE4);
SIMPLE_TEST(isDivisibleBy5LastDigitStrict, TestSAMPLE5, TRUE, -1082066345);

MUTUAL_RANDOM_TEST(isDivisibleBy5Mod, isDivisibleBy5LastDigitStrict, LOWER, UPPER);
