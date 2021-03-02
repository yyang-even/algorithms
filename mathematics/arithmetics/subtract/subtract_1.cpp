#include "common_header.h"

namespace {

/** Subtract 1 without arithmetic operators
 *
 * @reference   https://www.geeksforgeeks.org/subtract-1-without-arithmetic-operators/
 *
 * Write a program to subtract one from a given number. The use of operators like '+',
 * '-', '*', '/', '++', '--'... etc are not allowed.
 */
auto Subtract1(unsigned num) {
    unsigned mask = 1;
    for (; not(num & mask); mask <<= 1) {
        num ^= mask;
    }

    return num ^ mask;
}


auto Subtract1_Plus(const unsigned num) {
    return ((num << 1) + (~num));
}

}//namespace


THE_BENCHMARK(Subtract1, 3);

SIMPLE_TEST(Subtract1, TestSAMPLE1, 3u, 4);
SIMPLE_TEST(Subtract1, TestSAMPLE2, 9u, 10);
SIMPLE_TEST(Subtract1, TestSAMPLE3, -2u, -1);


THE_BENCHMARK(Subtract1_Plus, 3);

SIMPLE_TEST(Subtract1_Plus, TestSAMPLE1, 3u, 4);
SIMPLE_TEST(Subtract1_Plus, TestSAMPLE2, 9u, 10);
SIMPLE_TEST(Subtract1_Plus, TestSAMPLE3, -2u, -1);
