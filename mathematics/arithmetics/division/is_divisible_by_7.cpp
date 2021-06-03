#include "common_header.h"

#include "mathematics/arithmetics/modulo/modulo.h"


namespace {

/** Is divisible by 7
 *
 * @reference   Check divisibility by 7
 *              https://www.geeksforgeeks.org/divisibility-by-7/
 *
 * Given a number, check if it is divisible by 7. You are not allowed to use modulo
 * operator, floating point arithmetic is also not allowed.
 */

/**
 * @reference   Grade 7:  The Learning Equation Math
 *              11.04 Divisibility Rules
 *              http://staff.argyll.epsb.ca/jreed/math7/strand1/1104.htm
 *
 * To find out if a number is divisible by seven, take the last digit, double it, and
 * subtract it from the rest of the number. If you get an answer divisible by 7
 * (including zero), then the original number is divisible by seven. If you don't know
 * the new number's divisibility, you can apply the rule again.
 *
 * Example:  Check to see if 203 is divisible by 7.
 *
 *  double the last digit: 3 x 2 = 6
 *  subtract that from the rest of the number: 20 - 6 = 14.
 *  check to see if the difference is divisible by 7: 14 is divisible by 7, therefore
 *  203 is also divisible by 7.
 */
constexpr auto isDivisibleBy7(int num) {
    if (num < 0) {
        num = -num;
    }

    if (num == 0 or num == 7) {
        return true;
    }
    if (num < 14) {
        return false;
    }

    return isDivisibleBy7(num / 10 - 2 * Mod10(num));
}


/**
 * @reference   Check if Decimal representation of an Octal number is divisible by 7
 *              https://www.geeksforgeeks.org/check-if-decimal-representation-of-an-octal-number-is-divisible-by-7/
 */
inline auto isOctalDivisibleBy7(const std::string_view octal) {
    const auto digits_sum = std::accumulate(octal.cbegin(), octal.cend(), 0,
    [](const auto & sum, const auto & digit) {
        return sum + digit - '0';
    });

    return digits_sum % 7 == 0;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<int>::min();
constexpr auto UPPER = std::numeric_limits<int>::max();


SIMPLE_BENCHMARK(isDivisibleBy7, Sample1, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy7, Sample2, UPPER);

SIMPLE_TEST(isDivisibleBy7, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy7, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy7, TestSAMPLE1, true, 203);
SIMPLE_TEST(isDivisibleBy7, TestSAMPLE2, true, 7);
SIMPLE_TEST(isDivisibleBy7, TestSAMPLE3, false, 200);
SIMPLE_TEST(isDivisibleBy7, TestSAMPLE4, true, -203);
SIMPLE_TEST(isDivisibleBy7, TestSAMPLE5, false, -200);


THE_BENCHMARK(isOctalDivisibleBy7, "112");

SIMPLE_TEST(isOctalDivisibleBy7, TestSAMPLE1, false, "112");
SIMPLE_TEST(isOctalDivisibleBy7, TestSAMPLE2, true, "25");
