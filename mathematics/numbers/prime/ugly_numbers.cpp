#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;


/**
 * @reference   Ugly Number
 *              https://leetcode.com/problems/ugly-number/
 *
 * An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
 * Given an integer n, return true if n is an ugly number.
 */
constexpr auto isUglyNumber_Mod(int n) {
    if (n <= 0) {
        return false;
    }

    while (n % 2 == 0) {
        n /= 2;
    }

    while (n % 3 == 0) {
        n /= 3;
    }

    while (n % 5 == 0) {
        n /= 5;
    }

    return n == 1;
}


constexpr auto isUglyNumber(int n) {
    if (n < 1) {
        return false;
    }

    while ((n & 1) == 0) {
        n >>= 1;
    }

    for (long i = 1; i <= n; i *= 3) {
        for (long j = 1; j <= n; j *= 5) {
            if (i * j == n) {
                return true;
            }
        }
    }

    return false;
}


/** Ugly Numbers
 *
 * @reference   https://www.geeksforgeeks.org/ugly-numbers/
 *
 * Ugly numbers are numbers whose only prime factors are 2, 3 or 5. The sequence 1, 2, 3,
 * 4, 5, 6, 8, 9, 10, 12, 15, ... shows the first 11 ugly numbers. By convention, 1 is
 * included. Given a number n, the task is to find nth Ugly number.
 *
 * @reference   Ugly Number II
 *              https://leetcode.com/problems/ugly-number-ii/
 *
 * An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
 * Given an integer n, return the nth ugly number.
 */
constexpr auto NthUglyNumber(const unsigned N) {
    unsigned ugly_numbers[N] = {1};
    unsigned i2 = 0, i3 = 0, i5 = 0;
    unsigned next_multiple_of_2 = 2;
    unsigned next_multiple_of_3 = 3;
    unsigned next_multiple_of_5 = 5;

    for (unsigned i = 1; i < N; ++i) {
        const auto next_ugly_number = std::min(next_multiple_of_2,
                                               std::min(next_multiple_of_3, next_multiple_of_5));
        ugly_numbers[i] = next_ugly_number;
        if (next_ugly_number == next_multiple_of_2) {
            next_multiple_of_2 = ugly_numbers[++i2] * 2;
        }
        if (next_ugly_number == next_multiple_of_3) {
            next_multiple_of_3 = ugly_numbers[++i3] * 3;
        }
        if (next_ugly_number == next_multiple_of_5) {
            next_multiple_of_5 = ugly_numbers[++i5] * 5;
        }
    }

    return ugly_numbers[N - 1];
}


/**
 * @reference   Ugly Number III
 *              https://leetcode.com/problems/ugly-number-iii/
 *
 * An ugly number is a positive integer that is divisible by a, b, or c. Given four
 * integers n, a, b, and c, return the nth ugly number.
 */
