#include "common_header.h"


namespace {

/** Water Bottles
 *
 * @reference   https://leetcode.com/problems/water-bottles/
 *
 * There are numBottles water bottles that are initially full of water. You can exchange
 * numExchange empty water bottles from the market with one full water bottle.
 * The operation of drinking a full water bottle turns it into an empty bottle.
 * Given the two integers numBottles and numExchange, return the maximum number of water
 * bottles you can drink.
 */
inline constexpr auto WaterBottles(const int numBottles, const int numExchange) {
    return numBottles + (numBottles - 1) / (numExchange - 1);
}


/**
 * @reference   Count of Matches in Tournament
 *              https://leetcode.com/problems/count-of-matches-in-tournament/
 *
 * You are given an integer n, the number of teams in a tournament that has strange rules:
 *  If the current number of teams is even, each team gets paired with another team. A
 *      total of n / 2 matches are played, and n / 2 teams advance to the next round.
 *  If the current number of teams is odd, one team randomly advances in the tournament,
 *      and the rest gets paired. A total of (n - 1) / 2 matches are played, and
 *      (n - 1) / 2 + 1 teams advance to the next round.
 * Return the number of matches played in the tournament until a winner is decided.
 */
inline constexpr auto CountMatches(const int n) {
    return n - 1;
}

}//namespace


THE_BENCHMARK(WaterBottles, 9, 3);

SIMPLE_TEST(WaterBottles, TestSAMPLE1, 13, 9, 3);
SIMPLE_TEST(WaterBottles, TestSAMPLE2, 19, 15, 4);


THE_BENCHMARK(CountMatches, 9);

SIMPLE_TEST(CountMatches, TestSAMPLE1, 0, 1);
SIMPLE_TEST(CountMatches, TestSAMPLE2, 6, 7);
SIMPLE_TEST(CountMatches, TestSAMPLE3, 13, 14);
