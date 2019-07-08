#include "common_header.h"

#include "mathematics/arithmetics/modulo/modulo.h"


namespace {

typedef int InputType;

/** Is divisible by 7
 * @reference   Check divisibility by 7
 *              https://www.geeksforgeeks.org/divisibility-by-7/
 *
 * Given a number, check if it is divisible by 7.
 * You are not allowed to use modulo operator,
 * floating point arithmetic is also not allowed.
 */

/**
 * @reference   Grade 7:  The Learning Equation Math
 *              11.04 Divisibility Rules
 *              https://staff.argyll.epsb.ca/jreed/math7/strand1/1104.htm
 *
 * To find out if a number is divisible by seven, take the last digit, double it,
 * and subtract it from the rest of the number. If you get an answer divisible by 7
 * (including zero), then the original number is divisible by seven. If you don't
 * know the new number's divisibility, you can apply the rule again.
 *
 * Example:  Check to see if 203 is divisible by 7.
 *
 *  double the last digit: 3 x 2 = 6
 *  subtract that from the rest of the number: 20 - 6 = 14.
 *  check to see if the difference is divisible by 7: 14 is divisible by 7,
 *      therefore 203 is also divisible by 7.
 */
INT_BOOL isDivisibleBy7(InputType num) {
    if (num < 0) {
        num = -num;
    }

    if (num == 0 || num == 7) {
        return TRUE;
    }
    if (num < 14) {
        return FALSE;
    }

    return isDivisibleBy7(num / 10 - 2 * Mod10(num));
}

}//namespace


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();


SIMPLE_BENCHMARK(isDivisibleBy7, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy7, UPPER);
RANDOM_BENCHMARK(isDivisibleBy7, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy7, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy7, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy7, TestSAMPLE1, TRUE, 203);
SIMPLE_TEST(isDivisibleBy7, TestSAMPLE2, TRUE, 7);
SIMPLE_TEST(isDivisibleBy7, TestSAMPLE3, FALSE, 200);
SIMPLE_TEST(isDivisibleBy7, TestSAMPLE4, TRUE, -203);
SIMPLE_TEST(isDivisibleBy7, TestSAMPLE5, FALSE, -200);
