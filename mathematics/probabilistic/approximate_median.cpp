#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Randomized Algorithms | Set 3 (1/2 Approximate Median)
 *
 * @reference   https://www.geeksforgeeks.org/randomized-algorithms-set-3-12-approximate-median/
 *
 * Given an unsorted array A[] of n numbers and ε > 0, compute an element whose rank
 * (position in sorted A[]) is in the range [(1 – ε)n/2, (1 + ε)n/2].
 * For 1/2 Approximate Median Algorithm &epsilom; is 1/2 => rank should be in the range [n/4, 3n/4]
 */
auto ApproximateMedian(const ArrayType &values) {
    assert(not values.empty());

    const auto C = 10;
    int k = C * log2(values.size());

    std::set<ArrayType::value_type> samples;
    for (; k > 0; --k) {
        samples.insert(values[Random_Number<ArrayType::size_type>(0, values.size() - 1)]);
    }

    return *std::next(samples.cbegin(), (samples.size() / 2) - 1);
}


inline auto testApproximateMedian() {
    static const auto TOTAL_SAMPLE_SIZE = 100000;
    const ArrayType values = {1, 13, 4, 12, 5, 8, 15, 9, 7, 11, 6, 10, 3, 2, 14};
    auto sorted_array = values;
    std::sort(sorted_array.begin(), sorted_array.end());
    static const double ERROR_RATE = 2.0 / (values.size() * values.size());

    std::array<int, 2> counters {};
    for (int i = 0; i < TOTAL_SAMPLE_SIZE; ++i) {
        const auto median = ApproximateMedian(values);
        ++counters[median >= sorted_array[values.size() / 4] and
                          median <= sorted_array[values.size() * 3 / 4]];
    }

    return counters[0] <= (TOTAL_SAMPLE_SIZE * ERROR_RATE);
}

}//namespace


SIMPLE_BENCHMARK(ApproximateMedian, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});

SIMPLE_TEST0(testApproximateMedian, TestSample, true);