constexpr auto
nthDivisibleUglyNumber_BinarySearch(const long N, const long a,
                                    const long b, const long c) {
    long left = 1;
    long right = INT_MAX;
    const auto ab_lcm = std::lcm(a, b);
    const auto ac_lcm = std::lcm(a, c);
    const auto bc_lcm = std::lcm(b, c);
    const auto abc_lcm = std::lcm(a, bc_lcm);
    while (left < right) {
        const auto mid = (left + right) / 2;

        const auto count = mid / a + mid / b + mid / c -
                           mid / ab_lcm - mid / ac_lcm - mid / bc_lcm +
                           mid / abc_lcm;
        if (count >= N) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}


/**
 * @reference   Super Ugly Number (Number whose prime factors are in given set)
 *              https://www.geeksforgeeks.org/super-ugly-number-number-whose-prime-factors-given-set/
 *
 * @reference   Super Ugly Number
 *              https://leetcode.com/problems/super-ugly-number/
 *
 * A super ugly number is a positive integer whose prime factors are in the array primes.
 * Given an integer n and an array of integers primes, return the nth super ugly number.
 * The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
 */
auto NthSuperUglyNumber(const ArrayType &primes, const unsigned N) {
    assert(std::is_sorted(primes.cbegin(), primes.cend()));

    unsigned ugly_numbers[N] = {1};
    unsigned indices[primes.size()] = {};
    auto next_multiples = primes;

    for (unsigned i = 1; i < N; ++i) {
        const auto next_ugly_number =
            *std::min_element(next_multiples.cbegin(), next_multiples.cend());
        ugly_numbers[i] = next_ugly_number;
        for (ArrayType::size_type k = 0; k < next_multiples.size(); ++k) {
            if (next_ugly_number == next_multiples[k]) {
                next_multiples[k] = ugly_numbers[++indices[k]] * primes[k];
            }
        }
    }

    return ugly_numbers[N - 1];
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 7.7.
 *
 * Design an algorithm such that we have to find the kth element in the array such that
 * their only prime factors are 3,5 an 7.
 */
auto KthMagicNumber(const unsigned k) {
    std::queue<long> queue_threes;
    queue_threes.push(3);
    std::queue<long> queue_fives;
    queue_fives.push(5);
    std::queue<long> queue_sevens;
    queue_sevens.push(7);

    long result = 1;
    for (unsigned i = 1; i < k; ++i) {
        const auto threes_front = queue_threes.front();
        const auto fives_front = queue_fives.front();
        const auto sevens_front = queue_sevens.front();

        result = std::min(std::min(threes_front, fives_front), sevens_front);
        if (result == threes_front) {
            queue_threes.pop();
            queue_threes.push(3 * result);
            queue_fives.push(5 * result);
        } else if (result == fives_front) {
            queue_fives.pop();
            queue_fives.push(5 * result);
        } else if (result == sevens_front) {
            queue_sevens.pop();
        }
        queue_sevens.push(7 * result);
    }

    return result;
}

}//namespace


THE_BENCHMARK(NthUglyNumber, 150);

SIMPLE_TEST(NthUglyNumber, TestSAMPLE1, 8, 7);
SIMPLE_TEST(NthUglyNumber, TestSAMPLE2, 12, 10);
SIMPLE_TEST(NthUglyNumber, TestSAMPLE3, 24, 15);
SIMPLE_TEST(NthUglyNumber, TestSAMPLE4, 5832, 150);


const ArrayType SAMPLE1 = {2, 3, 5};
const ArrayType SAMPLE6 = {2, 5};
const ArrayType SAMPLE7 = {3, 5, 7, 11, 13};
const ArrayType SAMPLE9 = {3, 5, 7};
const ArrayType SAMPLE10 = {2, 7, 13, 19};


THE_BENCHMARK(NthSuperUglyNumber, SAMPLE1, 150);

SIMPLE_TEST(NthSuperUglyNumber, TestSAMPLE1, 8, SAMPLE1, 7);
SIMPLE_TEST(NthSuperUglyNumber, TestSAMPLE2, 12, SAMPLE1, 10);
SIMPLE_TEST(NthSuperUglyNumber, TestSAMPLE3, 24, SAMPLE1, 15);
SIMPLE_TEST(NthSuperUglyNumber, TestSAMPLE4, 5832, SAMPLE1, 150);
SIMPLE_TEST(NthSuperUglyNumber, TestSAMPLE5, 243, SAMPLE1, 50);
SIMPLE_TEST(NthSuperUglyNumber, TestSAMPLE6, 8, SAMPLE6, 5);
SIMPLE_TEST(NthSuperUglyNumber, TestSAMPLE7, 21, SAMPLE7, 9);
SIMPLE_TEST(NthSuperUglyNumber, TestSAMPLE8, 51200000, SAMPLE1, 1000);
SIMPLE_TEST(NthSuperUglyNumber, TestSAMPLE9, 25, SAMPLE9, 8);
SIMPLE_TEST(NthSuperUglyNumber, TestSAMPLE10, 63, SAMPLE9, 13);
SIMPLE_TEST(NthSuperUglyNumber, TestSAMPLE11, 32, SAMPLE10, 12);
SIMPLE_TEST(NthSuperUglyNumber, TestSAMPLE12, 1, SAMPLE1, 1);


THE_BENCHMARK(KthMagicNumber, 25);

SIMPLE_TEST(KthMagicNumber, TestSAMPLE1, 1, 0);
SIMPLE_TEST(KthMagicNumber, TestSAMPLE2, 1, 1);
SIMPLE_TEST(KthMagicNumber, TestSAMPLE3, 25, 8);
SIMPLE_TEST(KthMagicNumber, TestSAMPLE4, 63, 13);


THE_BENCHMARK(isUglyNumber_Mod, 25);

SIMPLE_TEST(isUglyNumber_Mod, TestSAMPLE1, false, 0);
SIMPLE_TEST(isUglyNumber_Mod, TestSAMPLE2, true, 1);
SIMPLE_TEST(isUglyNumber_Mod, TestSAMPLE3, true, 6);
SIMPLE_TEST(isUglyNumber_Mod, TestSAMPLE4, true, 8);
SIMPLE_TEST(isUglyNumber_Mod, TestSAMPLE5, false, 14);


THE_BENCHMARK(isUglyNumber, 25);

SIMPLE_TEST(isUglyNumber, TestSAMPLE1, false, 0);
SIMPLE_TEST(isUglyNumber, TestSAMPLE2, true, 1);
SIMPLE_TEST(isUglyNumber, TestSAMPLE3, true, 6);
SIMPLE_TEST(isUglyNumber, TestSAMPLE4, true, 8);
SIMPLE_TEST(isUglyNumber, TestSAMPLE5, false, 14);


THE_BENCHMARK(nthDivisibleUglyNumber_BinarySearch, 150, 2, 3, 5);

SIMPLE_TEST(nthDivisibleUglyNumber_BinarySearch, TestSAMPLE1, 4, 3, 2, 3, 5);
SIMPLE_TEST(nthDivisibleUglyNumber_BinarySearch, TestSAMPLE2, 6, 4, 2, 3, 4);
SIMPLE_TEST(nthDivisibleUglyNumber_BinarySearch, TestSAMPLE3, 10, 5, 2, 11, 13);
SIMPLE_TEST(nthDivisibleUglyNumber_BinarySearch, TestSAMPLE4, 1999999984,
            1000000000, 2, 217983653, 336916467);
