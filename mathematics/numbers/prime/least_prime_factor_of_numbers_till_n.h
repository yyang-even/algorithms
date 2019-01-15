#pragma once

/** Least prime factor of numbers till n
 *
 * @reference   https://www.geeksforgeeks.org/least-prime-factor-of-numbers-till-n/
 *
 * Given a number n, print least prime factors of all numbers from 1 to n. The least
 * prime factor of an integer n is the smallest prime number that divides the number.
 * The least prime factor of all even numbers is 2. A prime number is its own least
 * prime factor (as well as its own greatest prime factor).
 * Note: We need to print 1 for 1.
 */
auto LeastPrimeFactorOfNumbers(const unsigned N) {
    assert(N > 1);
    std::vector<unsigned> smallest_prime_factors(N + 1, 0);
    smallest_prime_factors[1] = 1;

    for (unsigned i = 2; i <= N; ++i) {
        if (smallest_prime_factors[i] == 0) {
            smallest_prime_factors[i] = i;
            for (unsigned j = i * 2; j <= N; j += i) {
                if (smallest_prime_factors[j] == 0) {
                    smallest_prime_factors[j] = i;
                }
            }
        }
    }

    return smallest_prime_factors;
}

