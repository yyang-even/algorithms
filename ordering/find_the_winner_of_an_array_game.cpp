#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find the Winner of an Array Game
 *
 * @reference   https://leetcode.com/problems/find-the-winner-of-an-array-game/
 *
 * Given an integer array arr of distinct integers and an integer k.
 * A game will be played between the first two elements of the array (i.e. arr[0] and arr[1]). In each
 * round of the game, we compare arr[0] with arr[1], the larger integer wins and remains at position 0,
 * and the smaller integer moves to the end of the array. The game ends when an integer wins k
 * consecutive rounds.
 * Return the integer which will win the game.
 * It is guaranteed that there will be a winner of the game.
 */
auto FindWinnerOfArrayGame(const ArrayType &nums, const int k) {
    auto result = nums.front();
    int count = 0;
    for (std::size_t i = 1; i < nums.size(); ++i) {
        const auto n = nums[i];
        if (n > result) {
            count = 0;
            result = n;
        }

        if (count++ == k - 1) {
            break;
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {2, 1, 3, 5, 4, 6, 7};
const ArrayType SAMPLE2 = {3, 2, 1};
const ArrayType SAMPLE3 = {1, 25, 35, 42, 68, 70};


THE_BENCHMARK(FindWinnerOfArrayGame, SAMPLE1, 2);

SIMPLE_TEST(FindWinnerOfArrayGame, TestSAMPLE1, 5, SAMPLE1, 2);
SIMPLE_TEST(FindWinnerOfArrayGame, TestSAMPLE2, 3, SAMPLE2, 10);
SIMPLE_TEST(FindWinnerOfArrayGame, TestSAMPLE3, 25, SAMPLE3, 1);
