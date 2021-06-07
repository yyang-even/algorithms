#include "common_header.h"

#include "largest_power_of_p_divides_factorial_n.h"
#include "least_prime_factor_of_numbers_till_n.h"

#include "mathematics/numbers/binary/count_set_bits.h"


namespace {

/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 4.4.
 */
constexpr inline unsigned LargestPowerOf2DividesFactorialN(const unsigned n) {
    return n - CountSetBits_BrianKernighan(n);
}


#ifdef __GNUC__
constexpr inline unsigned LargestPowerOf2DividesFactorialN_BuiltIn(const unsigned n) {
    return n - __builtin_popcount(n);
}
#endif


/**
 * @reference   Largest power of k in n! (factorial) where k may not be prime
 *              https://www.geeksforgeeks.org/largest-power-k-n-factorial-k-may-not-prime/
 */
auto LargestPowerOfKInNFactorial(unsigned k, const unsigned n) {
    assert(k > 1);

    const auto smallest_prime_factors = LeastPrimeFactorOfNumbers(k);

    std::unordered_map<unsigned, unsigned> factor_count_map;
    while (k != 1) {
        const auto prime_factor = smallest_prime_factors[k];
        ++factor_count_map[prime_factor];
        k /= prime_factor;
    }

    auto x = std::numeric_limits<unsigned>::max();
    for (const auto [factor, count] : factor_count_map) {
        x = std::min(x, LegendresFormula(factor, n) / count);
    }

    return x;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<unsigned>::min();
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


THE_BENCHMARK(LegendresFormula, 2, 10);

SIMPLE_TEST(LegendresFormula, TestSAMPLE1, 0, 3, 2);
SIMPLE_TEST(LegendresFormula, TestSAMPLE2, 8, 2, 10);
SIMPLE_TEST(LegendresFormula, TestSAMPLE3, 4, 3, 9);
SIMPLE_TEST(LegendresFormula, TestSAMPLE4, 97, 2, 100);
SIMPLE_TEST(LegendresFormula, TestUPPER,
            LargestPowerOf2DividesFactorialN(UPPER), 2, UPPER);
SIMPLE_TEST(LegendresFormula, TestSAMPLE5, 2, 3, 7);
SIMPLE_TEST(LegendresFormula, TestSAMPLE6, 4, 3, 10);
SIMPLE_TEST(LegendresFormula, TestSAMPLE7, 4, 2, 7);


THE_BENCHMARK(LargestPowerOfPDividesFactorialN, 2, 10);

SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE1, 0, 3, 2);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE2, 8, 2, 10);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE3, 4, 3, 9);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE4, 97, 2, 100);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestUPPER,
            LargestPowerOf2DividesFactorialN(UPPER), 2, UPPER);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE5, 2, 3, 7);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE6, 4, 3, 10);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE7, 4, 2, 7);


THE_BENCHMARK(LargestPowerOf2DividesFactorialN, 10);

SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestSAMPLE1, 0, 0);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestSAMPLE2, 8, 10);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestSAMPLE3, 97, 100);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestUPPER,
            UPPER - BitsNumber<decltype(UPPER)>, UPPER);


#ifdef __GNUC__
THE_BENCHMARK(LargestPowerOf2DividesFactorialN_BuiltIn, 10);

SIMPLE_TEST(LargestPowerOf2DividesFactorialN_BuiltIn, TestSAMPLE1, 0, 0);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN_BuiltIn, TestSAMPLE2, 8, 10);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN_BuiltIn, TestSAMPLE3, 97, 100);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN_BuiltIn, TestUPPER,
            UPPER - BitsNumber<decltype(UPPER)>, UPPER);

MUTUAL_RANDOM_TEST(LargestPowerOf2DividesFactorialN,
                   LargestPowerOf2DividesFactorialN_BuiltIn,
                   0, 96583);
#endif


THE_BENCHMARK(LargestPowerOfKInNFactorial, 2, 10);

SIMPLE_TEST(LargestPowerOfKInNFactorial, TestSAMPLE1, 0, 3, 2);
SIMPLE_TEST(LargestPowerOfKInNFactorial, TestSAMPLE2, 8, 2, 10);
SIMPLE_TEST(LargestPowerOfKInNFactorial, TestSAMPLE3, 4, 3, 9);
SIMPLE_TEST(LargestPowerOfKInNFactorial, TestSAMPLE4, 97, 2, 100);
SIMPLE_TEST(LargestPowerOfKInNFactorial, TestUPPER,
            LargestPowerOf2DividesFactorialN(UPPER), 2, UPPER);
SIMPLE_TEST(LargestPowerOfKInNFactorial, TestSAMPLE5, 2, 3, 7);
SIMPLE_TEST(LargestPowerOfKInNFactorial, TestSAMPLE6, 4, 3, 10);
SIMPLE_TEST(LargestPowerOfKInNFactorial, TestSAMPLE7, 4, 2, 7);
SIMPLE_TEST(LargestPowerOfKInNFactorial, TestSAMPLE8, 2, 9, 10);
