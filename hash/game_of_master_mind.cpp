#include "common_header.h"


namespace {

/** The game of master mind
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.5.
 *
 * The Game of Master Mind is played as follows:
 * The computer has four slots containing balls that are red (R), yellow (Y), green (G)
 * or blue (B). For example, the computer might have RGGB (e.g., Slot #1 is red, Slots #2
 * and #3 are green, Slot #4 is blue). You, the user, are trying to guess the solution.
 * You might, for example, guess YRGB. When you guess the correct color for the correct
 * slot, you get a "hit". If you guess a color that exists but is in the wrong slot, you
 * get a "pseudo-hit". For example, if the actual solution is RGBY and you guess GGRR,
 * you have one hit and one pseudo-hit. Write a method that, given a guess and a solution,
 * returns the number of hits and pseudo-hits.
 */
auto GameOfMasterMind(const std::string &solution, const std::string &guess) {
    assert(solution.size() == guess.size());

    int hits = 0;
    std::unordered_map<std::string::value_type, int> frequency_map;
    for (std::size_t i = 0; i < solution.size(); ++i) {
        if (solution[i] == guess[i]) {
            ++hits;
        } else {
            ++(frequency_map[solution[i]]);
        }
    }

    int pseudo_hits = 0;
    for (std::size_t i = 0; i < guess.size(); ++i) {
        if (guess[i] != solution[i] and (frequency_map[guess[i]])-- > 0) {
            ++pseudo_hits;
        }
    }

    return std::pair{hits, pseudo_hits};
}

}//namespace


const std::pair EXPECTED1 = {1, 1};
const std::pair EXPECTED2 = {4, 0};
const std::pair EXPECTED3 = {0, 4};


THE_BENCHMARK(GameOfMasterMind, "RGBY", "GGRR");

SIMPLE_TEST(GameOfMasterMind, TestSAMPLE1, EXPECTED1, "RGBY", "GGRR");
SIMPLE_TEST(GameOfMasterMind, TestSAMPLE2, EXPECTED2, "RGBY", "RGBY");
SIMPLE_TEST(GameOfMasterMind, TestSAMPLE3, EXPECTED3, "RGBY", "GBYR");
