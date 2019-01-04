#include "common_header.h"


/** Primality Test
 *
 * @reference   Prime Numbers
 *              https://www.geeksforgeeks.org/prime-numbers/
 *              Primality Test | Set 1 (Introduction and School Method)
 *              https://www.geeksforgeeks.org/primality-test-set-1-introduction-and-school-method/
 *              Primality Test | Set 2 (Fermat Method)
 *              https://www.geeksforgeeks.org/primality-test-set-2-fermet-method/
 *
 * Given a positive integer, check if the number is prime or not. A prime is a natural number
 * greater than 1 that has no positive divisors other than 1 and itself.
 */
INT_BOOL IsPrimeOptimizedSchoolMethod(const unsigned n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }

    if (n % 2 == 0 or n % 3 == 0) {
        return false;
    }

    for (unsigned i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}


/**
 * If a given number is prime, then this method always returns true. If given number is composite
 * (or non-prime), then it may return true or false, but the probability of producing incorrect
 * result for composite is low and can be reduced by doing more iterations.
 */
INT_BOOL IsPrimeFermet(const unsigned n) {
    if (n <= 1u || n == 4u) {
        return false;
    }
    if (n <= 3u) {
        return true;
    }

    const static auto K = 3;
    auto i = 0;
    while (++i <= K) {
        const auto a = Random_Number<unsigned>(2, n - 2);

        if ((static_cast<unsigned>(pow(a, n - 1)) % n) != 1) {
            return false;
        }
    }

    return true;
}


SIMPLE_BENCHMARK(IsPrimeOptimizedSchoolMethod, 18);

SIMPLE_TEST(IsPrimeOptimizedSchoolMethod, TestSample1, FALSE, 12);
SIMPLE_TEST(IsPrimeOptimizedSchoolMethod, TestSample2, FALSE, 15);
SIMPLE_TEST(IsPrimeOptimizedSchoolMethod, TestSample3, FALSE, 1);
SIMPLE_TEST(IsPrimeOptimizedSchoolMethod, TestSample4, TRUE, 11);


SIMPLE_BENCHMARK(IsPrimeFermet, 18);

SIMPLE_TEST(IsPrimeFermet, TestSample1, TRUE, 11);
