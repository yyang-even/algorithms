#include "common_header.h"

#include "swap_odd_even_bits.h"

typedef unsigned InputType;

/** Reverse bits
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Reverse bits the obvious way
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Write an Efficient C Program to Reverse Bits of a Number
 *              https://www.geeksforgeeks.org/write-an-efficient-c-program-to-reverse-bits-of-a-number/
 */
InputType Reverse32Bits(InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    auto size = Bits_Number<decltype(num)>() - 1;
    InputType ret = num;
    for (num >>= 1; num; num >>= 1) {
        ret <<= 1;
        ret |= (num & 1);
        --size;
    }
    return ret << size;
}

/** Reverse bits in word by lookup table
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Reverse bits in word by lookup table
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Reverse bits using lookup table in O(1) time
 *              https://www.geeksforgeeks.org/reverse-bits-using-lookup-table-in-o1-time/
 */
InputType Reverse32BitsLookupTable(const InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    static const unsigned char BitReverseTable256[256] = {
#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
        R6(0), R6(2), R6(1), R6(3)
    };

    InputType ret = 0;
    auto *num_ptr = reinterpret_cast<const unsigned char *>(&num);
    unsigned char *ret_ptr = reinterpret_cast<unsigned char *>(&ret);

    ret_ptr[3] = BitReverseTable256[num_ptr[0]];
    ret_ptr[2] = BitReverseTable256[num_ptr[1]];
    ret_ptr[1] = BitReverseTable256[num_ptr[2]];
    ret_ptr[0] = BitReverseTable256[num_ptr[3]];

    return ret;
}

