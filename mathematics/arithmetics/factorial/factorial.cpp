#include "common_header.h"

#include "factorial.h"
#include "mathematics/numbers/numbers.h"

typedef unsigned InputType;

/** Factorial
 * @reference   C Program for factorial of a number
 *              http://quiz.geeksforgeeks.org/c-program-factorial-number/
 *
 * Factorial of a non-negative integer, is multiplication of all integers
 * smaller than or equal to n.
 * For example factorial of 6 is 6*5*4*3*2*1 which is 720.
 */
unsigned long FactorialRecursive(const InputType num) {
    if (num > 1) {
        return FactorialRecursive(num - 1) * num;
    }
    return 1;
}

/**
 * @reference   Tail Recursion
 *              http://www.geeksforgeeks.org/tail-recursion/
 */
unsigned long FactorialTailRecursive(const InputType num, unsigned long factorial) {
    if (num < 2) {
        return factorial;
    }

    return FactorialTailRecursive(num - 1, num * factorial);
}
unsigned long FactorialTailRecursive(const InputType num) {
    return FactorialTailRecursive(num, 1);
}

/**
 * @reference   Factorial of a large number
 *              http://www.geeksforgeeks.org/factorial-large-number/
 *
 * How to compute factorial of 100 using a C/C++ program?
 * Factorial of 100 has 158 digits. It is not possible to store these many digits
 * even if we use long long int. Following is a simple solution where we use an
 * array to store individual digits of the result. The idea is to use basic
 * mathematics for multiplication.
 */
std::string FactorialOfLargeNumber(const InputType num) {
    LargeInteger result("1");
    for (InputType i = 2; i <= num; ++i) {
        result = result * i;
    }
    return result.ToString();
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

SIMPLE_BENCHMARK(FactorialTailRecursive, LOWER);
SIMPLE_BENCHMARK(FactorialTailRecursive, UPPER);
RANDOM_BENCHMARK(FactorialTailRecursive, LOWER, UPPER);

SIMPLE_TEST(FactorialTailRecursive, TestLOWER, 1, LOWER);
SIMPLE_TEST(FactorialTailRecursive, TestUPPER, 479001600, UPPER);
SIMPLE_TEST(FactorialTailRecursive, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(FactorialTailRecursive, TestSAMPLE2, 720, SAMPLE2);

SIMPLE_BENCHMARK(FactorialOfLargeNumber, LOWER);
SIMPLE_BENCHMARK(FactorialOfLargeNumber, UPPER);
RANDOM_BENCHMARK(FactorialOfLargeNumber, LOWER, 300);

SIMPLE_TEST(FactorialOfLargeNumber, TestLOWER, "1", LOWER);
SIMPLE_TEST(FactorialOfLargeNumber, TestUPPER, "479001600", UPPER);
SIMPLE_TEST(FactorialOfLargeNumber, TestSAMPLE1, "1", SAMPLE1);
SIMPLE_TEST(FactorialOfLargeNumber, TestSAMPLE2, "720", SAMPLE2);
SIMPLE_TEST(FactorialOfLargeNumber, TestSAMPLE3,
            "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000",
            100);
