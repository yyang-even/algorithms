#include "common_header.h"

#include "log_base_2.h"
#include "set_all_bits_after_most_significant_bit.h"


namespace {

/** Find the log base 2 of an integer with the MSB N set in O(N) operations (the obvious way)
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find the log base 2 of an integer with the MSB N set in O(N) operations (the obvious way)
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * The log base 2 of an integer is the same as the position of the highest bit set (or
 * most significant bit set, MSB).
 */
constexpr unsigned LogBase2(unsigned num) {
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
constexpr inline unsigned LogBase2_Float(const unsigned num) {
    union {
        unsigned int uNum[2];
        double dNum;
    } temp{};

    temp.uNum[__FLOAT_WORD_ORDER == LITTLE_ENDIAN] = 0x43300000;
    temp.uNum[__FLOAT_WORD_ORDER != LITTLE_ENDIAN] = num;
    temp.dNum -= 4503599627370496.0;
    return (temp.uNum[__FLOAT_WORD_ORDER == LITTLE_ENDIAN] >> 20) - 0x3FF;
}


/** Find the log base 2 of an N-bit integer in O(lg(N)) operations
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find the log base 2 of an N-bit integer in O(lg(N)) operations
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
constexpr auto LogBase2_LgN_Branch(uint32_t num) {
    constexpr unsigned int b[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000};
    constexpr unsigned int S[] = {1, 2, 4, 8, 16};

    unsigned result = 0;
    for (int i = 4; i >= 0; i--) {
        if (num & b[i]) {
            num >>= S[i];
            result |= S[i];
        }
    }

    return result;
}


constexpr inline auto LogBase2_LgN_NoBranch(uint32_t num) {
    unsigned result = (num > 0xFFFF) << 4;
    num >>= result;
    unsigned shift = (num > 0xFF) << 3;
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
constexpr inline unsigned
LogBase2_LgN_MultiplyAndLookup(const uint32_t num) {
    constexpr unsigned MultiplyDeBruijnBitPosition[32] = {
        0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
        8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
    };

    return MultiplyDeBruijnBitPosition[
            (uint32_t)(SetAllBitsAfterMSB(num) * 0x07C4ACDDU) >> 27];
}


/** Find integer log base 2 of a 32-bit IEEE float
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find integer log base 2 of a 32-bit IEEE float
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
constexpr inline int LogBase2_FloatInput(const float num) {
    static_assert(BitsNumber<decltype(num)> == 32, "float is not 32 bits.");

    int result{};
    memcpy(&result, &num, sizeof(result));
    return (result >> 23) - 127;
}


constexpr int LogBase2_IEEE754Float(const float num) {
    static_assert(BitsNumber<decltype(num)> == 32, "float is not 32 bits.");

    int x{};
    memcpy(&x, &num, sizeof(x));

    int result = x >> 23;

    if (result) {
        result -= 127;
    } else { // subnormal, so recompute using mantissa: c = intlog2(x) - 149;
        unsigned int t{};
        // Note that LogTable256 was defined earlier
        if ((t = x >> 16)) {
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
constexpr inline int LogBase2ofPow2r(const float num, const unsigned r) {
    static_assert(BitsNumber<decltype(num)> == 32, "float is not 32 bits.");

    int result{};
    memcpy(&result, &num, sizeof result);
    return ((((result - 0x3f800000) >> r) + 0x3f800000) >> 23) - 127;
}

}//namespace


constexpr uint32_t LOWER = 1;
constexpr auto UPPER = std::numeric_limits<uint32_t>::max();


THE_BENCHMARK(LogBase2, UPPER);

SIMPLE_TEST(LogBase2, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2, TestSAMPLE2, 4, 17);


THE_BENCHMARK(LogBase2_Float, UPPER);

SIMPLE_TEST(LogBase2_Float, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2_Float, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2_Float, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2_Float, TestSAMPLE2, 4, 17);

MUTUAL_RANDOM_TEST(LogBase2, LogBase2_Float, LOWER, UPPER);


THE_BENCHMARK(LogBase2_LookupTable, UPPER);

SIMPLE_TEST(LogBase2_LookupTable, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2_LookupTable, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2_LookupTable, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2_LookupTable, TestSAMPLE2, 4, 17);

MUTUAL_RANDOM_TEST(LogBase2_LookupTable, LogBase2_Float, LOWER, UPPER);


THE_BENCHMARK(LogBase2_LgN_Branch, UPPER);

SIMPLE_TEST(LogBase2_LgN_Branch, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2_LgN_Branch, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2_LgN_Branch, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2_LgN_Branch, TestSAMPLE2, 4, 17);

MUTUAL_RANDOM_TEST(LogBase2_LookupTable, LogBase2_LgN_Branch, LOWER, UPPER);


THE_BENCHMARK(LogBase2_LgN_NoBranch, UPPER);

SIMPLE_TEST(LogBase2_LgN_NoBranch, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2_LgN_NoBranch, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2_LgN_NoBranch, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2_LgN_NoBranch, TestSAMPLE2, 4, 17);

MUTUAL_RANDOM_TEST(LogBase2_LookupTable, LogBase2_LgN_NoBranch, LOWER, UPPER);


THE_BENCHMARK(LogBase2_LgN_MultiplyAndLookup, UPPER);

SIMPLE_TEST(LogBase2_LgN_MultiplyAndLookup, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2_LgN_MultiplyAndLookup, TestUPPER, 31, UPPER);
SIMPLE_TEST(LogBase2_LgN_MultiplyAndLookup, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2_LgN_MultiplyAndLookup, TestSAMPLE2, 4, 17);

MUTUAL_RANDOM_TEST(LogBase2_LookupTable, LogBase2_LgN_MultiplyAndLookup, LOWER, UPPER);


THE_BENCHMARK(LogBase2_FloatInput, UPPER);

SIMPLE_TEST(LogBase2_FloatInput, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2_FloatInput, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2_FloatInput, TestSAMPLE2, 4, 17);


THE_BENCHMARK(LogBase2_IEEE754Float, UPPER);

SIMPLE_TEST(LogBase2_IEEE754Float, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase2_IEEE754Float, TestSAMPLE1, 3, 8);
SIMPLE_TEST(LogBase2_IEEE754Float, TestSAMPLE2, 4, 17);


THE_BENCHMARK(LogBase2ofPow2r, UPPER, 0);

SIMPLE_TEST(LogBase2ofPow2r, TestLOWER, 0, LOWER, 0);
SIMPLE_TEST(LogBase2ofPow2r, TestSAMPLE1, 3, 8, 0);
SIMPLE_TEST(LogBase2ofPow2r, TestSAMPLE2, 4, 17, 0);
