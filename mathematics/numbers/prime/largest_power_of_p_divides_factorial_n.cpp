#include "common_header.h"

#include "largest_power_of_p_divides_factorial_n.h"
#include "mathematics/numbers/binary/count_set_bits.h"

namespace {

typedef unsigned InputType;


/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 4.4.
 */
InputType LargestPowerOf2DividesFactorialN(const InputType n) {
    return n - CountSetBitsBrianKernighan(n);
}
#ifdef __GNUC__
InputType LargestPowerOf2DividesFactorialNBuiltIn(const InputType n) {
    return n - __builtin_popcount(n);
}
#endif

}//namespace


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(LargestPowerOfPDividesFactorialN, 2, LOWER);
SIMPLE_BENCHMARK(LargestPowerOfPDividesFactorialN, 2, UPPER);
SIMPLE_BENCHMARK(LargestPowerOfPDividesFactorialN, 2, 10);

SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE1, 0, 3, 2);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE2, 8, 2, 10);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE3, 4, 3, 9);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE4, 97, 2, 100);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestUPPER, LargestPowerOf2DividesFactorialN(UPPER),
            2, UPPER);

SIMPLE_BENCHMARK(LargestPowerOf2DividesFactorialN, LOWER);
SIMPLE_BENCHMARK(LargestPowerOf2DividesFactorialN, UPPER);
SIMPLE_BENCHMARK(LargestPowerOf2DividesFactorialN, 10);

SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestSAMPLE1, 0, 0);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestSAMPLE2, 8, 10);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestSAMPLE3, 97, 100);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestUPPER, UPPER - Bits_Number<decltype(UPPER)>(),
            UPPER);

#ifdef __GNUC__
SIMPLE_BENCHMARK(LargestPowerOf2DividesFactorialNBuiltIn, LOWER);
SIMPLE_BENCHMARK(LargestPowerOf2DividesFactorialNBuiltIn, UPPER);
SIMPLE_BENCHMARK(LargestPowerOf2DividesFactorialNBuiltIn, 10);

SIMPLE_TEST(LargestPowerOf2DividesFactorialNBuiltIn, TestSAMPLE1, 0, 0);
SIMPLE_TEST(LargestPowerOf2DividesFactorialNBuiltIn, TestSAMPLE2, 8, 10);
SIMPLE_TEST(LargestPowerOf2DividesFactorialNBuiltIn, TestSAMPLE3, 97, 100);
SIMPLE_TEST(LargestPowerOf2DividesFactorialNBuiltIn, TestUPPER,
            UPPER - Bits_Number<decltype(UPPER)>(), UPPER);

MUTUAL_RANDOM_TEST(LargestPowerOf2DividesFactorialN, LargestPowerOf2DividesFactorialNBuiltIn, 0,
                   96583);
#endif
