#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string>;

/** Flip Game
 *
 * @reference   https://xinjiema.gitbooks.io/leetcode/content/flip-game.html
 *
 * You are playing the following Flip Game with your friend: Given a string that
 * contains only these two characters: + and -, you and your friend take turns to flip
 * two consecutive "++" into "--". The game ends when a person can no longer make a move
 * and therefore the other person will be the winner. Write a function to compute all
 * possible states of the string after one valid move.
 */
auto AllFlips(const std::string &s) {
    ArrayType results;
    for (std::size_t i = 1; i < s.size(); ++i) {
        if (s[i - 1] == '+' and s[i - 1] == s[i]) {
            results.push_back(s);
            results.back()[i - 1] = '-';
            results.back()[i] = '-';
        }
    }

    return results;
}


/**
 * @reference   Flip Game II
 *              http://buttercola.blogspot.com/2015/10/leetcode-flip-game-ii.html
 *
 * You are playing the following Flip Game with your friend: Given a string that
 * contains only these two characters: + and -, you and your friend take turns to flip
 * two consecutive "++" into "--". The game ends when a person can no longer make a move
 * and therefore the other person will be the winner. Write a function to determine if
 * the starting player can guarantee a win.
 */
auto CanWinFlip_Memo(std::string &s, std::unordered_map<std::string, bool> &isWin) {
    const auto [iter, inserted] = isWin.emplace(s, false);
    if (not inserted) {
        return iter->second;
    }

    for (std::size_t i = 1; i < s.size(); ++i) {
        if (s[i - 1] == '+' and s[i] == '+') {
            s[i - 1] = '-';
            s[i] = '-';

            const auto result = CanWinFlip_Memo(s, isWin);

            s[i] = '+';
            s[i - 1] = '+';

            if (not result) {
                iter->second = true;
                break;
            }
        }
    }

    return iter->second;
}

inline auto CanWinFlip_Memo(std::string s) {
    std::unordered_map<std::string, bool> isWin;
    return CanWinFlip_Memo(s, isWin);
}

}//namespace


const ArrayType EXPECTED0 = {};
const ArrayType EXPECTED1 = {"--++", "+--+", "++--"};


THE_BENCHMARK(AllFlips, "++++");

SIMPLE_TEST(AllFlips, TestSAMPLE0, EXPECTED0, "+--+");
SIMPLE_TEST(AllFlips, TestSAMPLE1, EXPECTED1, "++++");


THE_BENCHMARK(CanWinFlip_Memo, "++++");

SIMPLE_TEST(CanWinFlip_Memo, TestSAMPLE1, false, "+--+");
SIMPLE_TEST(CanWinFlip_Memo, TestSAMPLE2, true, "++++");
SIMPLE_TEST(CanWinFlip_Memo, TestSAMPLE3, false, "+++++");
