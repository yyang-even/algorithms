#include "common_header.h"

/** Efficient way to multiply with 7
 *
 * @reference   https://www.geeksforgeeks.org/efficient-way-to-multiply-with-7/
 *
 * We can multiply a number by 7 using bitwise operator. First left shift the
 * number by 3 bits (you will get 8n) then subtract the original number from
 * the shifted number and return the difference (8n – n).
 */
auto Multiply7(const unsigned n) {
    return (n << 3) - n;
}


SIMPLE_BENCHMARK(Multiply7, 4);

SIMPLE_TEST(Multiply7, TestSAMPLE1, 28, 4);
