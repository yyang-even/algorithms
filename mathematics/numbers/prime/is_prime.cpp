#include "common_header.h"

#include "is_prime.h"
#include "mathematics/arithmetics/factorial/factorial.h"


namespace {

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
 *
 * @reference   Lucas Primality Test
 *              https://www.geeksforgeeks.org/lucas-primality-test/
 *
 * This is also a probabilistic test.
 * This method is quite complicated and inefficient as compared to other primality tests.
 * And the main problems are factors of ‘n-1’ and choosing appropriate ‘a’.
 *
 * @reference   Vantieghems Theorem for Primality Test
 *              https://www.geeksforgeeks.org/vantieghems-theorem-primality-test/
 * @reference   Wilson’s Theorem
 *              https://www.geeksforgeeks.org/wilsons-theorem/
 * @reference   Implementation of Wilson Primality test
 *              https://www.geeksforgeeks.org/implementation-of-wilson-primality-test/
 * @reference   C Program to Check Whether a Number is Prime or not
 *              https://www.geeksforgeeks.org/c-program-to-check-whether-a-number-is-prime-or-not/
 * @reference   C++ Program to check Prime Number
 *              https://www.geeksforgeeks.org/c-program-to-check-prime-number/
 * @reference   Recursive program for prime number
 *              https://www.geeksforgeeks.org/recursive-program-prime-number/
 * @reference   Composite Number
 *              https://www.geeksforgeeks.org/composite-number/
 *
 * Given a positive integer, check if the number is prime or not. A prime is a natural number
 * greater than 1 that has no positive divisors other than 1 and itself.
 */


/**
 * If a given number is prime, then this method always returns true. If given number is composite
 * (or non-prime), then it may return true or false, but the probability of producing incorrect
 * result for composite is low and can be reduced by doing more iterations.
 */
INT_BOOL IsPrime_Fermet(const unsigned n) {
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
INT_BOOL IsPrime_MillerRabin(const unsigned n) {
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
INT_BOOL IsPrime_SolovayStrassen(long long n) {
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
INT_BOOL IsPrime_LucasLehmerSeries(unsigned long long p) {
    const unsigned long long n = pow(2, p) - 1;

    auto i = 4 % n;
    for (; p > 2; --p) {
        i = (i * i - 2) % n;
    }

    return (i == 0);
}


INT_BOOL IsPrime_Wilson(const unsigned p) {
    return p != 4 and (Factorial_Iterative(p >> 1) % p);
}


INT_BOOL IsPrime_Recursive(const unsigned n, const unsigned i = 2) {
    if (n < 2) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % i == 0) {
        return false;
    }
    if (i * i > n) {
        return true;
    }

    return IsPrime_Recursive(n, i + 1);
}

}//namespace


SIMPLE_BENCHMARK(IsPrime_OptimizedSchoolMethod, 18);

SIMPLE_TEST(IsPrime_OptimizedSchoolMethod, TestSample1, FALSE, 12);
SIMPLE_TEST(IsPrime_OptimizedSchoolMethod, TestSample2, FALSE, 15);
SIMPLE_TEST(IsPrime_OptimizedSchoolMethod, TestSample3, FALSE, 1);
SIMPLE_TEST(IsPrime_OptimizedSchoolMethod, TestSample4, TRUE, 11);


SIMPLE_BENCHMARK(IsPrime_Fermet, 11);

SIMPLE_TEST(IsPrime_Fermet, TestSample1, TRUE, 11);


SIMPLE_BENCHMARK(IsPrime_MillerRabin, 11);

SIMPLE_TEST(IsPrime_MillerRabin, TestSample1, TRUE, 11);


SIMPLE_BENCHMARK(IsPrime_SolovayStrassen, 11);

SIMPLE_TEST(IsPrime_SolovayStrassen, TestSample1, TRUE, 11);


SIMPLE_BENCHMARK(IsPrime_LucasLehmerSeries, 7);

SIMPLE_TEST(IsPrime_LucasLehmerSeries, TestSample1, TRUE, 7);


SIMPLE_BENCHMARK(IsPrime_Wilson, 11);

SIMPLE_TEST(IsPrime_Wilson, TestSample1, TRUE, 11);
SIMPLE_TEST(IsPrime_Wilson, TestSample2, TRUE, 5);
SIMPLE_TEST(IsPrime_Wilson, TestSample3, TRUE, 7);
SIMPLE_TEST(IsPrime_Wilson, TestSample4, FALSE, 4);
SIMPLE_TEST(IsPrime_Wilson, TestSample5, TRUE, 127);


SIMPLE_BENCHMARK(IsPrime_Recursive, 18);

SIMPLE_TEST(IsPrime_Recursive, TestSample1, FALSE, 12);
SIMPLE_TEST(IsPrime_Recursive, TestSample2, FALSE, 15);
SIMPLE_TEST(IsPrime_Recursive, TestSample3, FALSE, 1);
SIMPLE_TEST(IsPrime_Recursive, TestSample4, TRUE, 11);
