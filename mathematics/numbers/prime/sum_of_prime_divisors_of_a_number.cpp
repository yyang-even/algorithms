#include "common_header.h"


namespace {

/** Sum of all the prime divisors of a number
 *
 * @reference   https://www.geeksforgeeks.org/sum-of-all-the-prime-divisors-of-a-number/
 */
constexpr auto SumOfPrimeDivisors(const unsigned number) {
    unsigned sum_of_prime_divisors[number + 1] = {};

    for (unsigned i = 2; i <= number; ++i) {
        if (not sum_of_prime_divisors[i]) {
            for (auto j = i; j <= number; j += i) {
                sum_of_prime_divisors[j] += i;
            }
        }
    }

    return sum_of_prime_divisors[number];
}


/**
 * @reference   Count of numbers below N whose sum of prime divisors is K
 *              https://www.geeksforgeeks.org/count-of-numbers-below-n-whose-sum-of-prime-divisors-is-k/
 *
 * Given two integers K and N, the task is to find the count of integers from the range
 * [2, N – 1] whose sum of prime divisors is K
 */

}//namespace


THE_BENCHMARK(SumOfPrimeDivisors, 60);

SIMPLE_TEST(SumOfPrimeDivisors, TestSAMPLE1, 10, 60);
SIMPLE_TEST(SumOfPrimeDivisors, TestSAMPLE2, 16, 39);
