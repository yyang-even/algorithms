#include "common_header.h"


namespace {

/** Number of occurrences of 2 as a digit in numbers from 0 to n
 *
 * @reference   https://www.geeksforgeeks.org/number-of-occurrences-of-2-as-a-digit-in-numbers-from-0-to-n/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.4.
 *
 * Count the number of 2s as digit in all numbers from 0 to n.
 */
constexpr auto Count2sInRange(const unsigned N, const unsigned position,
                              const unsigned target_digit) {
    assert(target_digit < 10);

    const unsigned lower_power_of_10 = std::pow(10, position);
    const auto upper_power_of_10 = lower_power_of_10 * 10;

    const auto round_down = N - N % upper_power_of_10;
    const auto current_digit = (N / lower_power_of_10) % 10;

    if (current_digit < target_digit) {
        return round_down / 10;
    }
    if (current_digit == target_digit) {
        return (round_down / 10) + (N % lower_power_of_10) + 1;
    }
    const auto round_up = round_down + upper_power_of_10;
    return round_up / 10;
}


/**
 * @reference   Find the occurrences of digit d in the range [0..n]
 *              https://www.geeksforgeeks.org/find-the-occurrences-of-y-in-the-range-of-x/
 */
auto CountTheDigitsInRange(const unsigned N, const unsigned d) {
    const auto str_N = std::to_string(N);

    auto count = 0;
    for (std::size_t i = 0; i < str_N.size(); ++i) {
        count += Count2sInRange(N, i, d);
    }

    return count;
}


inline auto Count2sInRange(const unsigned N) {
    return CountTheDigitsInRange(N, 2);
}

}//namespace


THE_BENCHMARK(Count2sInRange, 100);

SIMPLE_TEST(Count2sInRange, TestSAMPLE1, 6, 22);
SIMPLE_TEST(Count2sInRange, TestSAMPLE2, 20, 100);
SIMPLE_TEST(Count2sInRange, TestSAMPLE3, 13, 30);
SIMPLE_TEST(Count2sInRange, TestSAMPLE4, 9, 25);


THE_BENCHMARK(CountTheDigitsInRange, 25, 2);

SIMPLE_TEST(CountTheDigitsInRange, TestSAMPLE1, 9, 25, 2);
SIMPLE_TEST(CountTheDigitsInRange, TestSAMPLE2, 3, 25, 3);
SIMPLE_TEST(CountTheDigitsInRange, TestSAMPLE3, 6, 32, 3);
