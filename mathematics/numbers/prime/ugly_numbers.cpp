#include "common_header.h"


namespace {

/** Ugly Numbers
 *
 * @reference   https://www.geeksforgeeks.org/ugly-numbers/
 *
 * Ugly numbers are numbers whose only prime factors are 2, 3 or 5. The sequence
 * 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, … shows the first 11 ugly numbers.
 * By convention, 1 is included.
 * Given a number n, the task is to find nth Ugly number.
 */
auto NthUglyNumber(const unsigned N) {
    unsigned ugly_numbers[N] = {1};
    unsigned i2 = 0, i3 = 0, i5 = 0;
    unsigned next_multiple_of_2 = 2;
    unsigned next_multiple_of_3 = 3;
    unsigned next_multiple_of_5 = 5;
    auto next_ugly_no = ugly_numbers[0];

    for (unsigned i = 1; i < N; ++i) {
        next_ugly_no = std::min(next_multiple_of_2,
                                std::min(next_multiple_of_3, next_multiple_of_5));
        ugly_numbers[i] = next_ugly_no;
        if (next_ugly_no == next_multiple_of_2) {
            next_multiple_of_2 = ugly_numbers[++i2] * 2;
        }
        if (next_ugly_no == next_multiple_of_3) {
            next_multiple_of_3 = ugly_numbers[++i3] * 3;
        }
        if (next_ugly_no == next_multiple_of_5) {
            next_multiple_of_5 = ugly_numbers[++i5] * 5;
        }
    }

    return next_ugly_no;
}

}//namespace


SIMPLE_BENCHMARK(NthUglyNumber, 150);

SIMPLE_TEST(NthUglyNumber, TestSAMPLE1, 8, 7);
SIMPLE_TEST(NthUglyNumber, TestSAMPLE2, 12, 10);
SIMPLE_TEST(NthUglyNumber, TestSAMPLE3, 24, 15);
SIMPLE_TEST(NthUglyNumber, TestSAMPLE4, 5832, 150);
