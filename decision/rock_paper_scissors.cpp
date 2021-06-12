#include "common_header.h"


namespace {

/** Rock Paper Scissors
 *
 * @reference   Rock Paper Scissors
 *              https://www.codewars.com/kata/rock-paper-scissors/cpp
 *
 * You have to return which player won! Return 1 if player 1 won. 2 for player 2. In
 * case of a draw return 0.
 */
inline constexpr int
RockPaperScissors(const std::string_view player1, const std::string_view player2) {
    if (player1[0] == player2[0]) {
        return 0;
    }
    if ((player1[0] == 'r' and player2[0] == 's') or
        (player1[0] == 's' and player2[0] == 'p') or
        (player1[0] == 'p' and player2[0] == 'r')) {
        return 1;
    }
    return 2;
}

}//namespace


THE_BENCHMARK(RockPaperScissors, "scissors", "paper");

SIMPLE_TEST(RockPaperScissors, TestSample1, 1, "scissors", "paper");
SIMPLE_TEST(RockPaperScissors, TestSample2, 2, "scissors", "rock");
SIMPLE_TEST(RockPaperScissors, TestSample3, 0, "scissors", "scissors");
SIMPLE_TEST(RockPaperScissors, TestSample4, 0, "paper", "paper");
SIMPLE_TEST(RockPaperScissors, TestSample5, 1, "paper", "rock");
SIMPLE_TEST(RockPaperScissors, TestSample6, 2, "paper", "scissors");
SIMPLE_TEST(RockPaperScissors, TestSample7, 0, "rock", "rock");
SIMPLE_TEST(RockPaperScissors, TestSample8, 1, "rock", "scissors");
SIMPLE_TEST(RockPaperScissors, TestSample9, 2, "rock", "paper");
