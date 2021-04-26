#include "common_header.h"


namespace {

/** Computing parity the naive way
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Computing parity the naive way
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Program to find parity
 *              https://www.geeksforgeeks.org/program-to-find-parity/
 *
 * 1 if an odd number of bits set, 0 otherwise.
 */
auto Parity_BrianKernighan(unsigned n) {
    bool parity = false;  // parity will be the parity of n

    while (n) {
        parity = !parity;
        n = n & (n - 1);
    }

    return parity;
}


/** Compute parity by lookup table
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute parity by lookup table
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Compute the parity of a number using XOR and table look-up
 *              https://www.geeksforgeeks.org/compute-parity-number-using-xor-table-look/
 */
auto Parity_LookupTable(const unsigned n) {
    static const bool ParityTable256[256] = {
#   define P2(n) n, n^1, n^1, n
#   define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
#   define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
        P6(0), P6(1), P6(1), P6(0)
    };

    const unsigned char *byte = reinterpret_cast<const unsigned char *>(&n);
    unsigned char parity = 0;
    for (size_t i = 0; i < sizeof(n); ++i) {
        parity ^= byte[i];
    }
    return ParityTable256[parity];
}


/** Compute parity of a byte using 64-bit multiply and modulus division
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute parity of a byte using 64-bit multiply and modulus division
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
bool ParityOfByte_64bit(const unsigned char n) {
    return (((n * 0x0101010101010101ULL) & 0x8040201008040201ULL) % 0x1FF) & 1;
}


/** Compute parity of word with a multiply
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute parity of word with a multiply
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
bool Parity_Multiply_32(uint32_t n) {
    n ^= n >> 1;
    n ^= n >> 2;
    n = (n & 0x11111111U) * 0x11111111U;
    return (n >> 28) & 1;
}


bool Parity_Multiply_64(uint64_t n) {
    n ^= n >> 1;
    n ^= n >> 2;
    n = (n & 0x1111111111111111UL) * 0x1111111111111111UL;
    return (n >> 60) & 1;
}


/** Compute parity in parallel
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute parity in parallel
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *              Finding the Parity of a number Efficiently
 *              https://www.geeksforgeeks.org/finding-the-parity-of-a-number-efficiently/
 */
bool Parity_Parallel(uint32_t n) {
    n ^= n >> 16;
    n ^= n >> 8;
    n ^= n >> 4;
    n &= 0xf;
    return (0x6996 >> n) & 1;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<uint32_t>::min();
constexpr auto UPPER = std::numeric_limits<uint32_t>::max();


SIMPLE_BENCHMARK(Parity_BrianKernighan, Sample1, LOWER);
SIMPLE_BENCHMARK(Parity_BrianKernighan, Sample2, UPPER);

SIMPLE_TEST(Parity_BrianKernighan, TestLOWER, false, LOWER);
SIMPLE_TEST(Parity_BrianKernighan, TestUPPER, false, UPPER);
SIMPLE_TEST(Parity_BrianKernighan, TestSAMPLE1, false, 6);
SIMPLE_TEST(Parity_BrianKernighan, TestSAMPLE2, true, 13);


SIMPLE_BENCHMARK(Parity_LookupTable, Sample1, LOWER);
SIMPLE_BENCHMARK(Parity_LookupTable, Sample2, UPPER);

SIMPLE_TEST(Parity_LookupTable, TestLOWER, false, LOWER);
SIMPLE_TEST(Parity_LookupTable, TestUPPER, false, UPPER);
SIMPLE_TEST(Parity_LookupTable, TestSAMPLE1, false, 6);
SIMPLE_TEST(Parity_LookupTable, TestSAMPLE2, true, 13);

MUTUAL_RANDOM_TEST(Parity_BrianKernighan, Parity_LookupTable, LOWER, UPPER);


SIMPLE_BENCHMARK(ParityOfByte_64bit, Sample1, LOWER);
SIMPLE_BENCHMARK(ParityOfByte_64bit, Sample2, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(ParityOfByte_64bit, TestLOWER, false, LOWER);
SIMPLE_TEST(ParityOfByte_64bit, TestUPPER, false, static_cast<unsigned char>(UPPER));
SIMPLE_TEST(ParityOfByte_64bit, TestSAMPLE1, false, 6);
SIMPLE_TEST(ParityOfByte_64bit, TestSAMPLE2, true, 13);


SIMPLE_BENCHMARK(Parity_Multiply_32, Sample1, LOWER);
SIMPLE_BENCHMARK(Parity_Multiply_32, Sample2, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(Parity_Multiply_32, TestLOWER, false, LOWER);
SIMPLE_TEST(Parity_Multiply_32, TestUPPER, false, static_cast<unsigned char>(UPPER));
SIMPLE_TEST(Parity_Multiply_32, TestSAMPLE1, false, 6);
SIMPLE_TEST(Parity_Multiply_32, TestSAMPLE2, true, 13);


SIMPLE_BENCHMARK(Parity_Multiply_64, Sample1, LOWER);
SIMPLE_BENCHMARK(Parity_Multiply_64, Sample2, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(Parity_Multiply_64, TestLOWER, false, LOWER);
SIMPLE_TEST(Parity_Multiply_64, TestUPPER, false, static_cast<unsigned char>(UPPER));
SIMPLE_TEST(Parity_Multiply_64, TestSAMPLE1, false, 6);
SIMPLE_TEST(Parity_Multiply_64, TestSAMPLE2, true, 13);

MUTUAL_RANDOM_TEST(Parity_BrianKernighan, Parity_Multiply_32, LOWER, UPPER);
MUTUAL_RANDOM_TEST(Parity_Multiply_32, Parity_Multiply_64, LOWER, UPPER);


SIMPLE_BENCHMARK(Parity_Parallel, Sample1, LOWER);
SIMPLE_BENCHMARK(Parity_Parallel, Sample2, static_cast<unsigned char>(UPPER));

SIMPLE_TEST(Parity_Parallel, TestLOWER, false, LOWER);
SIMPLE_TEST(Parity_Parallel, TestUPPER, false, static_cast<unsigned char>(UPPER));
SIMPLE_TEST(Parity_Parallel, TestSAMPLE1, false, 6);
SIMPLE_TEST(Parity_Parallel, TestSAMPLE2, true, 13);

MUTUAL_RANDOM_TEST(Parity_BrianKernighan, Parity_Parallel, LOWER, UPPER);


#ifdef __GNUG__
/** Builtin functions of GCC compiler
 *
 * @reference   https://www.geeksforgeeks.org/builtin-functions-gcc-compiler/
 */
MUTUAL_RANDOM_TEST(Parity_BrianKernighan, __builtin_parity, LOWER, UPPER);
#endif
