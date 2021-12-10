#include "common_header.h"


namespace {

/** Domino and Tromino Tiling
 *
 * @reference   https://leetcode.com/problems/domino-and-tromino-tiling/
 *
 * You have two types of tiles: a 2 x 1 domino shape and a tromino shape. You may rotate
 * these shapes. Given an integer n, return the number of ways to tile an 2 x n board.
 * Since the answer may be very large, return it modulo 10^9 + 7. In a tiling, every
 * square must be covered by a tile. Two tilings are different if and only if there are
 * two 4-directionally adjacent cells on the board such that exactly one of the tilings
 * has both squares occupied by a tile.
 *
 * dp(n) = dp(n-1) + dp(n-2) + 2 * (dp(n-3) + ... + dp(0))
 *       = dp(n-1) + dp(n-3) + dp(n-2) + dp(n-3) + 2 * (dp(n-4) + ... + dp(0))
 *       = dp(n-1) + dp(n-3) + dp(n-1)
 *       = 2 * dp(n-1) + dp(n-3)
 */
constexpr int DominoTrominoTiling(const int n) {
    if (n <= 2) {
        return n;
    }

    long curr = 5;
    long prev = 2;
    long before_prev = 1;

    for (int i = 4; i <= n; ++i) {
        const auto tmp = prev;
        prev = curr;
        curr = (2 * curr + before_prev) % LARGE_PRIME;
        before_prev = tmp;
    }

    return curr;
}

}//namespace


THE_BENCHMARK(DominoTrominoTiling, 3);

SIMPLE_TEST(DominoTrominoTiling, TestSAMPLE1, 1, 1);
SIMPLE_TEST(DominoTrominoTiling, TestSAMPLE2, 2, 2);
SIMPLE_TEST(DominoTrominoTiling, TestSAMPLE3, 5, 3);
