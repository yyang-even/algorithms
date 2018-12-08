#include "common_header.h"

/** Subtract 1 without arithmetic operators
 *
 * @reference   https://www.geeksforgeeks.org/subtract-1-without-arithmetic-operators/
 *
 * Write a program to subtract one from a given number. The use of operators
 * like ‘+’, ‘-‘, ‘*’, ‘/’, ‘++’, ‘–‘ …etc are not allowed.
 */
auto Subtract1(int num) {
    int mask = 1;
    for (; not(num & mask); mask <<= 1) {
        num ^= mask;
    }

    return    num ^ mask;
}


SIMPLE_BENCHMARK(Subtract1, 3);

SIMPLE_TEST(Subtract1, TestSAMPLE1, 3, 4);
SIMPLE_TEST(Subtract1, TestSAMPLE2, 9, 10);
SIMPLE_TEST(Subtract1, TestSAMPLE3, -2, -1);
