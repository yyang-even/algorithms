#include "common_header.h"

#include "prime_factors_of_n.h"

/** Primality Test
 *
 * @reference   Prime Numbers
 *              https://www.geeksforgeeks.org/prime-numbers/
 * @reference   Primality Test | Set 1 (Introduction and School Method)
 *              https://www.geeksforgeeks.org/primality-test-set-1-introduction-and-school-method/
 * @reference   Primality Test | Set 2 (Fermat Method)
 *              https://www.geeksforgeeks.org/primality-test-set-2-fermet-method/
 * @reference   Primality Test | Set 3 (Miller–Rabin)
 *              https://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/
 * @reference   Primality Test | Set 4 (Solovay-Strassen)
 *              https://www.geeksforgeeks.org/primality-test-set-4-solovay-strassen/
 * @reference   Primality Test | Set 5(Using Lucas-Lehmer Series)
 *              https://www.geeksforgeeks.org/primality-test-set-5using-lucas-lehmer-series/
 * @reference   Lucas Primality Test
 *              https://www.geeksforgeeks.org/lucas-primality-test/
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
    if (n <= 1u or n == 4u) {
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


/**
 * This method is a probabilistic method (Like Fermat), but it generally preferred over Fermat’s method.
 */
bool millerTest(unsigned d, const unsigned n) {
    const auto a = Random_Number<unsigned>(2, n - 2);
    auto x = static_cast<unsigned>(pow(a, d)) % n;
    const auto n_minus_1 = n - 1;

    if (x == 1  or x == n_minus_1) {
        return true;
    }

    while (d != n_minus_1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1) {
            return false;
        }
        if (x == n_minus_1) {
            return true;
        }
    }

    return false;
}
INT_BOOL IsPrimeMillerRabin(const unsigned n) {
    if (n <= 1u) {
        return false;
    }
    if (n <= 3u) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }

    auto d = n - 1u;
    while (d % 2u == 0u) {
        d /= 2u;
    }

    const static auto K = 3;
    for (auto i = 0; i < K; ++i)
        if (!millerTest(d, n)) {
            return false;
        }

    return true;
}


/**
 * The Solovay–Strassen primality test is a probabilistic test to
 * determine if a number is composite or probably prime.
 */
int calculateJacobian(long long a, long long n) {
    if (!a) {
        return 0;
    }

    int ans = 1;
    if (a < 0) {
        a = -a;
        if (n % 4 == 3) {
            ans = -ans;
        }
    }

    if (a == 1) {
        return ans;
    }

    while (a) {
        if (a < 0) {
            a = -a;
            if (n % 4 == 3) {
                ans = -ans;
            }
        }

        while (a % 2 == 0) {
            a = a / 2;
            if (n % 8 == 3 || n % 8 == 5) {
                ans = -ans;
            }

        }

        std::swap(a, n);

        if (a % 4 == 3 && n % 4 == 3) {
            ans = -ans;
        }
        a = a % n;

        if (a > n / 2) {
            a = a - n;
        }

    }

    if (n == 1) {
        return ans;
    }

    return 0;
}
INT_BOOL IsPrimeSolovayStrassen(long long n) {
    if (n <= 1u) {
        return false;
    }
    if (n <= 3u) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }

    const static auto K = 3;
    for (auto i = 0; i < K; ++i) {
        const auto a = Random_Number<long long>(2, n - 1);
        const auto jacobian = (n + calculateJacobian(a, n)) % n;
        const auto mod = static_cast<long long>(pow(a, (n - 1) / 2)) % n;

        if (!jacobian or mod != jacobian) {
            return false;
        }
    }
    return true;
}


/**
 * Lucas-Lehmer series is used to check primality of prime numbers of
 * the form n = 2^p – 1 where p is an integer.
 */
INT_BOOL IsPrimeLucasLehmerSeries(unsigned long long p) {
    const unsigned long long n = pow(2, p) - 1;

    auto i = 4 % n;
    for (; p > 2; --p) {
        i = (i * i - 2) % n;
    }

    return (i == 0);
}


/**
 * This is also a probabilistic test.
 * This method is quite complicated and inefficient as compared to other primality tests.
 * And the main problems are factors of ‘n-1’ and choosing appropriate ‘a’.
 */
INT_BOOL IsPrimeLucasTest(unsigned n) {
    if (n <= 1u) {
        return false;
    }
    if (n <= 3u) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }

    const auto prime_factors = UniquePrimeFactorsOf(n - 1);
    std::vector<unsigned> randoms;
    for (unsigned i = 2; i < n; ++i) {
        randoms.push_back(i);
    }
    std::shuffle(randoms.begin(), randoms.end(), std::default_random_engine(time(0)));

    for (const auto a : randoms) {
        if (static_cast<unsigned>(pow(a, n - 1)) % n != 1) {
            return false;
        }

        bool flag = true;
        for (const auto factor : prime_factors) {
            if (static_cast<unsigned>(pow(a, (n - 1) / factor)) % n == 1) {
                flag = false;
                break;
            }
        }

        if (flag) {
            return true;
        }
    }
    return false;
}


SIMPLE_BENCHMARK(IsPrimeOptimizedSchoolMethod, 18);

SIMPLE_TEST(IsPrimeOptimizedSchoolMethod, TestSample1, FALSE, 12);
SIMPLE_TEST(IsPrimeOptimizedSchoolMethod, TestSample2, FALSE, 15);
SIMPLE_TEST(IsPrimeOptimizedSchoolMethod, TestSample3, FALSE, 1);
SIMPLE_TEST(IsPrimeOptimizedSchoolMethod, TestSample4, TRUE, 11);


SIMPLE_BENCHMARK(IsPrimeFermet, 11);

SIMPLE_TEST(IsPrimeFermet, TestSample1, TRUE, 11);


SIMPLE_BENCHMARK(IsPrimeMillerRabin, 11);

SIMPLE_TEST(IsPrimeMillerRabin, TestSample1, TRUE, 11);


SIMPLE_BENCHMARK(IsPrimeSolovayStrassen, 11);

SIMPLE_TEST(IsPrimeSolovayStrassen, TestSample1, TRUE, 11);


SIMPLE_BENCHMARK(IsPrimeLucasLehmerSeries, 7);

SIMPLE_TEST(IsPrimeLucasLehmerSeries, TestSample1, TRUE, 7);


SIMPLE_BENCHMARK(IsPrimeLucasTest, 11);

SIMPLE_TEST(IsPrimeLucasTest, TestSample1, TRUE, 11);
