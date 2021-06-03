#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Randomized Algorithms | Set 3 (1/2 Approximate Median)
 *
 * @reference   https://www.geeksforgeeks.org/randomized-algorithms-set-3-12-approximate-median/
 *
 * Given an unsorted array A[] of n numbers and ε > 0, compute an element whose rank
 * (position in sorted A[]) is in the range [(1 – ε)n/2, (1 + ε)n/2]. For 1/2
 * Approximate Median Algorithm ε is 1/2 => rank should be in the range [n/4, 3n/4]
 *
 * @reference   Randomized Algorithms | Set 0 (Mathematical Background)
 *              https://www.geeksforgeeks.org/randomized-algorithms-set-0-mathematical-background/
 * @reference   Randomized Algorithms | Set 1 (Introduction and Analysis)
 *              https://www.geeksforgeeks.org/randomized-algorithms-set-1-introduction-and-analysis/
 * @reference   Randomized Algorithms | Set 2 (Classification and Applications)
 *              https://www.geeksforgeeks.org/randomized-algorithms-set-2-classification-and-applications/
 * @reference   Mathematics | Conditional Probability
 *              https://www.geeksforgeeks.org/conditional-probability/
 * @reference   Bayes’s Theorem for Conditional Probability
 *              https://www.geeksforgeeks.org/bayess-theorem-for-conditional-probability/
 * @reference   Linearity of Expectation
 *              https://www.geeksforgeeks.org/linearity-of-expectation/
 * @reference   Expected Number of Trials until Success
 *              https://www.geeksforgeeks.org/expected-number-of-trials-before-success/
 * @reference   Expected number of coin flips to get two heads in a row?
 *              https://www.geeksforgeeks.org/expected-number-of-coin-flips-to-get-two-heads-in-a-row/
 * @reference   Load Balancing on Servers (Randomized Algorithm)
 *              https://www.geeksforgeeks.org/load-balancing-on-servers-random-algorithm/
 */
auto ApproximateMedian(const ArrayType &values) {
    assert(not values.empty());

    constexpr auto C = 10;
    int k = C * std::log2(values.size());

    std::set<ArrayType::value_type> samples;
    for (; k > 0; --k) {
        samples.insert(values[Random_Number(0, values.size() - 1)]);
    }

    return *std::next(samples.cbegin(), (samples.size() / 2) - 1);
}


#ifdef WANT_TESTS
TEST(ApproximateMedianTest, TestSanity) {
    static constexpr auto TOTAL_SAMPLE_SIZE = 100000;
    const ArrayType values = {1, 13, 4, 12, 5, 8, 15, 9, 7, 11, 6, 10, 3, 2, 14};
    auto sorted_array = values;
    std::sort(sorted_array.begin(), sorted_array.end());
    const double ERROR_RATE = 2.0 / (values.size() * values.size());

    std::array<int, 2> counters {};
    for (int i = 0; i < TOTAL_SAMPLE_SIZE; ++i) {
        const auto median = ApproximateMedian(values);
        ++counters[median >= sorted_array[values.size() / 4] and
                          median <= sorted_array[values.size() * 3 / 4]];
    }

    EXPECT_GE((TOTAL_SAMPLE_SIZE * ERROR_RATE), counters[0]);
}
#endif

}//namespace


THE_BENCHMARK(ApproximateMedian, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
