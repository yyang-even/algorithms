#include "common_header.h"


namespace {

/** Compute modulus division by 1 << s without a division operator
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute modulus division by 1 << s without a division operator
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Compute modulus division by a power-of-2-number
 *              https://www.geeksforgeeks.org/compute-modulus-division-by-a-power-of-2-number/
 */
inline constexpr unsigned
Modulus2Power(const unsigned num, const unsigned s) {
    return num & ((1 << s) - 1);
}


/** Compute modulus division by (1 << s) - 1 without a division operator
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute modulus division by (1 << s) - 1 without a division operator
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
constexpr unsigned Modulus2PowerMinus1(unsigned num, const unsigned s) {
    unsigned result = num;
    const unsigned divisor = (1 << s) - 1;

    for (; num > divisor; num = result) {
        for (result = 0; num; num >>= s) {
            result += num & divisor;
        }
    }
    // Now result is a value from 0 to divisor, but since with modulus division we want result to be 0 when it is divisor.
    return result == divisor ? 0 : result;
}


/** Compute modulus division by (1 << s) - 1 in parallel without a division operator
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute modulus division by (1 << s) - 1 in parallel without a division operator
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
inline constexpr unsigned
Modulus2PowerMinus1_Parallel(uint32_t num, const unsigned s) {
    constexpr unsigned int M[] = {
        0x00000000, 0x55555555, 0x33333333, 0xc71c71c7,
        0x0f0f0f0f, 0xc1f07c1f, 0x3f03f03f, 0xf01fc07f,
        0x00ff00ff, 0x07fc01ff, 0x3ff003ff, 0xffc007ff,
        0xff000fff, 0xfc001fff, 0xf0003fff, 0xc0007fff,
        0x0000ffff, 0x0001ffff, 0x0003ffff, 0x0007ffff,
        0x000fffff, 0x001fffff, 0x003fffff, 0x007fffff,
        0x00ffffff, 0x01ffffff, 0x03ffffff, 0x07ffffff,
        0x0fffffff, 0x1fffffff, 0x3fffffff, 0x7fffffff
    };

    constexpr unsigned int Q[][6] = {
        { 0,  0,  0,  0,  0,  0}, {16,  8,  4,  2,  1,  1}, {16,  8,  4,  2,  2,  2},
        {15,  6,  3,  3,  3,  3}, {16,  8,  4,  4,  4,  4}, {15,  5,  5,  5,  5,  5},
        {12,  6,  6,  6,  6,  6}, {14,  7,  7,  7,  7,  7}, {16,  8,  8,  8,  8,  8},
        { 9,  9,  9,  9,  9,  9}, {10, 10, 10, 10, 10, 10}, {11, 11, 11, 11, 11, 11},
        {12, 12, 12, 12, 12, 12}, {13, 13, 13, 13, 13, 13}, {14, 14, 14, 14, 14, 14},
        {15, 15, 15, 15, 15, 15}, {16, 16, 16, 16, 16, 16}, {17, 17, 17, 17, 17, 17},
        {18, 18, 18, 18, 18, 18}, {19, 19, 19, 19, 19, 19}, {20, 20, 20, 20, 20, 20},
        {21, 21, 21, 21, 21, 21}, {22, 22, 22, 22, 22, 22}, {23, 23, 23, 23, 23, 23},
        {24, 24, 24, 24, 24, 24}, {25, 25, 25, 25, 25, 25}, {26, 26, 26, 26, 26, 26},
        {27, 27, 27, 27, 27, 27}, {28, 28, 28, 28, 28, 28}, {29, 29, 29, 29, 29, 29},
        {30, 30, 30, 30, 30, 30}, {31, 31, 31, 31, 31, 31}
    };

    constexpr unsigned int R[][6] = {
        {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
        {0x0000ffff, 0x000000ff, 0x0000000f, 0x00000003, 0x00000001, 0x00000001},
        {0x0000ffff, 0x000000ff, 0x0000000f, 0x00000003, 0x00000003, 0x00000003},
        {0x00007fff, 0x0000003f, 0x00000007, 0x00000007, 0x00000007, 0x00000007},
        {0x0000ffff, 0x000000ff, 0x0000000f, 0x0000000f, 0x0000000f, 0x0000000f},
        {0x00007fff, 0x0000001f, 0x0000001f, 0x0000001f, 0x0000001f, 0x0000001f},
        {0x00000fff, 0x0000003f, 0x0000003f, 0x0000003f, 0x0000003f, 0x0000003f},
        {0x00003fff, 0x0000007f, 0x0000007f, 0x0000007f, 0x0000007f, 0x0000007f},
        {0x0000ffff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff},
        {0x000001ff, 0x000001ff, 0x000001ff, 0x000001ff, 0x000001ff, 0x000001ff},
        {0x000003ff, 0x000003ff, 0x000003ff, 0x000003ff, 0x000003ff, 0x000003ff},
        {0x000007ff, 0x000007ff, 0x000007ff, 0x000007ff, 0x000007ff, 0x000007ff},
        {0x00000fff, 0x00000fff, 0x00000fff, 0x00000fff, 0x00000fff, 0x00000fff},
        {0x00001fff, 0x00001fff, 0x00001fff, 0x00001fff, 0x00001fff, 0x00001fff},
        {0x00003fff, 0x00003fff, 0x00003fff, 0x00003fff, 0x00003fff, 0x00003fff},
        {0x00007fff, 0x00007fff, 0x00007fff, 0x00007fff, 0x00007fff, 0x00007fff},
        {0x0000ffff, 0x0000ffff, 0x0000ffff, 0x0000ffff, 0x0000ffff, 0x0000ffff},
        {0x0001ffff, 0x0001ffff, 0x0001ffff, 0x0001ffff, 0x0001ffff, 0x0001ffff},
        {0x0003ffff, 0x0003ffff, 0x0003ffff, 0x0003ffff, 0x0003ffff, 0x0003ffff},
        {0x0007ffff, 0x0007ffff, 0x0007ffff, 0x0007ffff, 0x0007ffff, 0x0007ffff},
        {0x000fffff, 0x000fffff, 0x000fffff, 0x000fffff, 0x000fffff, 0x000fffff},
        {0x001fffff, 0x001fffff, 0x001fffff, 0x001fffff, 0x001fffff, 0x001fffff},
        {0x003fffff, 0x003fffff, 0x003fffff, 0x003fffff, 0x003fffff, 0x003fffff},
        {0x007fffff, 0x007fffff, 0x007fffff, 0x007fffff, 0x007fffff, 0x007fffff},
        {0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff},
        {0x01ffffff, 0x01ffffff, 0x01ffffff, 0x01ffffff, 0x01ffffff, 0x01ffffff},
        {0x03ffffff, 0x03ffffff, 0x03ffffff, 0x03ffffff, 0x03ffffff, 0x03ffffff},
        {0x07ffffff, 0x07ffffff, 0x07ffffff, 0x07ffffff, 0x07ffffff, 0x07ffffff},
        {0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff},
        {0x1fffffff, 0x1fffffff, 0x1fffffff, 0x1fffffff, 0x1fffffff, 0x1fffffff},
        {0x3fffffff, 0x3fffffff, 0x3fffffff, 0x3fffffff, 0x3fffffff, 0x3fffffff},
        {0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff}
    };

    // so divisor is either 1, 3, 7, 15, 31, ...).
    const unsigned int divisor = (1 << s) - 1;
    unsigned int result = (num & M[s]) + ((num >> s) & M[s]);

    for (const unsigned int *q = &Q[s][0], * r = &R[s][0]; result > divisor; q++, r++) {
        result = (result >> *q) + (result & *r);
    }
    // OR, less portably: result & -((signed)(result - divisor) >> s);
    return result == divisor ? 0 : result;
}

}//namespace


constexpr uint32_t LOWER = 0;
constexpr auto UPPER = BitsNumber<uint32_t> - 1;


THE_BENCHMARK(Modulus2Power, 1, UPPER);

SIMPLE_TEST(Modulus2Power, TestLOWER, LOWER, LOWER, LOWER);
SIMPLE_TEST(Modulus2Power, TestUPPER, UPPER, UPPER, UPPER);
SIMPLE_TEST(Modulus2Power, TestSAMPLE1, 51, 179, 7);
SIMPLE_TEST(Modulus2Power, TestSAMPLE2, 0, 708, 2);


THE_BENCHMARK(Modulus2PowerMinus1, 1, UPPER);

SIMPLE_TEST(Modulus2PowerMinus1, TestLOWER, LOWER, LOWER, LOWER);
SIMPLE_TEST(Modulus2PowerMinus1, TestUPPER, UPPER, UPPER, UPPER);
SIMPLE_TEST(Modulus2PowerMinus1, TestSAMPLE1, 52, 179, 7);
SIMPLE_TEST(Modulus2PowerMinus1, TestSAMPLE2, 0, 708, 2);


THE_BENCHMARK(Modulus2PowerMinus1_Parallel, 1, UPPER);

SIMPLE_TEST(Modulus2PowerMinus1_Parallel, TestLOWER, LOWER, LOWER, LOWER);
SIMPLE_TEST(Modulus2PowerMinus1_Parallel, TestUPPER, UPPER, UPPER, UPPER);
SIMPLE_TEST(Modulus2PowerMinus1_Parallel, TestSAMPLE1, 52, 179, 7);
SIMPLE_TEST(Modulus2PowerMinus1_Parallel, TestSAMPLE2, 0, 708, 2);
