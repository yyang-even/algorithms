#pragma once


/** GCD - Greatest Common Divisor
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 4.1.
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 31.2.
 * @reference   Euclidean algorithms (Basic and Extended)
 *              https://www.geeksforgeeks.org/euclidean-algorithms-basic-and-extended/
 * @reference   C Program for Basic Euclidean algorithms
 *              https://www.geeksforgeeks.org/c-program-for-basic-and-extended-euclidean-algorithms/
 * @reference   C Program for Extended Euclidean algorithms
 *              https://www.geeksforgeeks.org/c-program-for-basic-and-extended-euclidean-algorithms-2/
 * @reference   Program to find HCF (Highest Common Factor) of 2 Numbers
 *              https://www.geeksforgeeks.org/program-to-find-hcf-highest-common-factor-of-2-numbers/
 * @reference   Program to find GCD or HCF of two numbers using Middle School Procedure
 *              https://www.geeksforgeeks.org/program-to-find-gcd-or-hcf-of-two-numbers-using-middle-school-procedure/
 * @reference   Program to find GCD or HCF of two numbers
 *              https://www.geeksforgeeks.org/c-program-find-gcd-hcf-two-numbers/
 * @reference   TCS Coding Practice Question | HCF or GCD of 2 Numbers
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-hcf-or-gcd-of-2-numbers/
 * @reference   std::gcd | C++ inbuilt function for finding GCD
 *              https://www.geeksforgeeks.org/stdgcd-c-inbuilt-function-finding-gcd/
 *
 * The greatest common divisor of two integers m and n is the largest integer that
 * divides them both.
 *
 * How is Extended Algorithm Useful?
 * The extended Euclidean algorithm is particularly useful when a and b are coprime (or
 * gcd is 1). Since x is the modular multiplicative inverse of "a modulo b", and y is
 * the modular multiplicative inverse of "b modulo a". In particular, the computation of
 * the modular multiplicative inverse is an essential step in RSA public-key encryption
 * method.
 *
 * @reference   Find HCF of two numbers without using recursion or Euclidean algorithm
 *              https://www.geeksforgeeks.org/find-hcf-of-two-numbers-without-using-recursion-or-euclidean-algorithm/
 */

/**
 * Euclid's algorithm
 *
 * gcd(0,n) = n;
 * gcd(m,n) = gcd(n mod m, m),  for n > m > 0.
 */
static inline constexpr unsigned
gcd(unsigned m, unsigned n) {
    if (m > n) {
        std::swap(m, n);
    }
    if (m == 0) {
        return n;
    } else {
        return gcd(n % m, m);
    }
}


static inline constexpr int
gcd_Extended(const int a, const int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1 = 0, y1 = 0;
    const auto gcd = gcd_Extended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

static inline constexpr auto
gcd_Extended(const int a, const int b) {
    int x = 0, y = 0;
    const auto gcd = gcd_Extended(a, b, &x, &y);
    return std::make_tuple(gcd, x, y);
}
