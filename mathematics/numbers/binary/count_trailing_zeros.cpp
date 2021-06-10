#include "common_header.h"

#include "binary.h"
#include "count_trailing_zeros.h"


namespace {

/** Count the consecutive zero bits (trailing) on the right in parallel
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count the consecutive zero bits (trailing) on the right in parallel
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
constexpr auto CountTrailingZeros_Parallel(uint32_t num) {
    unsigned result = 32; // c will be the number of zero bits on the right
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
constexpr auto CountTrailingZeros_BinarySearch(uint32_t num) {
    unsigned result{};
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
inline constexpr unsigned CountTrailingZeros_Float(const uint32_t num) {
    if (num) {
        FloatUnsignedUnion float_unsigned_union{};
        float_unsigned_union.f = static_cast<float>(num & -num);
        return (float_unsigned_union.u >> 23) - 0x7f;
    } else {
        return 32;
    }
}


/** Count the consecutive zero bits (trailing) on the right with modulus division and lookup
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count the consecutive zero bits (trailing) on the right with modulus division and lookup
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Count trailing zero bits using lookup table
 *              https://www.geeksforgeeks.org/count-trailing-zero-bits-using-lookup-table/
 */
inline constexpr auto CountTrailingZeros_ModulusAndLookup(const uint32_t num) {
    constexpr unsigned Mod37BitPosition[] = {
        // map a bit value mod 37 to its position
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
inline constexpr auto CountTrailingZeros_MultiplyAndLookup(const uint32_t num) {
    constexpr unsigned MultiplyDeBruijnBitPosition[32] = {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    return num ?
           MultiplyDeBruijnBitPosition[((uint32_t)((num & -num) * 0x077CB531)) >> 27] :
           32;
}


/** Count number of trailing zeros in Binary representation of a number using Bitset
 *
 * @reference   https://www.geeksforgeeks.org/count-number-of-trailing-zeros-in-binary-representation-of-a-number-using-bitset/
 */
constexpr auto CountTrailingZeros_Bitset(const unsigned num) {
    std::bitset<BitsNumber<decltype(num)>> binary_num{num};

    unsigned count = 0;
    for (std::size_t i = 0; i < binary_num.size(); ++i) {
        if (binary_num[i] == 0) {
            ++count;
        } else {
            break;
        }
    }

    return count;
}


/**
 * @reference   Check divisibility of binary string by 2^k
 *              https://www.geeksforgeeks.org/check-divisibility-binary-string-2k/
 */


/** Count number of bits changed after adding 1 to given N
 *
 * @reference   https://www.geeksforgeeks.org/count-number-of-bits-changed-after-adding-1-to-given-n/
 */
inline constexpr auto CountChangedBitsAfterAdd1(const unsigned N) {
    return CountSetBits_BrianKernighan(N ^ (N + 1));
}

}//namespace


constexpr auto LOWER = std::numeric_limits<uint32_t>::min();
constexpr auto UPPER = std::numeric_limits<uint32_t>::max();
constexpr auto NUM_BITS = BitsNumber<uint32_t>;


SIMPLE_BENCHMARK(CountTrailingZeros_Linear, Sample1, UPPER);
SIMPLE_BENCHMARK(CountTrailingZeros_Linear, Sample2, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZeros_Linear, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZeros_Linear, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZeros_Linear, TestWorstCase, NUM_BITS - 1,
            1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZeros_Linear, TestSAMPLE1, 3, 0b1101000);
SIMPLE_TEST(CountTrailingZeros_Linear, TestSAMPLE2, 4, 16);
SIMPLE_TEST(CountTrailingZeros_Linear, TestSAMPLE3, 6, 64);


SIMPLE_BENCHMARK(CountTrailingZeros_Parallel, Sample1, UPPER);
SIMPLE_BENCHMARK(CountTrailingZeros_Parallel, Sample2, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZeros_Parallel, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZeros_Parallel, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZeros_Parallel, TestWorstCase, NUM_BITS - 1,
            1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZeros_Parallel, TestSAMPLE1, 3, 0b1101000);

MUTUAL_RANDOM_TEST(CountTrailingZeros_Linear, CountTrailingZeros_Parallel,
                   LOWER, UPPER);


SIMPLE_BENCHMARK(CountTrailingZeros_BinarySearch, Sample1, UPPER);
SIMPLE_BENCHMARK(CountTrailingZeros_BinarySearch, Sample2, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZeros_BinarySearch, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZeros_BinarySearch, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZeros_BinarySearch, TestWorstCase, NUM_BITS - 1,
            1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZeros_BinarySearch, TestSAMPLE1, 3, 0b1101000);

MUTUAL_RANDOM_TEST(CountTrailingZeros_Linear, CountTrailingZeros_BinarySearch,
                   LOWER, UPPER);


SIMPLE_BENCHMARK(CountTrailingZeros_Float, Sample1, UPPER);
SIMPLE_BENCHMARK(CountTrailingZeros_Float, Sample2, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZeros_Float, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZeros_Float, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZeros_Float, TestWorstCase, NUM_BITS - 1, 1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZeros_Float, TestSAMPLE1, 3, 0b1101000);


SIMPLE_BENCHMARK(CountTrailingZeros_ModulusAndLookup, Sample1, UPPER);
SIMPLE_BENCHMARK(CountTrailingZeros_ModulusAndLookup, Sample2, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZeros_ModulusAndLookup, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZeros_ModulusAndLookup, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZeros_ModulusAndLookup, TestWorstCase, NUM_BITS - 1,
            1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZeros_ModulusAndLookup, TestSAMPLE1, 3, 0b1101000);

MUTUAL_RANDOM_TEST(CountTrailingZeros_Linear, CountTrailingZeros_ModulusAndLookup,
                   LOWER, UPPER);


SIMPLE_BENCHMARK(CountTrailingZeros_MultiplyAndLookup, Sample1, UPPER);
SIMPLE_BENCHMARK(CountTrailingZeros_MultiplyAndLookup, Sample2, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZeros_MultiplyAndLookup, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZeros_MultiplyAndLookup, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZeros_MultiplyAndLookup, TestWorstCase, NUM_BITS - 1,
            1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZeros_MultiplyAndLookup, TestSAMPLE1, 3, 0b1101000);

MUTUAL_RANDOM_TEST(CountTrailingZeros_Linear, CountTrailingZeros_MultiplyAndLookup,
                   LOWER, UPPER);


#ifdef __GNUG__
/** Builtin functions of GCC compiler
 *
 * @reference   https://www.geeksforgeeks.org/builtin-functions-gcc-compiler/
 */
MUTUAL_RANDOM_TEST(__builtin_ctz, CountTrailingZeros_MultiplyAndLookup, LOWER, UPPER);
#endif


SIMPLE_BENCHMARK(CountTrailingZeros_Bitset, Sample1, UPPER);
SIMPLE_BENCHMARK(CountTrailingZeros_Bitset, Sample2, 1 << (NUM_BITS - 1));

SIMPLE_TEST(CountTrailingZeros_Bitset, TestLOWER, NUM_BITS, LOWER);
SIMPLE_TEST(CountTrailingZeros_Bitset, TestUPPER, 0, UPPER);
SIMPLE_TEST(CountTrailingZeros_Bitset, TestWorstCase, NUM_BITS - 1,
            1 << (NUM_BITS - 1));
SIMPLE_TEST(CountTrailingZeros_Bitset, TestSAMPLE1, 3, 0b1101000);
SIMPLE_TEST(CountTrailingZeros_Bitset, TestSAMPLE2, 4, 16);
SIMPLE_TEST(CountTrailingZeros_Bitset, TestSAMPLE3, 6, 64);

MUTUAL_RANDOM_TEST(CountTrailingZeros_Linear, CountTrailingZeros_Bitset, LOWER, UPPER);


THE_BENCHMARK(CountChangedBitsAfterAdd1, 5);

SIMPLE_TEST(CountChangedBitsAfterAdd1, TestSAMPLE1, 2, 5);
SIMPLE_TEST(CountChangedBitsAfterAdd1, TestSAMPLE2, 2, 1);
SIMPLE_TEST(CountChangedBitsAfterAdd1, TestSAMPLE3, 1, 0);
