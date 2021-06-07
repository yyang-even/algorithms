#pragma once


/** Prime Factors of N
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 4.2.
 *
 * Fundamental Theorem of Arithmetic: There's only one way to write n as a product of
 * primes in nondecreasing order.
 *
 * @reference   Efficient program to print all prime factors of a given number
 *              https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
 * @reference   C Program for efficiently print all prime factors of a given number
 *              https://www.geeksforgeeks.org/c-program-for-efficiently-print-all-prime-factors-of-a-given-number/
 * @reference   Prime Factor
 *              https://www.geeksforgeeks.org/prime-factor/
 *
 * Given a number n, write an efficient function to print all prime factors of n. For
 * example, if the input number is 12, then output should be "2 2 3". And if the input
 * number is 315, then output should be "3 3 5 7".
 *
 * Following are the steps to find all prime factors.
 *  1) While n is divisible by 2, print 2 and divide n by 2.
 *  2) After step 1, n must be odd. Now start a loop from i = 3 to square root of n.
 *  While i divides n, print i and divide n by i, increment i by 2 and continue.
 *  3) If n is a prime number and is greater than 2, then n will not become 1 by above
 *  two steps. So print n if it is greater than 2.
 */
static inline auto PrimeFactorsOf(unsigned N) {
    std::vector<unsigned> output;

    if (N > 2) {
        while (N % 2 == 0) {
            output.push_back(2);
            N /= 2;
        }

        const unsigned square_root = sqrt(double(N));
        for (unsigned i = 3; i <= square_root; i += 2) {
            while (N % i == 0) {
                output.push_back(i);
                N /= i;
            }
        }

        if (N > 2) {
            output.push_back(N);
        }
    }
    return output;
}


/**
 * @reference   Find largest prime factor of a number
 *              https://www.geeksforgeeks.org/find-largest-prime-factor-number/
 * @reference   C Program for Find largest prime factor of a number
 *              https://www.geeksforgeeks.org/c-program-for-find-largest-prime-factor-of-a-number/
 * @reference   Find sum of a number and its maximum prime factor
 *              https://www.geeksforgeeks.org/find-sum-of-a-number-and-its-maximum-prime-factor/
 */


/** k-th prime factor of a given number
 *
 * @reference   https://www.geeksforgeeks.org/k-th-prime-factor-given-number/
 *
 * Given two numbers n and k, print k-th prime factor among all prime factors of n.
 */


static inline auto UniquePrimeFactorsOf(const unsigned N) {
    auto prime_factors = PrimeFactorsOf(N);
    const auto last = std::unique(prime_factors.begin(), prime_factors.end());
    prime_factors.erase(last, prime_factors.end());
    return prime_factors;
}


/**
 * @reference   Prime Factorization using Sieve O(log n) for multiple queries
 *              https://www.geeksforgeeks.org/prime-factorization-using-sieve-olog-n-multiple-queries/
 * @reference   Print all prime factors and their powers
 *              https://www.geeksforgeeks.org/print-all-prime-factors-and-their-powers/
 */
static inline auto
PrimeFactorsOfN_Sieve(unsigned N, const std::vector<unsigned> &smallest_prime_factors) {
    std::vector<unsigned> output;
    while (N != 1) {
        const auto prime_factor = smallest_prime_factors[N];
        output.push_back(prime_factor);
        N /= prime_factor;
    }

    return output;
}
