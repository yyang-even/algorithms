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

}//namespace


THE_BENCHMARK(WaterBottles, 9, 3);

SIMPLE_TEST(WaterBottles, TestSAMPLE1, 13, 9, 3);
SIMPLE_TEST(WaterBottles, TestSAMPLE2, 19, 15, 4);
