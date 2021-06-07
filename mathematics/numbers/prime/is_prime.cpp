#include "common_header.h"

#include "is_prime.h"
#include "mathematics/arithmetics/factorial/factorial.h"


namespace {

/** Primality Test
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 31.8.
 * @reference   Prime Numbers
 *              https://www.geeksforgeeks.org/prime-numbers/
 * @reference   Primality Test | Set 1 (Introduction and School Method)
 *              https://www.geeksforgeeks.org/primality-test-set-1-introduction-and-school-method/
 * @reference   TCS Coding Practice Question | Checking Prime Number
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-checking-prime-number/
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
 * This is also a probabilistic test. This method is quite complicated and inefficient as
 * compared to other primality tests. And the main problems are factors of 'n-1' and
 * choosing appropriate 'a'.
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
 * Given a positive integer, check if the number is prime or not. A prime is a natural
 * number greater than 1 that has no positive divisors other than 1 and itself.
 *
 * @reference   Euclid’s lemma
 *              https://www.geeksforgeeks.org/euclids-lemma/
 *
 * Euclid's lemma states that if a prime p divides the product of two numbers (x*y), it
 * must divide at least one of those numbers.
 */


/**
 * If a given number is prime, then this method always returns true. If given number is
 * composite (or non-prime), then it may return true or false, but the probability of
 * producing incorrect result for composite is low and can be reduced by doing more
 * iterations.
 */
auto IsPrime_Fermet(const unsigned n) {
    if (n <= 1 or n == 4) {
        return false;
    }
    if (n <= 3) {
        return true;
    }

    static constexpr auto K = 3;
    auto i = 0;
    while (++i <= K) {
        const auto a = Random_Number(2, n - 2);

        if ((static_cast<unsigned>(pow(a, n - 1)) % n) != 1) {
            return false;
        }
    }

    return true;
}


/**
 * This method is a probabilistic method (Like Fermat), but it generally preferred over
 * Fermat’s method.
 */
auto millerTest(unsigned d, const unsigned n) {
    const auto a = Random_Number(2, n - 2);
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

auto IsPrime_MillerRabin(const unsigned n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }

    auto d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    static constexpr auto K = 3;
    for (auto i = 0; i < K; ++i)
        if (!millerTest(d, n)) {
            return false;
        }

    return true;
}


/**
 * The Solovay-Strassen primality test is a probabilistic test to determine if a number is
 * composite or probably prime.
 */
constexpr int calculateJacobian(long long a, long long n) {
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
            if (n % 8 == 3 or n % 8 == 5) {
                ans = -ans;
            }

        }

        std::swap(a, n);

        if (a % 4 == 3 and n % 4 == 3) {
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

auto IsPrime_SolovayStrassen(long long n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }

    static constexpr auto K = 3;
    for (auto i = 0; i < K; ++i) {
        const auto a = Random_Number(2, n - 1);
        const auto jacobian = (n + calculateJacobian(a, n)) % n;
        const auto mod = static_cast<long long>(pow(a, (n - 1) / 2)) % n;

        if (!jacobian or mod != jacobian) {
            return false;
        }
    }
    return true;
}


/**
 * Lucas-Lehmer series is used to check primality of prime numbers of the form n = 2^p - 1
 * where p is an integer.
 */
constexpr auto IsPrime_LucasLehmerSeries(unsigned long long p) {
    const unsigned long long n = pow(2, p) - 1;

    auto i = 4 % n;
    for (; p > 2; --p) {
        i = (i * i - 2) % n;
    }

    return (i == 0);
}


constexpr inline auto IsPrime_Wilson(const unsigned p) {
    return p != 4 and (Factorial_Iterative(p >> 1) % p);
}


constexpr inline auto IsPrime_Recursive(const unsigned n, const unsigned i = 2) {
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


THE_BENCHMARK(IsPrime_OptimizedSchoolMethod, 18);

SIMPLE_TEST(IsPrime_OptimizedSchoolMethod, TestSample1, false, 12);
SIMPLE_TEST(IsPrime_OptimizedSchoolMethod, TestSample2, false, 15);
SIMPLE_TEST(IsPrime_OptimizedSchoolMethod, TestSample3, false, 1);
SIMPLE_TEST(IsPrime_OptimizedSchoolMethod, TestSample4, true, 11);


THE_BENCHMARK(IsPrime_Fermet, 11);

SIMPLE_TEST(IsPrime_Fermet, TestSample1, true, 11);


THE_BENCHMARK(IsPrime_MillerRabin, 11);

SIMPLE_TEST(IsPrime_MillerRabin, TestSample1, true, 11);


THE_BENCHMARK(IsPrime_SolovayStrassen, 11);

SIMPLE_TEST(IsPrime_SolovayStrassen, TestSample1, true, 11);


THE_BENCHMARK(IsPrime_LucasLehmerSeries, 7);

SIMPLE_TEST(IsPrime_LucasLehmerSeries, TestSample1, true, 7);


THE_BENCHMARK(IsPrime_Wilson, 11);

SIMPLE_TEST(IsPrime_Wilson, TestSample1, true, 11);
SIMPLE_TEST(IsPrime_Wilson, TestSample2, true, 5);
SIMPLE_TEST(IsPrime_Wilson, TestSample3, true, 7);
SIMPLE_TEST(IsPrime_Wilson, TestSample4, false, 4);
SIMPLE_TEST(IsPrime_Wilson, TestSample5, true, 127);


THE_BENCHMARK(IsPrime_Recursive, 18);

SIMPLE_TEST(IsPrime_Recursive, TestSample1, false, 12);
SIMPLE_TEST(IsPrime_Recursive, TestSample2, false, 15);
SIMPLE_TEST(IsPrime_Recursive, TestSample3, false, 1);
SIMPLE_TEST(IsPrime_Recursive, TestSample4, true, 11);
