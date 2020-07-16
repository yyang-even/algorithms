#include "common_header.h"

#include "factorial.h"
#include "mathematics/numbers/large_integer.h"

namespace {

typedef unsigned InputType;

/** Factorial
 *
 * @reference   Program for factorial of a number
 *              https://www.geeksforgeeks.org/program-for-factorial-of-a-number/
 * @reference   C Program for factorial of a number
 *              https://www.geeksforgeeks.org/c-program-for-factorial-of-a-number/
 * @reference   One line function for factorial of a number
 *              https://www.geeksforgeeks.org/one-line-function-for-factorial-of-a-number/
 *
 * Factorial of a non-negative integer, is multiplication of all integers
 * smaller than or equal to n.
 * For example factorial of 6 is 6*5*4*3*2*1 which is 720.
 */
unsigned long Factorial_Recursive(const InputType num) {
    if (num > 1) {
        return Factorial_Recursive(num - 1) * num;
    }
    return 1;
}


unsigned long Factorial_OneLine(const unsigned n) {
    return (n == 1u || n == 0u) ? 1u : n * Factorial_OneLine(n - 1);
}


/**
 * @reference   Tail Recursion
 *              https://www.geeksforgeeks.org/tail-recursion/
 */
unsigned long Factorial_TailRecursive(const InputType num, unsigned long factorial) {
    if (num < 2) {
        return factorial;
    }

    return Factorial_TailRecursive(num - 1, num * factorial);
}
unsigned long Factorial_TailRecursive(const InputType num) {
    return Factorial_TailRecursive(num, 1);
}


/**
 * @reference   Agner Fog. Optimizing software in C++. Section 14.1.
 */
auto Factorial_LookupTable(const unsigned n) {
    static const unsigned FACTORIAL_TABLE[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};
    assert(n < (sizeof(FACTORIAL_TABLE) / sizeof(*FACTORIAL_TABLE)));
    return FACTORIAL_TABLE[n];
}


/**
 * @reference   Factorial of a large number
 *              https://www.geeksforgeeks.org/factorial-large-number/
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

}//namespace


const InputType LOWER = 0;
const InputType UPPER = 12;
const InputType SAMPLE1 = 1;
const InputType SAMPLE2 = 6;


SIMPLE_BENCHMARK(Factorial_Iterative, LOWER);
SIMPLE_BENCHMARK(Factorial_Iterative, UPPER);
RANDOM_BENCHMARK(Factorial_Iterative, LOWER, UPPER);

SIMPLE_TEST(Factorial_Iterative, TestLOWER, 1u, LOWER);
SIMPLE_TEST(Factorial_Iterative, TestUPPER, 479001600u, UPPER);
SIMPLE_TEST(Factorial_Iterative, TestSAMPLE1, 1u, SAMPLE1);
SIMPLE_TEST(Factorial_Iterative, TestSAMPLE2, 720u, SAMPLE2);


SIMPLE_BENCHMARK(Factorial_OneLine, LOWER);
SIMPLE_BENCHMARK(Factorial_OneLine, UPPER);
RANDOM_BENCHMARK(Factorial_OneLine, LOWER, UPPER);

SIMPLE_TEST(Factorial_OneLine, TestLOWER, 1u, LOWER);
SIMPLE_TEST(Factorial_OneLine, TestUPPER, 479001600u, UPPER);
SIMPLE_TEST(Factorial_OneLine, TestSAMPLE1, 1u, SAMPLE1);
SIMPLE_TEST(Factorial_OneLine, TestSAMPLE2, 720u, SAMPLE2);


SIMPLE_BENCHMARK(Factorial_Recursive, LOWER);
SIMPLE_BENCHMARK(Factorial_Recursive, UPPER);
RANDOM_BENCHMARK(Factorial_Recursive, LOWER, UPPER);

SIMPLE_TEST(Factorial_Recursive, TestLOWER, 1u, LOWER);
SIMPLE_TEST(Factorial_Recursive, TestUPPER, 479001600u, UPPER);
SIMPLE_TEST(Factorial_Recursive, TestSAMPLE1, 1u, SAMPLE1);
SIMPLE_TEST(Factorial_Recursive, TestSAMPLE2, 720u, SAMPLE2);


SIMPLE_BENCHMARK(Factorial_TailRecursive, LOWER);
SIMPLE_BENCHMARK(Factorial_TailRecursive, UPPER);
RANDOM_BENCHMARK(Factorial_TailRecursive, LOWER, UPPER);

SIMPLE_TEST(Factorial_TailRecursive, TestLOWER, 1u, LOWER);
SIMPLE_TEST(Factorial_TailRecursive, TestUPPER, 479001600u, UPPER);
SIMPLE_TEST(Factorial_TailRecursive, TestSAMPLE1, 1u, SAMPLE1);
SIMPLE_TEST(Factorial_TailRecursive, TestSAMPLE2, 720u, SAMPLE2);


SIMPLE_BENCHMARK(Factorial_LookupTable, LOWER);
SIMPLE_BENCHMARK(Factorial_LookupTable, UPPER);
RANDOM_BENCHMARK(Factorial_LookupTable, LOWER, UPPER);

SIMPLE_TEST(Factorial_LookupTable, TestLOWER, 1u, LOWER);
SIMPLE_TEST(Factorial_LookupTable, TestUPPER, 479001600u, UPPER);
SIMPLE_TEST(Factorial_LookupTable, TestSAMPLE1, 1u, SAMPLE1);
SIMPLE_TEST(Factorial_LookupTable, TestSAMPLE2, 720u, SAMPLE2);


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
