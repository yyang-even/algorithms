#include "common_header.h"

typedef int InputType;

/** Is divisible by 3
 *
 * @reference   Write an Efficient Method to Check if a Number is Multiple of 3
 * http://www.geeksforgeeks.org/write-an-efficient-method-to-check-if-a-number-is-multiple-of-3/
 *
 * There is a pattern in binary representation of the number that can be used to find if number is a multiple of 3.
 * If difference between count of odd set bits (Bits set at odd positions) and even set bits is multiple of 3 then is the number.
 */
INT_BOOL isDivisibleBy3(InputType num) {
    if (num < 0) {
        num = -num;
    }
    if (num == 0) {
        return TRUE;
    }
    if (num == 1) {
        return FALSE;
    }

    int even_odd_diff = 0;
    while (num) {
        if (num & 1) {
            ++even_odd_diff;
        }
        num >>= 1;

        if (num & 1) {
            --even_odd_diff;
        }
        num >>= 1;
    }

    return isDivisibleBy3(even_odd_diff);
}


const InputType LOWER = 2;
const InputType UPPER = INT_MAX;

SIMPLE_BENCHMARK(isDivisibleBy3, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy3, UPPER);
RANDOM_BENCHMARK(isDivisibleBy3, LOWER, UPPER);

SIMPLE_TEST(isDivisibleBy3, TestLOWER, FALSE, LOWER);
SIMPLE_TEST(isDivisibleBy3, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(isDivisibleBy3, TestSAMPLE1, TRUE, 612);
SIMPLE_TEST(isDivisibleBy3, TestSAMPLE2, TRUE, 3);
SIMPLE_TEST(isDivisibleBy3, TestSAMPLE3, FALSE, 610);
SIMPLE_TEST(isDivisibleBy3, TestSAMPLE4, TRUE, -612);
SIMPLE_TEST(isDivisibleBy3, TestSAMPLE5, FALSE, -610);
