#include "common_header.h"

typedef int InputType;

/** Sign extending
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Sign extending from a constant bit-width
 *              Sign extending from a variable bit-width
 *              Sign extending from a variable bit-width in 3 operations
 *              https://graphics.stanford.edu/~seander/bithacks.html
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


const InputType SAMPLE1 = 0b0000; //0
const InputType SAMPLE2 = 0b0001; //1
const InputType SAMPLE3 = 0b1111; //-1
const InputType SAMPLE4 = 0b1000; //-8
const InputType SAMPLE5 = 0b0111; //7

SIMPLE_BENCHMARK(SignExtendConst4Bits, 1);
SIMPLE_BENCHMARK(SignExtendConst4Bits, 0);
SIMPLE_BENCHMARK(SignExtendConst4Bits, INT_MIN);
SIMPLE_BENCHMARK(SignExtendConst4Bits, UINT_MAX);

SIMPLE_TEST(SignExtendConst4Bits, TestSample1, 0, SAMPLE1);
SIMPLE_TEST(SignExtendConst4Bits, TestSample2, 1, SAMPLE2);
SIMPLE_TEST(SignExtendConst4Bits, TestSample3, -1, SAMPLE3);
SIMPLE_TEST(SignExtendConst4Bits, TestSample4, -8, SAMPLE4);
SIMPLE_TEST(SignExtendConst4Bits, TestSample5, 7, SAMPLE5);
SIMPLE_TEST(SignExtendConst4Bits, TestSample6, 0, INT_MIN);
SIMPLE_TEST(SignExtendConst4Bits, TestSample7, -1, INT_MAX);

SIMPLE_BENCHMARK(SignExtendVariable4Bits, 1);
SIMPLE_BENCHMARK(SignExtendVariable4Bits, 0);
SIMPLE_BENCHMARK(SignExtendVariable4Bits, INT_MIN);
SIMPLE_BENCHMARK(SignExtendVariable4Bits, UINT_MAX);

SIMPLE_TEST(SignExtendVariable4Bits, TestSample1, 0, SAMPLE1);
SIMPLE_TEST(SignExtendVariable4Bits, TestSample2, 1, SAMPLE2);
SIMPLE_TEST(SignExtendVariable4Bits, TestSample3, -1, SAMPLE3);
SIMPLE_TEST(SignExtendVariable4Bits, TestSample4, -8, SAMPLE4);
SIMPLE_TEST(SignExtendVariable4Bits, TestSample5, 7, SAMPLE5);
SIMPLE_TEST(SignExtendVariable4Bits, TestSample6, 0, INT_MIN);
SIMPLE_TEST(SignExtendVariable4Bits, TestSample7, -1, INT_MAX);

SIMPLE_BENCHMARK(SignExtendVariableDirty4Bits, 1);
SIMPLE_BENCHMARK(SignExtendVariableDirty4Bits, 0);
SIMPLE_BENCHMARK(SignExtendVariableDirty4Bits, INT_MIN);
SIMPLE_BENCHMARK(SignExtendVariableDirty4Bits, UINT_MAX);

SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample1, 0, SAMPLE1);
SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample2, 1, SAMPLE2);
SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample3, -1, SAMPLE3);
SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample4, -8, SAMPLE4);
SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample5, 7, SAMPLE5);
SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample6, 0, INT_MIN);
SIMPLE_TEST(SignExtendVariableDirty4Bits, TestSample7, -1, INT_MAX);

MUTUAL_RANDOM_TEST(SignExtendConst4Bits, SignExtendVariable4Bits, INT_MIN, INT_MAX);
MUTUAL_RANDOM_TEST(SignExtendConst4Bits, SignExtendVariableDirty4Bits, INT_MIN, INT_MAX);
MUTUAL_RANDOM_TEST(SignExtendVariableDirty4Bits, SignExtendVariable4Bits, INT_MIN, INT_MAX);