/** Reverse the bits in a byte with 3 operations (64-bit multiply and modulus division)
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Reverse the bits in a byte with 3 operations (64-bit multiply and modulus division)
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
unsigned char ReverseBitsInByte3(const unsigned char byte) {
    return (byte * 0x0202020202ULL & 0x010884422010ULL) % 1023;
}

/** Reverse the bits in a byte with 4 operations (64-bit multiply, no division)
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Reverse the bits in a byte with 4 operations (64-bit multiply, no division)
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
unsigned char ReverseBitsInByte4(const unsigned char byte) {
    return ((byte * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
}

/** Reverse the bits in a byte with 7 operations (no 64-bit)
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Reverse the bits in a byte with 7 operations (no 64-bit)
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
unsigned char ReverseBitsInByte7(const unsigned char byte) {
    return ((byte * 0x0802LU & 0x22110LU) | (byte * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
}

/** Reverse an N-bit quantity in parallel in 5 * lg(N) operations
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Reverse an N-bit quantity in parallel in 5 * lg(N) operations
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
InputType Reverse32BitsParallel(InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    // swap odd and even bits
    num = SwapOddAndEvenBits(num);
    // swap consecutive pairs
    num = ((num >> 2) & 0x33333333) | ((num & 0x33333333) << 2);
    // swap nibbles ...
    num = ((num >> 4) & 0x0F0F0F0F) | ((num & 0x0F0F0F0F) << 4);
    // swap bytes
    num = ((num >> 8) & 0x00FF00FF) | ((num & 0x00FF00FF) << 8);
    // swap 2-byte long pairs
    num = (num >> 16) | (num               << 16);

    return num;
}

/** Reverse an N-bit quantity in parallel in 5 * lg(N) operations
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Reverse an N-bit quantity in parallel in 5 * lg(N) operations
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
template <typename T>
T ReverseNBitsParallel(T num) {
    T size = Bits_Number<T>(); // bit size; must be power of 2
    T mask = ~0;
    while ((size >>= 1) > 0) {
        mask ^= (mask << size);
        num = ((num >> size) & mask) | ((num << size) & ~mask);
    }

    return num;
}
InputType ReverseNBitsParallelUint32(InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    return ReverseNBitsParallel(num);
}


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(Reverse32Bits, UPPER);

SIMPLE_TEST(Reverse32Bits, TestLOWER, LOWER, LOWER);
SIMPLE_TEST(Reverse32Bits, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(Reverse32Bits, TestSAMPLE1, 0XB0000000, 0b1101);
SIMPLE_TEST(Reverse32Bits, TestSAMPLE2, 0X80, 0X01000000);

SIMPLE_BENCHMARK(Reverse32BitsLookupTable, UPPER);

SIMPLE_TEST(Reverse32BitsLookupTable, TestLOWER, LOWER, LOWER);
SIMPLE_TEST(Reverse32BitsLookupTable, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(Reverse32BitsLookupTable, TestSAMPLE1, 0XB0000000, 0b1101);
SIMPLE_TEST(Reverse32BitsLookupTable, TestSAMPLE2, 0X80, 0X01000000);

MUTUAL_RANDOM_TEST(Reverse32Bits, Reverse32BitsLookupTable, LOWER, UPPER);


SIMPLE_BENCHMARK(ReverseBitsInByte3, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(ReverseBitsInByte3, TestLOWER, static_cast<unsigned char>(0),
            static_cast<unsigned char>(LOWER));
SIMPLE_TEST(ReverseBitsInByte3, TestUPPER, static_cast<unsigned char>(0XFF),
            static_cast<unsigned char>(UPPER));
SIMPLE_TEST(ReverseBitsInByte3, TestSAMPLE1, static_cast<unsigned char>(0XB0),
            static_cast<unsigned char>(0b1101));
SIMPLE_TEST(ReverseBitsInByte3, TestSAMPLE2, static_cast<unsigned char>(0X80),
            static_cast<unsigned char>(0X01));

SIMPLE_BENCHMARK(ReverseBitsInByte4, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(ReverseBitsInByte4, TestLOWER, static_cast<unsigned char>(0),
            static_cast<unsigned char>(LOWER));
SIMPLE_TEST(ReverseBitsInByte4, TestUPPER, static_cast<unsigned char>(0XFF),
            static_cast<unsigned char>(UPPER));
SIMPLE_TEST(ReverseBitsInByte4, TestSAMPLE1, static_cast<unsigned char>(0XB0),
            static_cast<unsigned char>(0b1101));
SIMPLE_TEST(ReverseBitsInByte4, TestSAMPLE2, static_cast<unsigned char>(0X80),
            static_cast<unsigned char>(0X01));

MUTUAL_RANDOM_TEST(ReverseBitsInByte3, ReverseBitsInByte4, LOWER, UPPER);

SIMPLE_BENCHMARK(ReverseBitsInByte7, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(ReverseBitsInByte7, TestLOWER, 0, LOWER);
SIMPLE_TEST(ReverseBitsInByte7, TestUPPER, 0XFF, static_cast<unsigned char>(UPPER));
SIMPLE_TEST(ReverseBitsInByte7, TestSAMPLE1, 0XB0, 0b1101);
SIMPLE_TEST(ReverseBitsInByte7, TestSAMPLE2, 0X80, 0X01);

MUTUAL_RANDOM_TEST(ReverseBitsInByte7, ReverseBitsInByte4, LOWER, UPPER);

SIMPLE_BENCHMARK(Reverse32BitsParallel, UPPER);

SIMPLE_TEST(Reverse32BitsParallel, TestLOWER, LOWER, LOWER);
SIMPLE_TEST(Reverse32BitsParallel, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(Reverse32BitsParallel, TestSAMPLE1, 0XB0000000, 0b1101);
SIMPLE_TEST(Reverse32BitsParallel, TestSAMPLE2, 0X80, 0X01000000);

MUTUAL_RANDOM_TEST(Reverse32Bits, Reverse32BitsParallel, LOWER, UPPER);

SIMPLE_BENCHMARK(ReverseNBitsParallelUint32, UPPER);

SIMPLE_TEST(ReverseNBitsParallelUint32, TestLOWER, LOWER, LOWER);
SIMPLE_TEST(ReverseNBitsParallelUint32, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(ReverseNBitsParallelUint32, TestSAMPLE1, 0XB0000000, 0b1101);
SIMPLE_TEST(ReverseNBitsParallelUint32, TestSAMPLE2, 0X80, 0X01000000);

MUTUAL_RANDOM_TEST(Reverse32Bits, ReverseNBitsParallelUint32, LOWER, UPPER);
