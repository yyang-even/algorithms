#include "common_header.h"


namespace {

/**
 * @reference   Count digits in a factorial | Set 1
 *              https://www.geeksforgeeks.org/count-digits-factorial-set-1/
 *
 * Given an integer n, find the number of digits that appear in its factorial, where
 * factorial is defined as, factorial(n) = 1*2*3*4...n and factorial(0) = 1.
 */
constexpr unsigned CountDigitsInAFactorial(const unsigned n) {
    if (n <= 1) {
        return 1;
    }

    double digits = 0.0;
    for (unsigned i = 2; i <= n; ++i) {
        digits += std::log10(i);
    }

    return std::floor(digits) + 1;
}


/**
 * @reference   Count digits in a factorial | Set 2
 *              https://www.geeksforgeeks.org/count-digits-factorial-set-2/
 */
inline constexpr unsigned long long
CountDigitsInAFactorial_Kamenetsky(const unsigned n) {
    if (n <= 1) {
        return 1;
    }

    // Use Kamenetsky formula to calculate the number of digits
    const double digits = ((n * std::log10(n / M_E) + std::log10(2 * M_PI * n) / 2.0));

    return std::floor(digits) + 1;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<unsigned>::min();


THE_BENCHMARK(CountDigitsInAFactorial, 120);

SIMPLE_TEST(CountDigitsInAFactorial, TestLOWER, 1, LOWER);
SIMPLE_TEST(CountDigitsInAFactorial, TestSAMPLE1, 1, 1);
SIMPLE_TEST(CountDigitsInAFactorial, TestSAMPLE2, 3, 5);
SIMPLE_TEST(CountDigitsInAFactorial, TestSAMPLE3, 7, 10);
SIMPLE_TEST(CountDigitsInAFactorial, TestSAMPLE4, 199, 120);


constexpr auto UPPER = std::numeric_limits<unsigned>::max();


SIMPLE_BENCHMARK(CountDigitsInAFactorial_Kamenetsky, Sample1, LOWER);
SIMPLE_BENCHMARK(CountDigitsInAFactorial_Kamenetsky, Sample2, UPPER);
SIMPLE_BENCHMARK(CountDigitsInAFactorial_Kamenetsky, Sample3, 120);

SIMPLE_TEST(CountDigitsInAFactorial_Kamenetsky, TestLOWER, 1, LOWER);
SIMPLE_TEST(CountDigitsInAFactorial_Kamenetsky, TestSAMPLE1, 1, 1);
SIMPLE_TEST(CountDigitsInAFactorial_Kamenetsky, TestSAMPLE2, 7, 10);
SIMPLE_TEST(CountDigitsInAFactorial_Kamenetsky, TestSAMPLE3, 199, 120);
SIMPLE_TEST(CountDigitsInAFactorial_Kamenetsky, TestSAMPLE4, 363233781, 50000000);
SIMPLE_TEST(CountDigitsInAFactorial_Kamenetsky, TestSAMPLE5, 8565705523, 1000000000);
