#pragma once

/** Primes Below N [1, n)
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 4.2.
 * @reference   Print all prime numbers less than or equal to N
 *              https://www.geeksforgeeks.org/print-all-prime-numbers-less-than-or-equal-to-n/
 * @reference   TCS Coding Practice Question | Prime Numbers upto N
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-prime-numbers-upto-n/
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
template <typename Function>
auto SieveOfEratosthenes_VectorBool(const unsigned long N, const Function for_each_prime_function) {
    assert(N > 2);

    std::vector<bool> prime_marks(N, true);
    prime_marks[0] = false;
    prime_marks[1] = false;

    for_each_prime_function(2);
    for (unsigned long j = 2 * 2; j < N; j += 2) {
        prime_marks[j] = false;
    }

    for (unsigned long i = 3; i < N; i += 2) {
        if (prime_marks[i]) {
            for_each_prime_function(i);
            for (auto j = i * 2; j < N; j += i) {
                prime_marks[j] = false;
            }
        }
    }

    return prime_marks;
}

auto PrimesBelowN(const unsigned long N) {
    std::vector<unsigned long> output;
    if (N > 2) {
        SieveOfEratosthenes_VectorBool(N, [&output](const auto prime) {
            output.push_back(prime);
        });
    }
    return output;
}


auto SieveOfEratosthenes_UniqueCount(const unsigned long N) {
    assert(N > 2);

    std::vector<unsigned char> prime_marks(N, 0);

    for (unsigned long j = 2; j < N; j += 2) {
        ++prime_marks[j];
    }

    for (unsigned long i = 3; i < N; i += 2) {
        if (not prime_marks[i]) {
            for (auto j = i; j < N; j += i) {
                ++prime_marks[j];
            }
        }
    }

    return prime_marks;
}


auto SieveOfEratosthenes_Count(const unsigned long N) {
    assert(N > 2);

    std::vector<unsigned char> prime_marks(N, 0);

    prime_marks[2] = 1;
    for (unsigned long j = 2 * 2; j < N; j += 2) {
        for (auto temp = j; temp > 1 and temp % 2 == 0; temp /= 2) {
            ++prime_marks[j];
        }
    }

    for (unsigned long i = 3; i < N; i += 2) {
        if (not prime_marks[i]) {
            ++prime_marks[i];
            for (auto j = i * 2; j < N; j += i) {
                for (auto temp = j; temp > 1 and temp % i == 0; temp /= i) {
                    ++prime_marks[j];
                }
            }
        }
    }

    return prime_marks;
}
