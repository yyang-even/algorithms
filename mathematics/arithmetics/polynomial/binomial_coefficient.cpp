#include "common_header.h"

#include "binomial_coefficient.h"


namespace {

/** Binomial Coefficient
 *
 * @reference   Binomial Coefficient | DP-9
 *              https://www.geeksforgeeks.org/binomial-coefficient-dp-9/
 *
 * Write a function that takes two parameters n and k and returns the value of Binomial
 * Coefficient C(n, k).
 *  C(n, k) = C(n-1, k-1) + C(n-1, k)
 *  C(n, 0) = C(n, n) = 1
 */
constexpr auto BinomialCoefficient_Recursive(const int n, const int k) {
    if (k > n) {
        return 0;
    }
    if (k == 0 or k == n) {
        return 1;
    }

    return BinomialCoefficient_Recursive(n - 1, k - 1) +
           BinomialCoefficient_Recursive(n - 1, k);
}


constexpr auto BinomialCoefficient_DP(const int n, const int k) {
    int C[k + 1] = {1};

    for (int i = 1; i <= n; ++i) {
        // Compute next row of pascal triangle using the previous row
        for (int j = std::min(i, k); j > 0; --j) {
            C[j] = C[j] + C[j - 1];
        }
    }

    return C[k];
}

}//namespace


THE_BENCHMARK(BinomialCoefficient_DP, 4, 2);

SIMPLE_TEST(BinomialCoefficient_DP, TestSAMPLE1, 6, 4, 2);
SIMPLE_TEST(BinomialCoefficient_DP, TestSAMPLE2, 10, 5, 2);
SIMPLE_TEST(BinomialCoefficient_DP, TestSAMPLE3, 28, 8, 2);


THE_BENCHMARK(BinomialCoefficient_Recursive, 4, 2);

SIMPLE_TEST(BinomialCoefficient_Recursive, TestSAMPLE1, 6, 4, 2);
SIMPLE_TEST(BinomialCoefficient_Recursive, TestSAMPLE2, 10, 5, 2);
SIMPLE_TEST(BinomialCoefficient_Recursive, TestSAMPLE3, 28, 8, 2);


THE_BENCHMARK(BinomialCoefficient, 4, 2);

SIMPLE_TEST(BinomialCoefficient, TestSAMPLE1, 6, 4, 2);
SIMPLE_TEST(BinomialCoefficient, TestSAMPLE2, 10, 5, 2);
SIMPLE_TEST(BinomialCoefficient, TestSAMPLE3, 28, 8, 2);
