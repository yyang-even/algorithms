#include "common_header.h"


namespace {

/** LCM - Least Common Multiple
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Exercise 4.2.
 *
 * The best way known to compute lcm(m, n) is to compute gcd(m, n) first and then to divide mn by the gcd.
 *
 * @reference   Program to find LCM of two numbers
 *              https://www.geeksforgeeks.org/program-to-find-lcm-of-two-numbers/
 *
 * LCM (Least Common Multiple) of two numbers is the smallest number which can be divided by both numbers.
 *
 * @reference   TCS Coding Practice Question | LCM of 2 Numbers
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-lcm-of-2-numbers/
 */
unsigned LCM(const unsigned m, const unsigned n) {
    return m * n / std::gcd(m, n);
}


/**
 * @reference   Program to find LCM of 2 numbers without using GCD
 *              https://www.geeksforgeeks.org/program-to-find-lcm-of-2-numbers-without-using-gcd/
 */
auto LCM_MOD(const unsigned m, const unsigned n) {
    const auto min_max_pair = std::minmax(m, n);

    auto lcm = min_max_pair.second;
    for (; lcm % min_max_pair.first != 0; lcm += min_max_pair.second);

    return lcm;
}

}//namespace


SIMPLE_BENCHMARK(LCM, 12, 18);
SIMPLE_BENCHMARK(LCM, 18, 12);

SIMPLE_TEST(LCM, Test1, 36u, 12, 18);
SIMPLE_TEST(LCM, Test2, 36u, 18, 12);


SIMPLE_BENCHMARK(LCM_MOD, 12, 18);
SIMPLE_BENCHMARK(LCM_MOD, 18, 12);

SIMPLE_TEST(LCM_MOD, Test1, 36u, 12, 18);
SIMPLE_TEST(LCM_MOD, Test2, 36u, 18, 12);