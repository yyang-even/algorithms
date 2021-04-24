#include "common_header.h"

#include "swap_odd_even_bits.h"
#include "swap_nibbles.h"
#include "text/reverse.h"

#include "mathematics/numbers/reverse_digits.h"


namespace {

/** Reverse bits
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Reverse bits the obvious way
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Write an Efficient C Program to Reverse Bits of a Number
 *              https://www.geeksforgeeks.org/write-an-efficient-c-program-to-reverse-bits-of-a-number/
 */
auto ReverseBits(unsigned num) {
    auto size = BitsNumber<decltype(num)> - 1;
    auto ret = num;
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
auto ReverseBits_32_LookupTable(const uint32_t num) {
    static const unsigned char BitReverseTable256[256] = {
#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
        R6(0), R6(2), R6(1), R6(3)
    };

    unsigned ret = 0;
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
unsigned char ReverseBitsInByte_3(const unsigned char byte) {
    return (byte * 0x0202020202ULL & 0x010884422010ULL) % 1023;
}


/** Reverse the bits in a byte with 4 operations (64-bit multiply, no division)
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Reverse the bits in a byte with 4 operations (64-bit multiply, no division)
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
unsigned char ReverseBitsInByte_4(const unsigned char byte) {
    return ((byte * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
}


/** Reverse the bits in a byte with 7 operations (no 64-bit)
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Reverse the bits in a byte with 7 operations (no 64-bit)
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
unsigned char ReverseBitsInByte_7(const unsigned char byte) {
    return ((byte * 0x0802LU & 0x22110LU) | (byte * 0x8020LU & 0x88440LU)) *
           0x10101LU >>
           16;
}


/** Reverse an N-bit quantity in parallel in 5 * lg(N) operations
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Reverse an N-bit quantity in parallel in 5 * lg(N) operations
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
auto ReverseBits_32_Parallel(uint32_t num) {
    // swap odd and even bits
    num = SwapOddAndEvenBits(num);
    // swap consecutive pairs
    num = ((num >> 2) & 0x33333333) | ((num & 0x33333333) << 2);
    // swap nibbles ...
    num = SwapNibbles(num);
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
T ReverseNBits_Parallel(T num) {
    auto size = BitsNumber<T>; // bit size; must be power of 2
    T mask = ~0;
    while ((size >>= 1) > 0) {
        mask ^= (mask << size);
        num = ((num >> size) & mask) | ((num << size) & ~mask);
    }

    return num;
}

unsigned ReverseNBits_Parallel_Uint32(uint32_t num) {
    return ReverseNBits_Parallel(num);
}


/** Bit manipulation | Swap Endianness of a number
 *
 * @reference   https://www.geeksforgeeks.org/bit-manipulation-swap-endianness-of-a-number/
 */
auto ReverseBytes_String(unsigned num) {
    auto *begin = reinterpret_cast<unsigned char *>(&num);

    Reverse_TwoPointers(begin, begin + sizeof(num),
    [](auto & lhs, auto & rhs) {
        std::swap(lhs, rhs);
    });

    return num;
}


/**
 * @reference   Reverse bytes of a Hexadecimal Number
 *              https://www.geeksforgeeks.org/reverse-bytes-of-a-hexadecimal-number/
 */
auto ReverseBytes_Shift(const unsigned num) {
    return (num << 24) |
           (((num >> 16) << 24) >> 16) |
           (((num << 16) >> 24) << 16) |
           (num >> 24);
}


/** Reverse actual bits of the given number
 *
 * @reference   https://www.geeksforgeeks.org/reverse-actual-bits-given-number/
 *
 * Given a non-negative integer n. The problem is to reverse the bits of n and print the
 * number obtained after reversing the bits. Note that the actual binary representation
 * of the number is being considered for reversing the bits, no leading 0’s are being
 * considered.
 */
auto ReverseActualBits(const unsigned number) {
    return ReverseDigits(number, 2);
}

}//namespace


constexpr auto LOWER = std::numeric_limits<uint32_t>::min();
constexpr auto UPPER = std::numeric_limits<uint32_t>::max();


SIMPLE_BENCHMARK(ReverseBits, Sample1, UPPER);

SIMPLE_TEST(ReverseBits, TestLOWER, LOWER, LOWER);
SIMPLE_TEST(ReverseBits, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(ReverseBits, TestSAMPLE1, 0XB0000000u, 0b1101);
SIMPLE_TEST(ReverseBits, TestSAMPLE2, 0X80u, 0X01000000);


SIMPLE_BENCHMARK(ReverseBits_32_LookupTable, Sample1, UPPER);

SIMPLE_TEST(ReverseBits_32_LookupTable, TestLOWER, LOWER, LOWER);
SIMPLE_TEST(ReverseBits_32_LookupTable, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(ReverseBits_32_LookupTable, TestSAMPLE1, 0XB0000000u, 0b1101);
SIMPLE_TEST(ReverseBits_32_LookupTable, TestSAMPLE2, 0X80u, 0X01000000);

MUTUAL_RANDOM_TEST(ReverseBits, ReverseBits_32_LookupTable, LOWER, UPPER);


SIMPLE_BENCHMARK(ReverseBitsInByte_3, Sample1, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(ReverseBitsInByte_3, TestLOWER, static_cast<unsigned char>(0),
            static_cast<unsigned char>(LOWER));
SIMPLE_TEST(ReverseBitsInByte_3, TestUPPER, static_cast<unsigned char>(0XFF),
            static_cast<unsigned char>(UPPER));
SIMPLE_TEST(ReverseBitsInByte_3, TestSAMPLE1, static_cast<unsigned char>(0XB0),
            static_cast<unsigned char>(0b1101));
SIMPLE_TEST(ReverseBitsInByte_3, TestSAMPLE2, static_cast<unsigned char>(0X80),
            static_cast<unsigned char>(0X01));


SIMPLE_BENCHMARK(ReverseBitsInByte_4, Sample1, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(ReverseBitsInByte_4, TestLOWER, static_cast<unsigned char>(0),
            static_cast<unsigned char>(LOWER));
SIMPLE_TEST(ReverseBitsInByte_4, TestUPPER, static_cast<unsigned char>(0XFF),
            static_cast<unsigned char>(UPPER));
SIMPLE_TEST(ReverseBitsInByte_4, TestSAMPLE1, static_cast<unsigned char>(0XB0),
            static_cast<unsigned char>(0b1101));
SIMPLE_TEST(ReverseBitsInByte_4, TestSAMPLE2, static_cast<unsigned char>(0X80),
            static_cast<unsigned char>(0X01));

MUTUAL_RANDOM_TEST(ReverseBitsInByte_3, ReverseBitsInByte_4, LOWER, UPPER);


SIMPLE_BENCHMARK(ReverseBitsInByte_7, Sample1, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(ReverseBitsInByte_7, TestLOWER, 0u, LOWER);
SIMPLE_TEST(ReverseBitsInByte_7, TestUPPER, 0XFFu, static_cast<unsigned char>(UPPER));
SIMPLE_TEST(ReverseBitsInByte_7, TestSAMPLE1, 0XB0u, 0b1101);
SIMPLE_TEST(ReverseBitsInByte_7, TestSAMPLE2, 0X80u, 0X01);

MUTUAL_RANDOM_TEST(ReverseBitsInByte_7, ReverseBitsInByte_4, LOWER, UPPER);


SIMPLE_BENCHMARK(ReverseBits_32_Parallel, Sample1, UPPER);

SIMPLE_TEST(ReverseBits_32_Parallel, TestLOWER, LOWER, LOWER);
SIMPLE_TEST(ReverseBits_32_Parallel, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(ReverseBits_32_Parallel, TestSAMPLE1, 0XB0000000u, 0b1101);
SIMPLE_TEST(ReverseBits_32_Parallel, TestSAMPLE2, 0X80u, 0X01000000);

MUTUAL_RANDOM_TEST(ReverseBits, ReverseBits_32_Parallel, LOWER, UPPER);


SIMPLE_BENCHMARK(ReverseNBits_Parallel_Uint32, Sample1, UPPER);

SIMPLE_TEST(ReverseNBits_Parallel_Uint32, TestLOWER, LOWER, LOWER);
SIMPLE_TEST(ReverseNBits_Parallel_Uint32, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(ReverseNBits_Parallel_Uint32, TestSAMPLE1, 0XB0000000u, 0b1101);
SIMPLE_TEST(ReverseNBits_Parallel_Uint32, TestSAMPLE2, 0X80u, 0X01000000);

MUTUAL_RANDOM_TEST(ReverseBits, ReverseNBits_Parallel_Uint32, LOWER, UPPER);


SIMPLE_BENCHMARK(ReverseBytes_String, Sample1, 0x12345678);

SIMPLE_TEST(ReverseBytes_String, TestSAMPLE1, 0x78563412u, 0x12345678);
SIMPLE_TEST(ReverseBytes_String, TestSAMPLE2, 0x21436587u, 0x87654321);


SIMPLE_BENCHMARK(ReverseBytes_Shift, Sample1, 0x12345678);

SIMPLE_TEST(ReverseBytes_Shift, TestSAMPLE1, 0x78563412u, 0x12345678);
SIMPLE_TEST(ReverseBytes_Shift, TestSAMPLE2, 0x21436587u, 0x87654321);


SIMPLE_BENCHMARK(ReverseActualBits, Sample1, 0x12345678);

SIMPLE_TEST(ReverseActualBits, TestSAMPLE1, 0b1101, 0b1011);
SIMPLE_TEST(ReverseActualBits, TestSAMPLE2, 0b101, 0b1010);
