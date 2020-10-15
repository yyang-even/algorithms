#include "common_header.h"

#include "largest_power_of_p_divides_factorial_n.h"
#include "mathematics/numbers/binary/count_set_bits.h"


namespace {

typedef unsigned InputType;

/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 4.4.
 */
InputType LargestPowerOf2DividesFactorialN(const InputType n) {
    return n - CountSetBits_BrianKernighan(n);
}


#ifdef __GNUC__
InputType LargestPowerOf2DividesFactorialN_BuiltIn(const InputType n) {
    return n - __builtin_popcount(n);
}
#endif

}//namespace


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();


SIMPLE_BENCHMARK(LargestPowerOfPDividesFactorialN, Sample1, 2, 10);

SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE1, 0u, 3, 2);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE2, 8u, 2, 10);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE3, 4u, 3, 9);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE4, 97u, 2, 100);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestUPPER,
            LargestPowerOf2DividesFactorialN(UPPER),
            2, UPPER);


SIMPLE_BENCHMARK(LargestPowerOf2DividesFactorialN, Sample1, 10);

SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestSAMPLE1, 0u, 0);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestSAMPLE2, 8u, 10);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestSAMPLE3, 97u, 100);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestUPPER,
            UPPER - BitsNumber<decltype(UPPER)>,
            UPPER);


#ifdef __GNUC__
SIMPLE_BENCHMARK(LargestPowerOf2DividesFactorialN_BuiltIn, Sample1, 10);

SIMPLE_TEST(LargestPowerOf2DividesFactorialN_BuiltIn, TestSAMPLE1, 0u, 0);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN_BuiltIn, TestSAMPLE2, 8u, 10);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN_BuiltIn, TestSAMPLE3, 97u, 100);
SIMPLE_TEST(LargestPowerOf2DividesFactorialN_BuiltIn, TestUPPER,
            UPPER - BitsNumber<decltype(UPPER)>, UPPER);

MUTUAL_RANDOM_TEST(LargestPowerOf2DividesFactorialN,
                   LargestPowerOf2DividesFactorialN_BuiltIn, 0,
                   96583);
#endif
