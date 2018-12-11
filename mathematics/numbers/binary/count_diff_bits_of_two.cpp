#include "common_header.h"

#include "binary.h"

typedef unsigned InputType;

/** Count number of bits to be flipped to convert A to B
 *
 * @reference   https://www.geeksforgeeks.org/count-number-of-bits-to-be-flipped-to-convert-a-to-b/
 * @reference   Number of mismatching bits in the binary representation of two integers
 *              https://www.geeksforgeeks.org/number-of-mismatching-bits-in-the-binary-representation-of-two-integers/
 *
 * Given two numbers ‘a’ and b’. Write a program to count number of bits needed to be flipped to convert ‘a’ to ‘b’.
 */
auto CountDiffBits(const InputType a, const InputType b) {
    return CountSetBitsBrianKernighan(a ^ b);
}


SIMPLE_BENCHMARK(CountDiffBits, 10, 20);

SIMPLE_TEST(CountDiffBits, TestSample1, 4, 10, 20);
SIMPLE_TEST(CountDiffBits, TestSample2, 3, 10, 7);
SIMPLE_TEST(CountDiffBits, TestSample3, 2, 12, 15);
SIMPLE_TEST(CountDiffBits, TestSample4, 3, 3, 16);
