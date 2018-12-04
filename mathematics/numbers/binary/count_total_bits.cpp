#include "common_header.h"

using InputType = unsigned;

/** Count total bits in a number
 *
 * @reference   https://www.geeksforgeeks.org/count-total-bits-number/
 *
 * Given a positive number n, count total bit in it.
 */
auto CountTotalBitsLog(const InputType num) {
    assert(num);
    return static_cast<InputType>(log2(num)) + 1;
}

auto CountTotalBitsLoop(InputType num) {
    InputType count = 0;
    for (; num; num >>= 1) {
        ++count;
    }
    return count;
}


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(CountTotalBitsLog, UPPER);
RANDOM_BENCHMARK(CountTotalBitsLog, LOWER, UPPER);

SIMPLE_TEST(CountTotalBitsLog, TestUPPER, Bits_Number<decltype(UPPER)>(), UPPER);
SIMPLE_TEST(CountTotalBitsLog, TestSAMPLE1, 4, 13);
SIMPLE_TEST(CountTotalBitsLog, TestSAMPLE2, 8, 183);
SIMPLE_TEST(CountTotalBitsLog, TestSAMPLE3, 13, 4096);
SIMPLE_TEST(CountTotalBitsLog, TestSAMPLE4, 7, 65);


SIMPLE_BENCHMARK(CountTotalBitsLoop, LOWER);
SIMPLE_BENCHMARK(CountTotalBitsLoop, UPPER);
RANDOM_BENCHMARK(CountTotalBitsLoop, LOWER, UPPER);

SIMPLE_TEST(CountTotalBitsLoop, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountTotalBitsLoop, TestUPPER, Bits_Number<decltype(UPPER)>(), UPPER);
SIMPLE_TEST(CountTotalBitsLoop, TestSAMPLE1, 4, 13);
SIMPLE_TEST(CountTotalBitsLoop, TestSAMPLE2, 8, 183);
SIMPLE_TEST(CountTotalBitsLoop, TestSAMPLE3, 13, 4096);
SIMPLE_TEST(CountTotalBitsLoop, TestSAMPLE4, 7, 65);

MUTUAL_RANDOM_TEST(CountTotalBitsLog, CountTotalBitsLoop, LOWER, UPPER);
