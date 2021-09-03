#pragma once


/**
 * @reference   Space and time efficient Binomial Coefficient
 *              https://www.geeksforgeeks.org/space-and-time-efficient-binomial-coefficient/
 */
static inline constexpr auto
BinomialCoefficient(const int n, int k) {
    int result = 1;

    // Since C(n, k) = C(n, n-k)
    if (k > n - k) {
        k = n - k;
    }

    for (int i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }

    return result;
}
