#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Minimum Domino Rotations For Equal Row
 *
 * @reference   https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/
 *
 * In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the
 * ith domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the
 * tile.)
 * We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.
 * Return the minimum number of rotations so that all the values in tops are the same, or
 * all the values in bottoms are the same.
 * If it cannot be done, return -1.
 */
int
MinDominoRatationsForEqualRow_Hash(const ArrayType &tops, const ArrayType &bottoms) {
    constexpr auto N = 7;
    std::size_t count_tops[N] = {};
    std::size_t count_bottoms[N] = {};
    std::size_t equals[N] = {};

    for (std::size_t i = 0; i < tops.size(); ++i) {
        ++count_tops[tops[i]];
        ++count_bottoms[bottoms[i]];
        if (tops[i] == bottoms[i]) {
            ++equals[tops[i]];
        }
    }

    for (int i = 1; i < N; ++i) {
        if (count_tops[i] + count_bottoms[i] - equals[i] == tops.size()) {
            return tops.size() - std::max(count_tops[i], count_bottoms[i]);
        }
    }

    return -1;
}


int
checkCandidate(const ArrayType &tops, const ArrayType &bottoms, const int candidate) {
    std::size_t i = 0, top_swap = 0, bottom_swap = 0;
    for (; i < tops.size() and (tops[i] == candidate or bottoms[i] == candidate); ++i) {
        if (tops[i] != candidate) {
            ++top_swap;
        }

        if (bottoms[i] != candidate) {
            ++bottom_swap;
        }
    }

    return i == tops.size() ? std::min(top_swap, bottom_swap) : -1;
}

auto
MinDominoRatationsForEqualRow_Greedy(const ArrayType &tops, const ArrayType &bottoms) {
    const auto result = checkCandidate(tops, bottoms, tops.front());
    return result != -1 ? result : checkCandidate(tops, bottoms, bottoms.front());
}

}//namespace


const ArrayType SAMPLE1T = {2, 1, 2, 4, 2, 2};
const ArrayType SAMPLE1B = {5, 2, 6, 2, 3, 2};

const ArrayType SAMPLE2T = {3, 5, 1, 2, 3};
const ArrayType SAMPLE2B = {3, 6, 3, 3, 4};


THE_BENCHMARK(MinDominoRatationsForEqualRow_Hash, SAMPLE1T, SAMPLE1B);

SIMPLE_TEST(MinDominoRatationsForEqualRow_Hash, TestSAMPLE1, 2, SAMPLE1T, SAMPLE1B);
SIMPLE_TEST(MinDominoRatationsForEqualRow_Hash, TestSAMPLE2, -1, SAMPLE2T, SAMPLE2B);


THE_BENCHMARK(MinDominoRatationsForEqualRow_Greedy, SAMPLE1T, SAMPLE1B);

SIMPLE_TEST(MinDominoRatationsForEqualRow_Greedy, TestSAMPLE1, 2, SAMPLE1T, SAMPLE1B);
SIMPLE_TEST(MinDominoRatationsForEqualRow_Greedy, TestSAMPLE2, -1, SAMPLE2T, SAMPLE2B);
