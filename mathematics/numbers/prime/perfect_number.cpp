#include "common_header.h"

#include "sum_of_factors_of_a_number.h"


namespace {

/** Perfect Number
 *
 * @reference   https://www.geeksforgeeks.org/perfect-number/
 *
 * A number is a perfect number if is equal to sum of its proper divisors, that is, sum
 * of its positive divisors excluding the number itself. Write a function to check if a
 * given number is perfect or not.
 */
inline auto isPerfectNumber(const unsigned N) {
    return SumOfProferDivisors(N) == N;
}

}//namespace


THE_BENCHMARK(isPerfectNumber, 15);

SIMPLE_TEST(isPerfectNumber, TestSAMPLE1, false, 15);
SIMPLE_TEST(isPerfectNumber, TestSAMPLE2, true, 6);
