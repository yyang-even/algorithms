#include "common_header.h"

typedef int InputType;

/** Sign extending
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Sign extending from a constant bit-width
 *              Sign extending from a variable bit-width
 *              Sign extending from a variable bit-width in 3 operations
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Sign extension is automatic for built-in types, such as chars and ints.
 * But suppose you have a signed two's complement number, x, that is stored
 * using only b bits. Moreover, suppose you want to convert x to an int,
 * which has more than b bits. A simple copy will work if x is positive,
 * but if negative, the sign must be extended. For example, if we have only
 * 4 bits to store a number, then -3 is represented as 1101 in binary.
 * If we have 8 bits, then -3 is 11111101. The most-significant bit of
 * the 4-bit representation is replicated sinistrally to fill in the
 * destination when we convert to a representation with more bits;
 * this is sign extending.
 */
template <unsigned B>
inline InputType SignExtendConst(const InputType x) {
    struct {
    InputType x:
        B;
    } bits;
    return bits.x = x;
}
InputType SignExtendConst4Bits(const InputType x) {
    return SignExtendConst<4>(x);
}

template <unsigned B>
inline InputType SignExtendVariable(InputType x) {
    static const InputType mask = 1U << (B - 1);
    x = x & ((1U << B) - 1);
    return (x ^ mask) - mask;
}
InputType SignExtendVariable4Bits(InputType x) {
    return SignExtendVariable<4>(x);
}

template <unsigned B>
inline InputType SignExtendVariableDirty(const InputType x) {
    static const InputType mask = CHAR_BIT * sizeof(x) - B;
    return (x << mask) >> mask;
}
InputType SignExtendVariableDirty4Bits(InputType x) {
    return SignExtendVariableDirty<4>(x);
}


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();
constexpr InputType SAMPLE1 = 0b0000; //0
constexpr InputType SAMPLE2 = 0b0001; //1
constexpr InputType SAMPLE3 = 0b1111; //-1
constexpr InputType SAMPLE4 = 0b1000; //-8
constexpr InputType SAMPLE5 = 0b0111; //7

SIMPLE_BENCHMARK(SignExtendConst4Bits, 1);
SIMPLE_BENCHMARK(SignExtendConst4Bits, 0);
SIMPLE_BENCHMARK(SignExtendConst4Bits, LOWER);
SIMPLE_BENCHMARK(SignExtendConst4Bits, std::numeric_limits<unsigned>::max());

SIMPLE_TEST(SignExtendConst4Bits, TestSample1, 0, SAMPLE1);
SIMPLE_TEST(SignExtendConst4Bits, TestSample2, 1, SAMPLE2);
SIMPLE_TEST(SignExtendConst4Bits, TestSample3, -1, SAMPLE3);
SIMPLE_TEST(SignExtendConst4Bits, TestSample4, -8, SAMPLE4);
SIMPLE_TEST(SignExtendConst4Bits, TestSample5, 7, SAMPLE5);
SIMPLE_TEST(SignExtendConst4Bits, TestSample6, 0, LOWER);
SIMPLE_TEST(SignExtendConst4Bits, TestSample7, -1, UPPER);

SIMPLE_BENCHMARK(SignExtendVariable4Bits, 1);
SIMPLE_BENCHMARK(SignExtendVariable4Bits, 0);
SIMPLE_BENCHMARK(SignExtendVariable4Bits, LOWER);
SIMPLE_BENCHMARK(SignExtendVariable4Bits, std::numeric_limits<unsigned>::max());

SIMPLE_TEST(SignExtendVariable4Bits, TestSample1, 0, SAMPLE1);
SIMPLE_TEST(SignExtendVariable4Bits, TestSample2, 1, SAMPLE2);
SIMPLE_TEST(SignExtendVariable4Bits, TestSample3, -1, SAMPLE3);
SIMPLE_TEST(SignExtendVariable4Bits, TestSample4, -8, SAMPLE4);
SIMPLE_TEST(SignExtendVariable4Bits, TestSample5, 7, SAMPLE5);
SIMPLE_TEST(SignExtendVariable4Bits, TestSample6, 0, LOWER);
SIMPLE_TEST(SignExtendVariable4Bits, TestSample7, -1, UPPER);

SIMPLE_BENCHMARK(SignExtendVariableDirty4Bits, 1);
SIMPLE_BENCHMARK(SignExtendVariableDirty4Bits, 0);
SIMPLE_BENCHMARK(SignExtendVariableDirty4Bits, LOWER);
SIMPLE_BENCHMARK(SignExtendVariableDirty4Bits, std::numeric_limits<unsigned>::max());

SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample1, 0, SAMPLE1);
SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample2, 1, SAMPLE2);
SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample3, -1, SAMPLE3);
SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample4, -8, SAMPLE4);
SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample5, 7, SAMPLE5);
SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample6, 0, LOWER);
SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample7, -1, UPPER);

MUTUAL_RANDOM_TEST(SignExtendConst4Bits, SignExtendVariable4Bits, LOWER, UPPER);
MUTUAL_RANDOM_TEST(SignExtendConst4Bits, SignExtendVariableDirty4Bits, LOWER, UPPER);
MUTUAL_RANDOM_TEST(SignExtendVariableDirty4Bits, SignExtendVariable4Bits, LOWER, UPPER);
