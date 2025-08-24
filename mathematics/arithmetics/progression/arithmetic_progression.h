#pragma once


/**
 * @reference   Program to find sum of first n natural numbers
 *              https://www.geeksforgeeks.org/program-find-sum-first-n-natural-numbers/
 * @reference   Natural Numbers
 *              https://www.geeksforgeeks.org/natural-numbers/
 * @reference   Sum of natural numbers using recursion
 *              https://www.geeksforgeeks.org/sum-of-natural-numbers-using-recursion/
 *
 * Given a number n, find sum of first natural numbers.
 *
 * @tags    #arithmetic-progression
 */
static inline constexpr auto SumOfNaturals(const unsigned N) {
    return N * (N + 1) / 2;
}


static inline constexpr auto
ArithmeticProgressionSum(const int first, const int n, const int diff) {
    return (2 * first + (n - 1) * diff) * n / 2;
}
