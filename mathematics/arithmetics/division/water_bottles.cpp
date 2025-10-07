#include "common_header.h"


namespace {

/**
 * @reference   Water Bottles
 *              https://leetcode.com/problems/water-bottles/
 *
 * There are numBottles water bottles that are initially full of water. You can exchange numExchange
 * empty water bottles from the market with one full water bottle.
 * The operation of drinking a full water bottle turns it into an empty bottle.
 * Given the two integers numBottles and numExchange, return the maximum number of water bottles you can
 * drink.
 *
 * @tags    #division
 */
inline constexpr auto WaterBottles(const int numBottles, const int numExchange) {
    return numBottles + (numBottles - 1) / (numExchange - 1);
}


/**
 * @reference   Water Bottles II
 *              https://leetcode.com/problems/water-bottles-ii/
 *
 * You are given two integers numBottles and numExchange.
 * numBottles represents the number of full water bottles that you initially have. In one operation, you
 * can perform one of the following operations:
 *  Drink any number of full water bottles turning them into empty bottles.
 *  Exchange numExchange empty bottles with one full water bottle. Then, increase numExchange by one.
 * Note that you cannot exchange multiple batches of empty bottles for the same value of numExchange.
 * For example, if numBottles == 3 and numExchange == 1, you cannot exchange 3 empty water bottles for 3
 * full bottles.
 * Return the maximum number of water bottles you can drink.
 *
 * @tags    #arithmetic-progression #quadratic-formula
 */
auto WaterBottlesProgression(const int numBottles, const int numExchange) {
    const double a = 1;
    const double b = 2 * numExchange - 3;
    const double c = -2 * numBottles;
    const double delta = b * b - 4.0 * a * c;
    const int t = std::ceil((-b + std::sqrt(delta)) / (2.0 * a));

    return numBottles + t - 1;
}


/**
 * @reference   Count of Matches in Tournament
 *              https://leetcode.com/problems/count-of-matches-in-tournament/
 *
 * You are given an integer n, the number of teams in a tournament that has strange rules:
 *  If the current number of teams is even, each team gets paired with another team. A total of n / 2
 *      matches are played, and n / 2 teams advance to the next round.
 *  If the current number of teams is odd, one team randomly advances in the tournament, and the rest
 *      gets paired. A total of (n - 1) / 2 matches are played, and (n - 1) / 2 + 1 teams advance to the
 *      next round.
 * Return the number of matches played in the tournament until a winner is decided.
 */
inline constexpr auto CountMatches(const int n) {
    return n - 1;
}

} //namespace


THE_BENCHMARK(WaterBottles, 9, 3);

SIMPLE_TEST(WaterBottles, TestSAMPLE1, 13, 9, 3);
SIMPLE_TEST(WaterBottles, TestSAMPLE2, 19, 15, 4);


THE_BENCHMARK(WaterBottlesProgression, 13, 6);

SIMPLE_TEST(WaterBottlesProgression, TestSAMPLE1, 15, 13, 6);
SIMPLE_TEST(WaterBottlesProgression, TestSAMPLE2, 13, 10, 3);


THE_BENCHMARK(CountMatches, 9);

SIMPLE_TEST(CountMatches, TestSAMPLE1, 0, 1);
SIMPLE_TEST(CountMatches, TestSAMPLE2, 6, 7);
SIMPLE_TEST(CountMatches, TestSAMPLE3, 13, 14);
