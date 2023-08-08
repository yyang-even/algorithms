#include "common_header.h"


namespace {

/** Soup Servings
 *
 * @reference   https://leetcode.com/problems/soup-servings/
 *
 * There are two types of soup: type A and type B. Initially, we have n ml of each type of soup. There
 * are four kinds of operations:
 *  Serve 100 ml of soup A and 0 ml of soup B,
 *  Serve 75 ml of soup A and 25 ml of soup B,
 *  Serve 50 ml of soup A and 50 ml of soup B, and
 *  Serve 25 ml of soup A and 75 ml of soup B.
 * When we serve some soup, we give it to someone, and we no longer have it. Each turn, we will choose
 * from the four operations with an equal probability 0.25. If the remaining volume of soup is not
 * enough to complete the operation, we will serve as much as possible. We stop once we no longer have
 * some quantity of both types of soup.
 * Note that we do not have an operation where all 100 ml's of soup B are used first.
 * Return the probability that soup A will be empty first, plus half the probability that A and B become
 * empty at the same time. Answers within 10-5 of the actual answer will be accepted.
 * 0 <= n <= 10^9
 */
double SoupServings(const int a, const int b, std::unordered_map<int, double> &memo) {
    if (a <= 0 and b <= 0) {
        return 0.5;
    }

    if (a <= 0) {
        return 1.0;
    }

    if (b <= 0) {
        return 0.0;
    }

    const auto key = a * 5000 + b;
    const auto [iter, inserted] = memo.emplace(key, 0.0);
    if (not inserted) {
        return iter->second;
    }
    iter->second = 0.25 * (SoupServings(a - 4, b, memo) + SoupServings(a - 3, b - 1, memo) +
                           SoupServings(a - 2, b - 2, memo) + SoupServings(a - 1, b - 3, memo));

    return iter->second;
}

auto SoupServings(int n) {
    if (n > 4451) {
        return 1.0;
    }

    n = (n + 24) / 25;
    std::unordered_map<int, double> memo;

    return SoupServings(n, n, memo);
}

} //namespace


THE_BENCHMARK(SoupServings, 4000);

SIMPLE_DOUBLE_TEST(SoupServings, TestSAMPLE1, 0.625, 50);
SIMPLE_DOUBLE_TEST(SoupServings, TestSAMPLE2, 0.71875, 100);
