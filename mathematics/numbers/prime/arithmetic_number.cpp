#include "common_header.h"

#include "count_divisors_of_n.h"
#include "sum_of_factors_of_a_number.h"


namespace {

/** Arithmetic Number
 *
 * @reference   https://www.geeksforgeeks.org/arithmetic-number/
 *
 * In number theory, an arithmetic number is an integer for which the average of its
 * positive divisors is also an integer. Or in other words, a number N is arithmetic
 * if the number of divisors divides the sum of divisors.
 */
inline auto isArithmeticNumber(const unsigned N) {
    const auto divisors_sum = SumOfFactorsOfN(N);
    const auto count_divisors = CountDivisorsOfN(N);
    return divisors_sum % count_divisors == 0;
}

}//namespace


THE_BENCHMARK(isArithmeticNumber, 6);

SIMPLE_TEST(isArithmeticNumber, TestSAMPLE1, true, 6);
SIMPLE_TEST(isArithmeticNumber, TestSAMPLE2, false, 2);
