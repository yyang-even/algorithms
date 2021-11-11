#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Unique Paths
 *
 * @reference   https://leetcode.com/problems/unique-paths/
 *
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in the
 * diagram below). The robot can only move either down or right at any point in time.
 * The robot is trying to reach the bottom-right corner of the grid (marked 'Finish'
 * in the diagram below). How many possible unique paths are there?
 *
 * (m+n)! / (m! * n!)
 */
constexpr int combine(const int m, const int n) {
    assert(m >= n);

    long result = 1;
    int j = 1;
    for (int i = m + 1; i <= m + n; ++i, ++j) {
        result *= i;
        result /= j;
    }

    return result;
}

constexpr auto UniquePaths(const int m, const int n) {
    if (m == 1 or n == 1) {
        return 1;
    }

    if (m < n) {
        return combine(n - 1, m - 1);
    }
    return combine(m - 1, n - 1);
}

}//namespace


THE_BENCHMARK(UniquePaths, 3, 7);

SIMPLE_TEST(UniquePaths, TestSAMPLE1, 28, 3, 7);
SIMPLE_TEST(UniquePaths, TestSAMPLE2, 3, 3, 2);
SIMPLE_TEST(UniquePaths, TestSAMPLE3, 28, 7, 3);
SIMPLE_TEST(UniquePaths, TestSAMPLE4, 6, 3, 3);
