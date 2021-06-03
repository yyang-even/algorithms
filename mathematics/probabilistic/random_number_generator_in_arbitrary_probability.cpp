#include "common_header.h"

#include "random_number_generator_in_arbitrary_probability.h"


namespace {

using ArrayType = std::vector<int>;

/** Random number generator in arbitrary probability distribution fashion
 *
 * @reference   https://www.geeksforgeeks.org/random-number-generator-in-arbitrary-probability-distribution-fashion/
 *
 * Given n numbers, each with some frequency of occurrence. Return a random number with
 * probability proportional to its frequency of occurrence.
 */
auto RandomNumberInArbitraryProbability_Simple(const ArrayType &numbers,
                                               const ArrayType &frequencies) {
    assert(numbers.size() == frequencies.size());

    ArrayType samples;
    for (ArrayType::size_type i = 0; i < numbers.size(); ++i) {
        std::fill_n(std::back_insert_iterator<ArrayType>(samples), frequencies[i], numbers[i]);
    }

    return samples[Random_Number(0, samples.size() - 1)];
}


const ArrayType NUMBERS = {0, 1};
const ArrayType FREQUENCIES = {25, 75};

inline bool testRandomNumberInArbitraryProbability(
    const std::function<int(const ArrayType &, const ArrayType &)> generator) {
    static constexpr auto TOTAL_SAMPLE_SIZE = 4000000;
    static constexpr auto SAMPLE_SIZE0 = TOTAL_SAMPLE_SIZE / 4;
    static constexpr auto SAMPLE_SIZE1 = SAMPLE_SIZE0 * 3;
    static constexpr double ERROR_RATE = 0.01;
    static constexpr int TOLERATION0 = SAMPLE_SIZE0 * ERROR_RATE;
    static constexpr auto TOLERATION1 = TOLERATION0 * 3;

    std::array<int, 2> counters {};
    for (int i = 0; i < TOTAL_SAMPLE_SIZE; ++i) {
        ++counters[generator(NUMBERS, FREQUENCIES)];
    }

    return SAMPLE_SIZE0 - TOLERATION0 <= counters[0] and
           SAMPLE_SIZE0 + TOLERATION0 >= counters[0] and
           SAMPLE_SIZE1 - TOLERATION1 <= counters[1] and
           SAMPLE_SIZE1 + TOLERATION1 >= counters[1];
}


/** Write a function that generates one of 3 numbers according to given probabilities
 *
 * @reference   https://www.geeksforgeeks.org/write-a-function-to-generate-3-numbers-according-to-given-probabilities/
 *
 * You are given a function rand(a, b) which generates equiprobable random numbers
 * between [a, b] inclusive. Generate 3 numbers x, y, z with probability P(x), P(y),
 * P(z) such that P(x) + P(y) + P(z) = 1 using the given rand(a,b) function.
 */
inline auto RandomNumber1of3(const int x, const int y, const int z,
                             const int px, const int py, const int pz) {
    return RandomNumberInArbitraryProbability_Ceil({x, y, z}, {px, py, pz});
}

}//namespace


THE_BENCHMARK(RandomNumberInArbitraryProbability_Simple, NUMBERS, FREQUENCIES);

SIMPLE_TEST(testRandomNumberInArbitraryProbability, TestSample, true,
            RandomNumberInArbitraryProbability_Simple);


THE_BENCHMARK(RandomNumberInArbitraryProbability_Ceil, NUMBERS, FREQUENCIES);

SIMPLE_TEST(testRandomNumberInArbitraryProbability, TestCeil, true,
            RandomNumberInArbitraryProbability_Ceil);


THE_BENCHMARK(RandomNumber1of3, 1, 2, 3, 40, 25, 35);
