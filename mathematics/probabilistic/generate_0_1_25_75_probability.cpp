#include "common_header.h"

/** Generate 0 and 1 with 25% and 75% probability
 *
 * @reference   https://www.geeksforgeeks.org/generate-0-1-25-75-probability/
 *
 * Given a function rand50() that returns 0 or 1 with equal probability,
 * write a function that returns 1 with 75% probability and 0 with 25%
 * probability using rand50() only. Minimize the number of calls to rand50()
 * method. Also, use of any other library function and floating point
 * arithmetic are not allowed.
 */
inline auto rand50() {
    return Random_Number(0, 1);
}
auto Generate25BiasedCoinFromFair() {
    return rand50() | rand50();
}


bool testGenerate25BiasedCoinFromFair() {
    static const auto TOTAL_SAMPLE_SIZE = 4000000;
    static const auto SAMPLE_SIZE0 = TOTAL_SAMPLE_SIZE / 4;
    static const auto SAMPLE_SIZE1 = SAMPLE_SIZE0 * 3;
    static const double ERROR_RATE = 0.01;
    static const int TOLERATION0 = SAMPLE_SIZE0 * ERROR_RATE;
    static const auto TOLERATION1 = TOLERATION0 * 3;

    std::array<int, 2> counters {};
    for (int i = 0; i < TOTAL_SAMPLE_SIZE; ++i) {
        ++counters[Generate25BiasedCoinFromFair()];
    }

    return SAMPLE_SIZE0 - TOLERATION0 <= counters[0] and
           SAMPLE_SIZE0 + TOLERATION0 >= counters[0] and
           SAMPLE_SIZE1 - TOLERATION1 <= counters[1] and
           SAMPLE_SIZE1 + TOLERATION1 >= counters[1];
}


SIMPLE_BENCHMARK(Generate25BiasedCoinFromFair);

SIMPLE_TEST0(testGenerate25BiasedCoinFromFair, TestSample, true);
