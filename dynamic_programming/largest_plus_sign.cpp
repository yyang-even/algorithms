#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

/** Largest Plus Sign
 *
 * @reference   https://leetcode.com/problems/largest-plus-sign/
 *
 * You are given an integer n. You have an n x n binary grid with all values
 * initially 1's except for some indices given in the array mines. The ith element of
 * the array mines is defined as mines[i] = [xi, yi] where grid[xi][yi] == 0. Return the
 * order of the largest axis-aligned plus sign of 1's contained in grid. If there is none,
 * return 0. An axis-aligned plus sign of 1's of order k has some center grid[r][c] == 1
 * along with four arms of length k - 1 going up, down, left, and right, and made of 1's.
 * Note that there could be 0's or 1's beyond the arms of the plus sign, only the relevant
 * area of the plus sign is checked for 1's.
 */
auto LargestPlusSign(const int N, const ArrayType &mines) {
    const std::unordered_set<std::pair<int, int>, PairHash>
    zeros(mines.cbegin(), mines.cend());

    int min_arms[N][N] = {};
    for (int r = 0; r < N; ++r) {
        int count = 0;
        for (int c = 0; c < N; ++c) {
            count = zeros.find({r, c}) != zeros.cend() ? 0 : count + 1;
            min_arms[r][c] = count;
        }

        count = 0;
        for (int c = N - 1; c >= 0; --c) {
            count = zeros.find({r, c}) != zeros.cend() ? 0 : count + 1;
            min_arms[r][c] = std::min(min_arms[r][c], count);
        }
    }

    int result = 0;
    for (int c = 0; c < N; ++c) {
        int count = 0;
        for (int r = 0; r < N; ++r) {
            count = zeros.find({r, c}) != zeros.cend() ? 0 : count + 1;
            min_arms[r][c] = std::min(min_arms[r][c], count);
        }

        count = 0;
        for (int r = N - 1; r >= 0; --r) {
            count = zeros.find({r, c}) != zeros.cend() ? 0 : count + 1;
            min_arms[r][c] = std::min(min_arms[r][c], count);
            result = std::max(result, min_arms[r][c]);
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {{4, 2}};
const ArrayType SAMPLE2 = {{0, 0}};


THE_BENCHMARK(LargestPlusSign, 5, SAMPLE1);

SIMPLE_TEST(LargestPlusSign, TestSAMPLE1, 2, 5, SAMPLE1);
SIMPLE_TEST(LargestPlusSign, TestSAMPLE2, 0, 1, SAMPLE2);
