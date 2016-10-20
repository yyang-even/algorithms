#include "common_header.h"

#include "mathematics/numbers/binary/binary.h"

typedef unsigned InputType;

/**The largest power of p that divides n!
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 4.4.
 *
 * We'd like to determine, for any given prime p, the largest power of p that divides n!; that is,
 * we want the exponent of p in n!'s unique factorization.
 */
InputType LargestPowerOfPDividesFactorialN(const InputType p, const InputType n) {
    InputType power = 0;
    //Use ULL to prevent overflow
    for (unsigned long long i = p; i <= n; i *= p) {
        power += (n / i);
    }
    return power;
}

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


const InputType LOWER = 0;
const InputType UPPER = UINT_MAX;

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
SIMPLE_TEST(LargestPowerOf2DividesFactorialN, TestUPPER, UPPER - sizeof(UPPER) * CHAR_BIT, UPPER);

#ifdef __GNUC__
SIMPLE_BENCHMARK(LargestPowerOf2DividesFactorialNBuiltIn, LOWER);
SIMPLE_BENCHMARK(LargestPowerOf2DividesFactorialNBuiltIn, UPPER);
SIMPLE_BENCHMARK(LargestPowerOf2DividesFactorialNBuiltIn, 10);

SIMPLE_TEST(LargestPowerOf2DividesFactorialNBuiltIn, TestSAMPLE1, 0, 0);
SIMPLE_TEST(LargestPowerOf2DividesFactorialNBuiltIn, TestSAMPLE2, 8, 10);
SIMPLE_TEST(LargestPowerOf2DividesFactorialNBuiltIn, TestSAMPLE3, 97, 100);
SIMPLE_TEST(LargestPowerOf2DividesFactorialNBuiltIn, TestUPPER, UPPER - sizeof(UPPER) * CHAR_BIT,
            UPPER);

MUTUAL_RANDOM_TEST(LargestPowerOf2DividesFactorialN, LargestPowerOf2DividesFactorialNBuiltIn, 0,
                   96583);
#endif
