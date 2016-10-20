#include "common_header.h"

typedef int InputType;

/**Is divisible by 11
 *
 * @reference   Grade 7:  The Learning Equation Math
 *              11.04 Divisibility Rules
 *              http://staff.argyll.epsb.ca/jreed/math7/strand1/1104.htm
 *
 * The (sum of the odd numbered digits) - (sum of the even numbered digits) is divisible by 11.
 */
INT_BOOL isDivisibleBy11(int num) {
    if (num < 0) {
        num = -num;
    }
    if (num == 0 || num == 11) {
        return TRUE;
    }
    if (num < 22) {
        return FALSE;
    }

    bool positive = true;
    int last_digit, next_n;
    int even_odd_diff = 0;
    while (num) {
        next_n = num / 10;
        last_digit = num - next_n * 10;
        if (positive) {
            even_odd_diff += last_digit;
        } else {
            even_odd_diff -= last_digit;
        }
        positive = !positive;
        num = next_n;
    }

    return isDivisibleBy11(even_odd_diff);
}

const InputType LOWER = INT_MIN;
const InputType UPPER = INT_MAX;
const InputType SAMPLE1 = -120;
const InputType SAMPLE2 = -121;
const InputType SAMPLE3 = 60;
const InputType SAMPLE4 = 6600;

SIMPLE_BENCHMARK(isDivisibleBy11, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy11, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy11, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy11, SAMPLE4);
RANDOM_BENCHMARK(isDivisibleBy11, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy11, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy11, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy11, TestSAMPLE1, FALSE, SAMPLE1);
SIMPLE_TEST(isDivisibleBy11, TestSAMPLE2, TRUE, SAMPLE2);
SIMPLE_TEST(isDivisibleBy11, TestSAMPLE3, FALSE, SAMPLE3);
SIMPLE_TEST(isDivisibleBy11, TestSAMPLE4, TRUE, SAMPLE4);
SIMPLE_TEST(isDivisibleBy11, TestSAMPLE5, TRUE, 0);
