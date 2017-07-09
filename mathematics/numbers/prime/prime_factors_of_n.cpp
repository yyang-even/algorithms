#include "common_header.h"

char ToChar(const int digit) {
    return '0' + digit;
}

typedef unsigned InputType;
/** Prime Factors of N
 * @reference Ronald Graham, Oren Patashnik, Donald Knuth.
 *            Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 4.2.
 * Fundamental Theorem of Arithmetic: There's only one way to write n as a product of primes in
 * nondecreasing order.
 *
 * @reference http://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
 * Efficient program to print all prime factors of a given number.
 *
 * Given a number n, write an efficient function to print all prime factors of n.
 * For example, if the input number is 12, then output should be "2 2 3".
 * And if the input number is 315, then output should be "3 3 5 7".
 *
 * Following are the steps to find all prime factors.
 * 1) While n is divisible by 2, print 2 and divide n by 2.
 * 2) After step 1, n must be odd. Now start a loop from i = 3 to square root of n.
 * While i divides n, print i and divide n by i, increment i by 2 and continue.
 * 3) If n is a prime number and is greater than 2, then n will not become 1 by above two steps.
 * So print n if it is greater than 2.
 */
std::string PrintAllPrimeFactors(InputType N) {
    std::string output;
    if (N > 2) {
        while (N % 2 == 0) {
            output.push_back(ToChar(2));
            N /= 2;
        }

        const unsigned square_root = sqrt(double(N));
        for (unsigned i = 3; i <= square_root; i += 2) {
            while (N % i == 0) {
                output.push_back(ToChar(i));
                N /= i;
            }
        }

        if (N > 2) {
            output.push_back(ToChar(N));
        }
    }
    return output;
}


constexpr InputType LOWER = 1;
constexpr InputType SAMPLE1 = 12;
constexpr InputType SAMPLE2 = 315;

SIMPLE_BENCHMARK(PrintAllPrimeFactors, LOWER);
SIMPLE_BENCHMARK(PrintAllPrimeFactors, SAMPLE1);
RANDOM_BENCHMARK(PrintAllPrimeFactors, LOWER, std::numeric_limits<InputType>::max());

SIMPLE_TEST(PrintAllPrimeFactors, TestLOWER, "", LOWER);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE1, "223", SAMPLE1);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE2, "3357", SAMPLE2);
