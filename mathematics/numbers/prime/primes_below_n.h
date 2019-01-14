#pragma once

/** Primes Below N [1, n)
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 4.2.
 * @reference   Print all prime numbers less than or equal to N
 *              https://www.geeksforgeeks.org/print-all-prime-numbers-less-than-or-equal-to-n/
 * @reference   Sieve of Eratosthenes
 *              https://www.geeksforgeeks.org/sieve-of-eratosthenes/
 * @reference   Sieve of Eratosthenes in 0(n) time complexity
 *              https://www.geeksforgeeks.org/sieve-eratosthenes-0n-time-complexity/
 *
 * @reference   Segmented Sieve
 *              https://www.geeksforgeeks.org/segmented-sieve/
 *
 * Note that time complexity (or number of operations) by Segmented Sieve is same as Simple Sieve.
 * It has advantages for large ‘n’ as it has better locality of reference and requires.
 *
 * @reference   Bitwise Sieve
 *              https://www.geeksforgeeks.org/bitwise-sieve/
 *
 * A positive integer p is called prime if it has just two divisors, namely 1 and p.
 * By convention, 1 isn't prime, so the sequence of primes starts out like this:
 *  2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,...
 *
 * Sieve of Eratosthenes:
 * First write down all integers from 2 through N.
 * Next circle 2, marking it prime, and cross out all other multiples of 2.
 * The repeatedly circle the smallest uncircled, uncrossed number and cross out its other multiples.
 * When everything has been circled or crossed out, the circled numbers are the primes.
 */
auto SieveOfEratosthenes(const unsigned long N) {
    std::vector<unsigned long> output;
    if (N > 2) {
        std::vector<bool> prime_marks(N, true);
        unsigned long j;
        for (unsigned long i = 2; i < N; ++i) {
            if (prime_marks[i]) {
                output.push_back(i);
                for (j = i * 2; j < N; j += i) {
                    prime_marks[j] = false;
                }
            }
        }
    }
    return output;
}
