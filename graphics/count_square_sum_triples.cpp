#include "common_header.h"


namespace {

/** Count Square Sum Triples
 *
 * @reference   https://leetcode.com/problems/count-square-sum-triples/
 *
 * A square triple (a,b,c) is a triple where a, b, and c are integers and a^2 + b^2 = c^2.
 * Given an integer n, return the number of square triples such that 1 <= a, b, c <= n.
 */
constexpr auto CountSquareSumTriples(const int n) {
    bool squares[n * n + 1] = {};
    for (auto i = 1; i <= n; ++i) {
        squares[i * i] = true;
    }

    int result = 0;
    for (int i = 1; i <= n; ++i) {
        for (auto j = i; i * i + j * j <= n * n; ++j) {
            result += squares[i * i + j * j] * 2;
        }
    }

    return result;
}

}//namespace


THE_BENCHMARK(CountSquareSumTriples, 5);

SIMPLE_TEST(CountSquareSumTriples, TestSAMPLE1, 2, 5);
SIMPLE_TEST(CountSquareSumTriples, TestSAMPLE2, 4, 12);
SIMPLE_TEST(CountSquareSumTriples, TestSAMPLE3, 4, 10);
