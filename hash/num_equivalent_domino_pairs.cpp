#include "common_header.h"

#include "hash.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

/** Number of Equivalent Domino Pairs
 *
 * @reference   https://leetcode.com/problems/number-of-equivalent-domino-pairs/
 *
 * Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d]
 * if and only if either (a == c and b == d), or (a == d and b == c) - that is, one
 * domino can be rotated to be equal to another domino. Return the number of pairs (i, j)
 * for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].
 * 1 <= dominoes[i][j] <= 9
 */
auto NumEquivalentDominoPairs(const ArrayType &dominoes) {
    std::unordered_map<std::pair<int, int>, int, PairHash> counts;
    for (const auto [i, j] : dominoes) {
        if (i > j) {
            ++counts[std::pair(j, i)];
        } else {
            ++counts[std::pair(i, j)];
        }
    }

    int result = 0;
    for (const auto [_, c] : counts) {
        result += (c - 1) * c / 2;
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {{1, 2}, {2, 1}, {3, 4}, {5, 6}};
const ArrayType SAMPLE2 = {{1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 2}};


THE_BENCHMARK(NumEquivalentDominoPairs, SAMPLE1);

SIMPLE_TEST(NumEquivalentDominoPairs, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(NumEquivalentDominoPairs, TestSAMPLE2, 3, SAMPLE2);
