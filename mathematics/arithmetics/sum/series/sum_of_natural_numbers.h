#pragma once

/** Program to find sum of first n natural numbers
 *
 * @reference   https://www.geeksforgeeks.org/program-find-sum-first-n-natural-numbers/
 * @reference   Natural Numbers
 *              https://www.geeksforgeeks.org/natural-numbers/
 * @reference   Sum of natural numbers using recursion
 *              https://www.geeksforgeeks.org/sum-of-natural-numbers-using-recursion/
 *
 * Given a number n, find sum of first natural numbers.
 */
static inline constexpr auto SumOfNaturals(const unsigned N) {
    return N * (N + 1) / 2;
}
