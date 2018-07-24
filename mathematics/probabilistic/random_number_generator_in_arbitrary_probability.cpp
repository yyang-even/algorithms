#include "common_header.h"

#include "probabilistic.h"

using ArrayType = std::vector<int>;

/** Random number generator in arbitrary probability distribution fashion
 *
 * @reference   https://www.geeksforgeeks.org/random-number-generator-in-arbitrary-probability-distribution-fashion/
 *
 * Given n numbers, each with some frequency of occurrence. Return a
 * random number with probability proportional to its frequency of occurrence.
 */
int RandomNumberInArbitraryProbabilitySimple(const ArrayType &numbers,
        const ArrayType &frequencies) {
    assert(numbers.size() == frequencies.size());

    std::vector<ArrayType::value_type> samples;
    for (ArrayType::size_type i = 0; i < numbers.size(); ++i) {
        std::fill_n(std::back_insert_iterator<ArrayType>(samples), frequencies[i], numbers[i]);
    }

    return samples[Random_Number<std::size_t>(0, samples.size() - 1)];
}


static const ArrayType NUMBERS = {0, 1};
static const ArrayType FREQUENCIES = {25, 75};
bool testRandomNumberInArbitraryProbabilitySimple() {
    static const auto TOTAL_SAMPLE_SIZE = 4000000;
    static const auto SAMPLE_SIZE0 = TOTAL_SAMPLE_SIZE / 4;
    static const auto SAMPLE_SIZE1 = SAMPLE_SIZE0 * 3;
    static const double ERROR_RATE = 0.01;
    static const int TOLERATION0 = SAMPLE_SIZE0 * ERROR_RATE;
    static const auto TOLERATION1 = TOLERATION0 * 3;

    std::array<int, 2> counters {};
    for (int i = 0; i < TOTAL_SAMPLE_SIZE; ++i) {
        ++counters[RandomNumberInArbitraryProbabilitySimple(NUMBERS, FREQUENCIES)];
    }

    return SAMPLE_SIZE0 - TOLERATION0 <= counters[0] and
           SAMPLE_SIZE0 + TOLERATION0 >= counters[0] and
           SAMPLE_SIZE1 - TOLERATION1 <= counters[1] and
           SAMPLE_SIZE1 + TOLERATION1 >= counters[1];
}


SIMPLE_BENCHMARK(RandomNumberInArbitraryProbabilitySimple, NUMBERS, FREQUENCIES);

SIMPLE_TEST0(testRandomNumberInArbitraryProbabilitySimple, TestSample, true);
