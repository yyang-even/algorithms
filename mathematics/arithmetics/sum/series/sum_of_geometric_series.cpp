#include "common_header.h"


namespace {

/** Sum of Geometric Series
 *
 * @reference   Sum of the series 2^0 + 2^1 + 2^2 +…..+ 2^n
 *              https://www.geeksforgeeks.org/sum-of-the-series-20-21-22-2n/
 */
auto SumOfGeometricSeries(const unsigned N) {
    return (1 << (N + 1)) - 1;
}

}//namespace


SIMPLE_BENCHMARK(SumOfGeometricSeries, Sample1, 5);

SIMPLE_TEST(SumOfGeometricSeries, TestSAMPLE1, 31, 4);
SIMPLE_TEST(SumOfGeometricSeries, TestSAMPLE2, 1023, 9);
