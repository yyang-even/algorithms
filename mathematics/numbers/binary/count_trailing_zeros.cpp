#include "common_header.h"

typedef unsigned InputType;

/** Count the consecutive zero bits (trailing) on the right linearly
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count the consecutive zero bits (trailing) on the right linearly
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Count num's trailing zero bits, so if v is 1101000 (base 2), then the output will be 3
 */
auto CountTrailingZerosLinear(InputType num) {
    InputType result = 0;
    if (num) {
        num = (num ^ (num - 1)) >> 1;  // Set num's trailing 0s to 1s and zero rest
        for (; num; ++result) {
            num >>= 1;
        }
    } else {
        result = Bits_Number<decltype(num)>();
    }
    return result;
}


/** Count the consecutive zero bits (trailing) on the right in parallel
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count the consecutive zero bits (trailing) on the right in parallel
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
auto CountTrailingZerosParallel(InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    InputType result = 32; // c will be the number of zero bits on the right
    num &= -signed(num);
    if (num) {
        --result;
    }
    if (num & 0x0000FFFF) {
        result -= 16;
    }
    if (num & 0x00FF00FF) {
        result -= 8;
    }
    if (num & 0x0F0F0F0F) {
        result -= 4;
    }
    if (num & 0x33333333) {
        result -= 2;
    }
    if (num & 0x55555555) {
        --result;
    }

    return result;
}


/** Count the consecutive zero bits (trailing) on the right by binary search
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count the consecutive zero bits (trailing) on the right by binary search
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
auto CountTrailingZerosBinarySearch(InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    InputType result;
    if (num == 0) {
        result = 32;
    } else if (num & 0x1) {
        result = 0;
    } else {
        result = 1;
        if ((num & 0xffff) == 0) {
            num >>= 16;
            result += 16;
        }
        if ((num & 0xff) == 0) {
            num >>= 8;
            result += 8;
        }
        if ((num & 0xf) == 0) {
            num >>= 4;
            result += 4;
        }
        if ((num & 0x3) == 0) {
            num >>= 2;
            result += 2;
        }
        result -= num & 0x1;
    }
    return result;
}


/** Count the consecutive zero bits (trailing) on the right by casting to a float
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count the consecutive zero bits (trailing) on the right by casting to a float
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
InputType CountTrailingZerosFloat(const InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    if (num) {
        const float f_num = (float)(num & -num);
        return (*(uint32_t *)&f_num >> 23) - 0x7f;
    } else {
        return 32;
    }
}


/** Count the consecutive zero bits (trailing) on the right with modulus division and lookup
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count the consecutive zero bits (trailing) on the right with modulus division and lookup
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
auto CountTrailingZerosModulusAndLookup(const InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    static constexpr InputType Mod37BitPosition[] = { // map a bit value mod 37 to its position
        32, 0, 1, 26, 2, 23, 27, 0, 3, 16, 24, 30, 28, 11, 0, 13, 4,
        7, 17, 0, 25, 22, 31, 15, 29, 10, 12, 6, 0, 21, 14, 9, 5,
        20, 8, 19, 18
    };
    return Mod37BitPosition[(-num & num) % 37];
}


/** Count the consecutive zero bits (trailing) on the right with multiply and lookup
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count the consecutive zero bits (trailing) on the right with multiply and lookup
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
auto CountTrailingZerosMultiplyAndLookup(const InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    static constexpr InputType MultiplyDeBruijnBitPosition[32] = {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    return num ? MultiplyDeBruijnBitPosition[((uint32_t)((num & -num) * 0x077CB531U)) >> 27] : 32;
}


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();
constexpr InputType NUM_BITS = Bits_Number<InputType>();

SIMPLE_BENCHMARK(CountTrailingZerosLinear, UPPER);
SIMPLE_BENCHMARK(CountTrailingZerosLinear, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZerosLinear, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZerosLinear, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZerosLinear, TestWorstCase, NUM_BITS - 1, 1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZerosLinear, TestSAMPLE1, 3, 0b1101000);

SIMPLE_BENCHMARK(CountTrailingZerosParallel, UPPER);
SIMPLE_BENCHMARK(CountTrailingZerosParallel, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZerosParallel, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZerosParallel, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZerosParallel, TestWorstCase, NUM_BITS - 1, 1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZerosParallel, TestSAMPLE1, 3, 0b1101000);

MUTUAL_RANDOM_TEST(CountTrailingZerosLinear, CountTrailingZerosParallel, LOWER, UPPER);

SIMPLE_BENCHMARK(CountTrailingZerosBinarySearch, UPPER);
SIMPLE_BENCHMARK(CountTrailingZerosBinarySearch, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZerosBinarySearch, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZerosBinarySearch, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZerosBinarySearch, TestWorstCase, NUM_BITS - 1, 1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZerosBinarySearch, TestSAMPLE1, 3, 0b1101000);

MUTUAL_RANDOM_TEST(CountTrailingZerosLinear, CountTrailingZerosBinarySearch, LOWER, UPPER);

SIMPLE_BENCHMARK(CountTrailingZerosFloat, UPPER);
SIMPLE_BENCHMARK(CountTrailingZerosFloat, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZerosFloat, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZerosFloat, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZerosFloat, TestWorstCase, NUM_BITS - 1, 1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZerosFloat, TestSAMPLE1, 3, 0b1101000);

SIMPLE_BENCHMARK(CountTrailingZerosModulusAndLookup, UPPER);
SIMPLE_BENCHMARK(CountTrailingZerosModulusAndLookup, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZerosModulusAndLookup, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZerosModulusAndLookup, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZerosModulusAndLookup, TestWorstCase, NUM_BITS - 1, 1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZerosModulusAndLookup, TestSAMPLE1, 3, 0b1101000);

MUTUAL_RANDOM_TEST(CountTrailingZerosLinear, CountTrailingZerosModulusAndLookup, LOWER, UPPER);

SIMPLE_BENCHMARK(CountTrailingZerosMultiplyAndLookup, UPPER);
SIMPLE_BENCHMARK(CountTrailingZerosMultiplyAndLookup, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZerosMultiplyAndLookup, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZerosMultiplyAndLookup, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZerosMultiplyAndLookup, TestWorstCase, NUM_BITS - 1, 1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZerosMultiplyAndLookup, TestSAMPLE1, 3, 0b1101000);

MUTUAL_RANDOM_TEST(CountTrailingZerosLinear, CountTrailingZerosMultiplyAndLookup, LOWER, UPPER);

#ifdef __GNUG__
/** Builtin functions of GCC compiler
 *
 * @reference   https://www.geeksforgeeks.org/builtin-functions-gcc-compiler/
 */
MUTUAL_RANDOM_TEST(__builtin_ctz, CountTrailingZerosMultiplyAndLookup, LOWER, UPPER);
#endif
