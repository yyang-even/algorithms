#include "common_header.h"

typedef unsigned InputType;

/** Factorial
 * @reference   C Program for factorial of a number
 *              http://quiz.geeksforgeeks.org/c-program-factorial-number/
 *
 * Factorial of a non-negative integer, is multiplication of all integers
 * smaller than or equal to n.
 * For example factorial of 6 is 6*5*4*3*2*1 which is 720.
 */
unsigned long FactorialIterative(unsigned num) {
    unsigned long result = 1;
    for (; num > 1; --num) {
        result *= num;
    }
    return result;
}

unsigned long FactorialRecursive(const unsigned num) {
    if (num > 1) {
        return FactorialRecursive(num - 1) * num;
    }
    return 1;
}


const InputType LOWER = 0;
const InputType UPPER = 12;
const InputType SAMPLE1 = 1;
const InputType SAMPLE2 = 6;

SIMPLE_BENCHMARK(FactorialIterative, LOWER);
SIMPLE_BENCHMARK(FactorialIterative, UPPER);
RANDOM_BENCHMARK(FactorialIterative, LOWER, UPPER);

SIMPLE_TEST(FactorialIterative, TestLOWER, 1, LOWER);
SIMPLE_TEST(FactorialIterative, TestUPPER, 479001600, UPPER);
SIMPLE_TEST(FactorialIterative, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(FactorialIterative, TestSAMPLE2, 720, SAMPLE2);

SIMPLE_BENCHMARK(FactorialRecursive, LOWER);
SIMPLE_BENCHMARK(FactorialRecursive, UPPER);
RANDOM_BENCHMARK(FactorialRecursive, LOWER, UPPER);

SIMPLE_TEST(FactorialRecursive, TestLOWER, 1, LOWER);
SIMPLE_TEST(FactorialRecursive, TestUPPER, 479001600, UPPER);
SIMPLE_TEST(FactorialRecursive, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(FactorialRecursive, TestSAMPLE2, 720, SAMPLE2);
