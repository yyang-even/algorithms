#include "common_header.h"

#include "count_set_bits.h"


namespace {

/** Count number of bits to be flipped to convert A to B
 *
 * @reference   https://www.geeksforgeeks.org/count-number-of-bits-to-be-flipped-to-convert-a-to-b/
 * @reference   Number of mismatching bits in the binary representation of two integers
 *              https://www.geeksforgeeks.org/number-of-mismatching-bits-in-the-binary-representation-of-two-integers/
 * @reference   Count number of bits to be flipped to convert A to B | Set-2
 *              https://www.geeksforgeeks.org/count-number-of-bits-to-be-flipped-to-convert-a-to-b-set-2/
 *
 * Given two numbers 'a' and 'b'. Write a program to count number of bits needed to be
 * flipped to convert 'a' to 'b'.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 5.5.
 */
inline constexpr auto CountDiffBits(const unsigned a, const unsigned b) {
    return CountSetBits_BrianKernighan(a ^ b);
}

}//namespace


THE_BENCHMARK(CountDiffBits, 10, 20);

SIMPLE_TEST(CountDiffBits, TestSample1, 4, 10, 20);
SIMPLE_TEST(CountDiffBits, TestSample2, 3, 10, 7);
SIMPLE_TEST(CountDiffBits, TestSample3, 2, 12, 15);
SIMPLE_TEST(CountDiffBits, TestSample4, 3, 3, 16);
