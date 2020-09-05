#include "common_header.h"

#include "legendres_formula.h"
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


SIMPLE_BENCHMARK(SumOfDivisorsOfFactorial, Sample1, 4);

SIMPLE_TEST(SumOfDivisorsOfFactorial, TestSAMPLE1, 60, 4);
SIMPLE_TEST(SumOfDivisorsOfFactorial, TestSAMPLE2, 2418, 6);
