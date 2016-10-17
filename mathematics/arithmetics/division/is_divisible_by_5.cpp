#include "common_header.h"

typedef int InputType;

bool isDivisibleBy5Mod(const InputType n) {
    return n % 5 == 0;
}

bool isDivisibleBy5LastDigit(const InputType n) {
    const auto last_digit = n % 10;
    return (last_digit == 0) or (last_digit == 5);
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
bool isDivisibleBy5Subtraction(InputType n) {
    if (n < 0) {
        n = -n;
    }
    while (n > 0) {
        n -= 5;
    }

    if (n == 0) {
        return true;
    } else {
        return false;
    }
}

/** Convert to string and check the last character
 *
 * @reference   Check if a number is multiple of 5 without using / and % operators
 *              http://www.geeksforgeeks.org/check-if-a-number-is-multiple-of-5-without-using-and-operators/
 */
bool isDivisibleBy5ToString(const InputType n) {
    const auto str_n = std::to_string(n);
    if (str_n.back() == '0' || str_n.back() == '5') {
        return true;
    } else {
        return false;
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
bool isDivisibleBy5Float(const InputType n) {
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
        return true;
    } else {
        return false;
    }
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

SIMPLE_TEST(isDivisibleBy5Mod, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy5Mod, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy5Mod, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5Mod, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5Mod, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5Mod, TestSAMPLE4, true, SAMPLE4);

SIMPLE_BENCHMARK(isDivisibleBy5LastDigit, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5LastDigit, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5LastDigit, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5LastDigit, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5LastDigit, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5LastDigit, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy5LastDigit, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy5LastDigit, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5LastDigit, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5LastDigit, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5LastDigit, TestSAMPLE4, true, SAMPLE4);

MUTUAL_RANDOM_TEST(isDivisibleBy5Mod, isDivisibleBy5LastDigit, LOWER, UPPER);

SIMPLE_BENCHMARK(isDivisibleBy5Subtraction, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5Subtraction, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5Subtraction, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5Subtraction, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5Subtraction, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5Subtraction, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy5Subtraction, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy5Subtraction, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5Subtraction, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5Subtraction, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5Subtraction, TestSAMPLE4, true, SAMPLE4);

SIMPLE_BENCHMARK(isDivisibleBy5ToString, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5ToString, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5ToString, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5ToString, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5ToString, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5ToString, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy5ToString, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy5ToString, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5ToString, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5ToString, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5ToString, TestSAMPLE4, true, SAMPLE4);

SIMPLE_BENCHMARK(isDivisibleBy5Float, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5Float, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5Float, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy5Float, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy5Float, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy5Float, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy5Float, TestLOWERPlusOne, false, LOWER + 1);
SIMPLE_TEST(isDivisibleBy5Float, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy5Float, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5Float, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5Float, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5Float, TestSAMPLE4, true, SAMPLE4);
SIMPLE_TEST(isDivisibleBy5Float, TestSAMPLE5, true, -1082066345);

MUTUAL_RANDOM_TEST(isDivisibleBy5Mod, isDivisibleBy5Subtraction, LOWER, UPPER);
MUTUAL_RANDOM_TEST(isDivisibleBy5Mod, isDivisibleBy5ToString, LOWER, UPPER);
MUTUAL_RANDOM_TEST(isDivisibleBy5Mod, isDivisibleBy5Float, LOWER, UPPER);
