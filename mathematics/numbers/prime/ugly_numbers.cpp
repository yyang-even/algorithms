#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Ugly Numbers
 *
 * @reference   https://www.geeksforgeeks.org/ugly-numbers/
 *
 * Ugly numbers are numbers whose only prime factors are 2, 3 or 5. The sequence 1, 2, 3,
 * 4, 5, 6, 8, 9, 10, 12, 15, ... shows the first 11 ugly numbers. By convention, 1 is
 * included. Given a number n, the task is to find nth Ugly number.
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
 * @reference   Super Ugly Number (Number whose prime factors are in given set)
 *              https://www.geeksforgeeks.org/super-ugly-number-number-whose-prime-factors-given-set/
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
    std::queue<int> queue_threes;
    std::queue<int> queue_fives;
    std::queue<int> queue_sevens;
    int result = 1;
    queue_threes.push(result);
    for (unsigned i = 0; i < k; ++i) {
        const auto threes_front = queue_threes.empty() ? std::numeric_limits<int>::max() :
                                  queue_threes.front();
        const auto fives_front = queue_fives.empty() ? std::numeric_limits<int>::max() :
                                 queue_fives.front();
        const auto sevens_front = queue_sevens.empty() ? std::numeric_limits<int>::max() :
                                  queue_sevens.front();

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


THE_BENCHMARK(KthMagicNumber, 25);

SIMPLE_TEST(KthMagicNumber, TestSAMPLE1, 1, 0);
SIMPLE_TEST(KthMagicNumber, TestSAMPLE2, 1, 1);
SIMPLE_TEST(KthMagicNumber, TestSAMPLE3, 25, 8);
SIMPLE_TEST(KthMagicNumber, TestSAMPLE4, 63, 13);
