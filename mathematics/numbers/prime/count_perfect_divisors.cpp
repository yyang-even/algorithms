#include "common_header.h"


namespace {

/** Count all perfect divisors of a number
 *
 * @reference   https://www.geeksforgeeks.org/count-perfect-divisors-number/
 *
 * Given a number n, count total perfect divisors of n. Perfect divisors are those
 * divisors which are square of some integer. For example a perfect divisor of 8 is 4.
 */
auto CountPerfectDivisors(const unsigned N) {
    assert(N);

    std::vector<unsigned> perfect_divisors_count(N + 1, 1);
    perfect_divisors_count[0] = 0;
    for (unsigned i = 2; i * i <= N; ++i) {
        const auto square = i * i;
        for (auto j = square; j <= N; j += square) {
            ++perfect_divisors_count[j];
        }
    }

    return perfect_divisors_count[N];
}

}//namespace


THE_BENCHMARK(CountPerfectDivisors, 16);

SIMPLE_TEST(CountPerfectDivisors, TestSAMPLE1, 3, 16);
SIMPLE_TEST(CountPerfectDivisors, TestSAMPLE2, 2, 12);
