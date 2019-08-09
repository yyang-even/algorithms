#pragma once


/** GCD - Greatest Common Divisor
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 4.1.
 * @reference   Euclidean algorithms (Basic and Extended)
 *              https://www.geeksforgeeks.org/euclidean-algorithms-basic-and-extended/
 * @reference   C Program for Basic Euclidean algorithms
 *              https://www.geeksforgeeks.org/c-program-for-basic-and-extended-euclidean-algorithms/
 * @reference   C Program for Extended Euclidean algorithms
 *              https://www.geeksforgeeks.org/c-program-for-basic-and-extended-euclidean-algorithms-2/
 *
 * The greatest common divisor of two integers m and n is the largest integer that divides them both.
 * How is Extended Algorithm Useful?
 * The extended Euclidean algorithm is particularly useful when a and b are coprime (or gcd is 1).
 * Since x is the modular multiplicative inverse of “a modulo b”, and y is the modular multiplicative
 * inverse of “b modulo a”. In particular, the computation of the modular multiplicative inverse is
 * an essential step in RSA public-key encryption method.
 */

/**
 * Euclid's algorithm
 *
 * gcd(0,n) = n;
 * gcd(m,n) = gcd(n mod m, m),  for n > m > 0.
 */
unsigned gcd(unsigned m, unsigned n) {
    if (m > n) {
        std::swap(m, n);
    }
    if (m == 0) {
        return n;
    } else {
        return gcd(n % m, m);
    }
}


int gcd_Extended(const int a, const int b, int *x, int *y) {
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
auto gcd_Extended(const int a, const int b) {
    int x = 0, y = 0;
    const auto gcd = gcd_Extended(a, b, &x, &y);
    return std::make_tuple(gcd, x, y);
}
