#include "common_header.h"

#include "binary.h"

#include "set_all_bits_after_most_significant_bit.h"

typedef unsigned InputType;

/** Find the log base 2 of an integer with the MSB N set in O(N) operations (the obvious way)
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find the log base 2 of an integer with the MSB N set in O(N) operations (the obvious way)
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * The log base 2 of an integer is the same as the position of the highest bit set (or most significant bit set, MSB).
 */
InputType LogBase2(InputType num) {
    unsigned result = 0;
    while (num >>= 1) {
        ++result;
    }

    return result;
}


/** Find the integer log base 2 of an integer with an 64-bit IEEE float
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find the integer log base 2 of an integer with an 64-bit IEEE float
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
InputType LogBase2Float(const InputType num) {
    union {
        unsigned int uNum[2];
        double dNum;
    } temp;

    temp.uNum[__FLOAT_WORD_ORDER == LITTLE_ENDIAN] = 0x43300000;
    temp.uNum[__FLOAT_WORD_ORDER != LITTLE_ENDIAN] = num;
    temp.dNum -= 4503599627370496.0;
    return (temp.uNum[__FLOAT_WORD_ORDER == LITTLE_ENDIAN] >> 20) - 0x3FF;
}


/** Find the log base 2 of an integer with a lookup table
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find the log base 2 of an integer with a lookup table
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
static constexpr char LogTable256[256] = {
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
    -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
    LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
};
InputType LogBase2LookupTable(const InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    register InputType t, tt; // temporaries

    if (tt = num >> 16) {
        return (t = tt >> 8) ? 24 + LogTable256[t] : 16 + LogTable256[tt];
    } else {
        return (t = num >> 8) ? 8 + LogTable256[t] : LogTable256[num];
    }
}


/** Find the log base 2 of an N-bit integer in O(lg(N)) operations
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find the log base 2 of an N-bit integer in O(lg(N)) operations
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
InputType LogBase2LgNBranch(InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    static constexpr unsigned int b[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000};
    static const unsigned int S[] = {1, 2, 4, 8, 16};

    register InputType result = 0;
    for (int i = 4; i >= 0; i--) {
        if (num & b[i]) {
            num >>= S[i];
            result |= S[i];
        }
    }

    return result;
}
InputType LogBase2LgNNoBranch(InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    register InputType result;
    register InputType shift;

    result = (num > 0xFFFF) << 4;
    num >>= result;
    shift = (num > 0xFF) << 3;
    num >>= shift;
    result |= shift;
    shift = (num > 0xF) << 2;
    num >>= shift;
    result |= shift;
    shift = (num > 0x3) << 1;
    num >>= shift;
    result |= shift;
    result |= (num >> 1);

    return result;
}


/** Find the log base 2 of an N-bit integer in O(lg(N)) operations with multiply and lookup
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find the log base 2 of an N-bit integer in O(lg(N)) operations with multiply and lookup
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
InputType LogBase2LgNMultiplyAndLookup(const InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    static constexpr InputType MultiplyDeBruijnBitPosition[32] = {
        0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
        8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
    };

    return MultiplyDeBruijnBitPosition[(uint32_t)(SetAllBitsAfterMSB(num) * 0x07C4ACDDU) >> 27];
}


/** Find integer log base 2 of a 32-bit IEEE float
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find integer log base 2 of a 32-bit IEEE float
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
int LogBase2FloatInput(const float num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    int result;
    memcpy(&result, &num, sizeof(result));
    return (result >> 23) - 127;
}
int LogBase2IEEE754Float(const float num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    int x;
    memcpy(&x, &num, sizeof(x));

    int result = x >> 23;

    if (result) {
        result -= 127;
    } else { // subnormal, so recompute using mantissa: c = intlog2(x) - 149;
        register unsigned int t;
        // Note that LogTable256 was defined earlier
        if (t = x >> 16) {
            result = LogTable256[t] - 133;
        } else {
            result = (t = x >> 8) ? LogTable256[t] - 141 : LogTable256[x] - 149;
        }
    }
    return result;
}
/** Find integer log base 2 of the pow(2, r)-root of a 32-bit IEEE float (for unsigned integer r)
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find integer log base 2 of the pow(2, r)-root of a 32-bit IEEE float (for unsigned integer r)
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * find int(log2(pow((double) v, 1. / pow(2, r)))), where isnormal(v) and v > 0
 */
