#include "common_header.h"


namespace {

/**
 * @reference   Sum Game
 *              https://leetcode.com/problems/sum-game/
 *
 * Alice and Bob take turns playing a game, with Alice starting first.
 * You are given a string num of even length consisting of digits and '?' characters. On each turn, a
 * player will do the following if there is still at least one '?' in num:
 *  Choose an index i where num[i] == '?'.
 *  Replace num[i] with any digit between '0' and '9'.
 * The game ends when there are no more '?' characters in num.
 * For Bob to win, the sum of the digits in the first half of num must be equal to the sum of the digits
 * in the second half. For Alice to win, the sums must not be equal.
 *  For example, if the game ended with num = "243801", then Bob wins because 2+4+3 = 8+0+1. If the game
 *  ended with num = "243803", then Alice wins because 2+4+3 != 8+0+3.
 * Assuming Alice and Bob play optimally, return true if Alice will win and false if Bob will win.
 *
 * @tags    #greedy #numeric-string #accumulate
 */
auto SumGame(const std::string_view &num) {
    int sum = 0;
    int count = 0;

    const int N = num.size();
    for (int i = 0; i < N; ++i) {
        const auto is_digit = (num[i] != '?');
        const auto digit = is_digit ? (num[i] - '0') : 0;
        if (i < N / 2) {
            sum += digit;
            count += not is_digit;
        } else {
            sum -= digit;
            count -= not is_digit;
        }
    }

    if (count % 2) {
        return true;
    } else {
        return -sum != (count / 2 * 9);
    }
}

} //namespace


THE_BENCHMARK(SumGame, "5023");

SIMPLE_TEST(SumGame, TestSAMPLE1, false, "5023");
SIMPLE_TEST(SumGame, TestSAMPLE2, true, "25??");
SIMPLE_TEST(SumGame, TestSAMPLE3, false, "?3295???");
SIMPLE_TEST(SumGame, TestSAMPLE4, true, "?6?6?000?3");
