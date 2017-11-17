#include "common_header.h"

using InputType = int;

/** The Modulo-3 Sequence
 *  @reference  The Modulo-3 Sequence
 *              https://www.codewars.com/kata/the-modulo-3-sequence/cpp
 *
 * Consider a sequence where the first two numbers are 0 and 1 and the
 * next number of the sequence is the sum of the previous 2 modulo 3.
 * Write a function that finds the nth number of the sequence.
 */
InputType Modulo3Sequence(const InputType n) {
    const std::vector<InputType> pattern = {1, 0, 1, 1, 2, 0, 2, 1};
    return pattern[n % pattern.size()];
}


constexpr auto LOWER = 1;
constexpr auto UPPER = std::numeric_limits<InputType>::max();
constexpr InputType SAMPLE2 = 2;
constexpr InputType SAMPLE3 = 3;
constexpr InputType SAMPLE4 = 4;
constexpr InputType SAMPLE5 = 5;

SIMPLE_BENCHMARK(Modulo3Sequence, LOWER);
SIMPLE_BENCHMARK(Modulo3Sequence, UPPER);
RANDOM_BENCHMARK(Modulo3Sequence, LOWER, UPPER);

SIMPLE_TEST(Modulo3Sequence, TestLOWER, 0, LOWER);
SIMPLE_TEST(Modulo3Sequence, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(Modulo3Sequence, TestSAMPLE3, 1, SAMPLE3);
SIMPLE_TEST(Modulo3Sequence, TestSAMPLE4, 2, SAMPLE4);
SIMPLE_TEST(Modulo3Sequence, TestSAMPLE5, 0, SAMPLE5);