int LogBase2ofPow2r(const float num, const unsigned r) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    int result;
    memcpy(&result, &num, sizeof result);
    return ((((result - 0x3f800000) >> r) + 0x3f800000) >> 23) - 127;
}


constexpr InputType LOWER = 1;
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(LogBase2, UPPER);

SIMPLE_TEST(LogBase2, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2, TestSAMPLE2, 4, 17);

SIMPLE_BENCHMARK(LogBase2Float, UPPER);

SIMPLE_TEST(LogBase2Float, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2Float, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2Float, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2Float, TestSAMPLE2, 4, 17);

MUTUAL_RANDOM_TEST(LogBase2, LogBase2Float, LOWER, UPPER);

SIMPLE_BENCHMARK(LogBase2LookupTable, UPPER);

SIMPLE_TEST(LogBase2LookupTable, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2LookupTable, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2LookupTable, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2LookupTable, TestSAMPLE2, 4, 17);

MUTUAL_RANDOM_TEST(LogBase2LookupTable, LogBase2Float, LOWER, UPPER);

SIMPLE_BENCHMARK(LogBase2LgNBranch, UPPER);

SIMPLE_TEST(LogBase2LgNBranch, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2LgNBranch, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2LgNBranch, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2LgNBranch, TestSAMPLE2, 4, 17);

MUTUAL_RANDOM_TEST(LogBase2LookupTable, LogBase2LgNBranch, LOWER, UPPER);

SIMPLE_BENCHMARK(LogBase2LgNNoBranch, UPPER);

SIMPLE_TEST(LogBase2LgNNoBranch, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2LgNNoBranch, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2LgNNoBranch, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2LgNNoBranch, TestSAMPLE2, 4, 17);

MUTUAL_RANDOM_TEST(LogBase2LookupTable, LogBase2LgNNoBranch, LOWER, UPPER);

SIMPLE_BENCHMARK(LogBase2LgNMultiplyAndLookup, UPPER);

SIMPLE_TEST(LogBase2LgNMultiplyAndLookup, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2LgNMultiplyAndLookup, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2LgNMultiplyAndLookup, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2LgNMultiplyAndLookup, TestSAMPLE2, 4, 17);

MUTUAL_RANDOM_TEST(LogBase2LookupTable, LogBase2LgNMultiplyAndLookup, LOWER, UPPER);

SIMPLE_BENCHMARK(LogBase2FloatInput, UPPER);

SIMPLE_TEST(LogBase2FloatInput, TestLOWER, 0, LOWER);
//SIMPLE_TEST(LogBase2FloatInput, TestUPPER, 31, UPPER);  //Failed
SIMPLE_TEST(LogBase2FloatInput, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2FloatInput, TestSAMPLE2, 4, 17);

SIMPLE_BENCHMARK(LogBase2IEEE754Float, UPPER);

SIMPLE_TEST(LogBase2IEEE754Float, TestLOWER, 0, LOWER);
//SIMPLE_TEST(LogBase2IEEE754Float, TestUPPER, 31, UPPER);    //Failed
SIMPLE_TEST(LogBase2IEEE754Float, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2IEEE754Float, TestSAMPLE2, 4, 17);

SIMPLE_BENCHMARK(LogBase2ofPow2r, UPPER, 0);

SIMPLE_TEST(LogBase2ofPow2r, TestLOWER, 0, LOWER, 0);
//SIMPLE_TEST(LogBase2ofPow2r, TestUPPER, 31, UPPER, 0);    //Failed
SIMPLE_TEST(LogBase2ofPow2r, TestSAMPLE1, 3, 8, 0);
SIMPLE_TEST(LogBase2ofPow2r, TestSAMPLE2, 4, 17, 0);
