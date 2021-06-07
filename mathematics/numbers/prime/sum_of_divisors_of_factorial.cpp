#include "common_header.h"

#include "largest_power_of_p_divides_factorial_n.h"
#include "primes_below_n.h"


namespace {

/** Sum of divisors of factorial of a number
 *
 * @reference   https://www.geeksforgeeks.org/sum-divisors-factorial-number/
 */
auto SumOfDivisorsOfFactorial(const unsigned number) {
    const auto primes_till_n = PrimesBelowN(number + 1);

    unsigned result = 1;
    for (const auto p : primes_till_n) {
        const auto x = LegendresFormula(p, number);

        result *= (std::pow(p, x + 1) - 1) / (p - 1);
    }

    return result;
}

}//namespace


THE_BENCHMARK(SumOfDivisorsOfFactorial, 4);

SIMPLE_TEST(SumOfDivisorsOfFactorial, TestSAMPLE1, 60, 4);
SIMPLE_TEST(SumOfDivisorsOfFactorial, TestSAMPLE2, 2418, 6);
