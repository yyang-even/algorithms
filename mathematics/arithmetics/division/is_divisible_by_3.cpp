#include "common_header.h"

#include "divisibility.h"

typedef int InputType;

/** Is divisible by 3
 *
 * @reference   Write an Efficient Method to Check if a Number is Multiple of 3
 * http://www.geeksforgeeks.org/write-an-efficient-method-to-check-if-a-number-is-multiple-of-3/
 *
 * There is a pattern in binary representation of the number that can be used to find if number is a multiple of 3.
 * If difference between count of odd set bits (Bits set at odd positions) and even set bits is multiple of 3 then is the number.
 */
bool isMultipleOf3(int num) {
    if (num < 0) {
        num = -num;
    }
    if (num == 0) {
        return true;
    }
    if (num == 1) {
        return false;
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

    return isMultipleOf3(even_odd_diff);
}


const int LOWER = 2;
const int UPPER = INT_MAX;

SIMPLE_BENCHMARK(isMultipleOf3, LOWER);
SIMPLE_BENCHMARK(isMultipleOf3, UPPER);
RANDOM_BENCHMARK(isMultipleOf3, LOWER, UPPER);

SIMPLE_TEST(isMultipleOf3, TestLOWER, false, LOWER);
SIMPLE_TEST(isMultipleOf3, TestUPPER, false, UPPER);
SIMPLE_TEST(isMultipleOf3, TestSAMPLE1, true, 612);
SIMPLE_TEST(isMultipleOf3, TestSAMPLE2, true, 3);
