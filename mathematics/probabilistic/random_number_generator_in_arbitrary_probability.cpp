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
auto RandomNumberInArbitraryProbabilitySimple(const ArrayType &numbers,
        const ArrayType &frequencies) {
    assert(numbers.size() == frequencies.size());

    std::vector<ArrayType::value_type> samples;
    for (ArrayType::size_type i = 0; i < numbers.size(); ++i) {
        std::fill_n(std::back_insert_iterator<ArrayType>(samples), frequencies[i], numbers[i]);
    }

    return samples[Random_Number<std::size_t>(0, samples.size() - 1)];
}


auto findCeil(const std::vector<ArrayType::value_type> &prefixs,
              const ArrayType::value_type value) {
    const auto ceil = std::upper_bound(prefixs.cbegin(), prefixs.cend(), value);
    return ceil == prefixs.cend() ? -1 : ceil - prefixs.cbegin();
}
auto RandomNumberInArbitraryProbabilityCeil(const ArrayType &numbers,
        const ArrayType &frequencies) {
    assert(numbers.size() == frequencies.size());

    std::vector<ArrayType::value_type> prefixs = {frequencies.front()};
    for (auto iter = frequencies.cbegin() + 1; iter < frequencies.cend(); ++iter) {
        prefixs.push_back(prefixs.back() + *iter);
    }

    const auto random_number = Random_Number(1, prefixs.back());
    return numbers[findCeil(prefixs, random_number)];
}


static const ArrayType NUMBERS = {0, 1};
static const ArrayType FREQUENCIES = {25, 75};
bool testRandomNumberInArbitraryProbability(
    const std::function<int(const ArrayType &, const ArrayType &)> generator) {
    static const auto TOTAL_SAMPLE_SIZE = 4000000;
    static const auto SAMPLE_SIZE0 = TOTAL_SAMPLE_SIZE / 4;
    static const auto SAMPLE_SIZE1 = SAMPLE_SIZE0 * 3;
    static const double ERROR_RATE = 0.01;
    static const int TOLERATION0 = SAMPLE_SIZE0 * ERROR_RATE;
    static const auto TOLERATION1 = TOLERATION0 * 3;

    std::array<int, 2> counters {};
    for (int i = 0; i < TOTAL_SAMPLE_SIZE; ++i) {
        ++counters[generator(NUMBERS, FREQUENCIES)];
    }

    return SAMPLE_SIZE0 - TOLERATION0 <= counters[0] and
           SAMPLE_SIZE0 + TOLERATION0 >= counters[0] and
           SAMPLE_SIZE1 - TOLERATION1 <= counters[1] and
           SAMPLE_SIZE1 + TOLERATION1 >= counters[1];
}


SIMPLE_BENCHMARK(RandomNumberInArbitraryProbabilitySimple, NUMBERS, FREQUENCIES);

SIMPLE_TEST(testRandomNumberInArbitraryProbability, TestSample, true,
            RandomNumberInArbitraryProbabilitySimple);


SIMPLE_BENCHMARK(RandomNumberInArbitraryProbabilityCeil, NUMBERS, FREQUENCIES);

SIMPLE_TEST(testRandomNumberInArbitraryProbability, TestCeil, true,
            RandomNumberInArbitraryProbabilityCeil);


int RandomNumberInArbitraryProbability(const std::vector<int> &numbers,
                                       const std::vector<int> &frequencies) {
    return RandomNumberInArbitraryProbabilityCeil(numbers, frequencies);
}
