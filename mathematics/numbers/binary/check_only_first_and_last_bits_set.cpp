#include "common_header.h"

#include "is_power_of_2.h"

/** Check whether the number has only first and last bits set
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-number-first-last-bits-set/
 * @reference   Check whether the number has only first and last bits set | Set 2
 *              https://www.geeksforgeeks.org/check-whether-the-number-has-only-first-and-last-bits-set-set-2/
 *
 * Given a positive integer n. The problem is to check whether only the
 * first and last bits are set in the binary representation of n.
 */
INT_BOOL CheckIfOnlyFirstAndLastBitsSet(const unsigned n) {
    if (n == 1) {
        return true;
    } else if (n == 2) {
        return false;
    } else {
        return IsPowerOf2(n - 1);
    }
}


SIMPLE_BENCHMARK(CheckIfOnlyFirstAndLastBitsSet, std::numeric_limits<unsigned>::max());

SIMPLE_TEST(CheckIfOnlyFirstAndLastBitsSet, TestSample1, TRUE, 1);
SIMPLE_TEST(CheckIfOnlyFirstAndLastBitsSet, TestSample2, FALSE, 0);
SIMPLE_TEST(CheckIfOnlyFirstAndLastBitsSet, TestSample3, TRUE, 9);
SIMPLE_TEST(CheckIfOnlyFirstAndLastBitsSet, TestSample4, FALSE, 2);
SIMPLE_TEST(CheckIfOnlyFirstAndLastBitsSet, TestSample5, FALSE, 15);
