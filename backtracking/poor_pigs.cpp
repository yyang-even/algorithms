#include "common_header.h"


namespace {

/** Poor Pigs
 *
 * @reference   https://leetcode.com/problems/poor-pigs/
 *
 * There are buckets buckets of liquid, where exactly one of the buckets is poisonous. To figure out
 * which one is poisonous, you feed some number of (poor) pigs the liquid to see whether they will die
 * or not. Unfortunately, you only have minutesToTest minutes to determine which bucket is poisonous.
 * You can feed the pigs according to these steps:
 *  Choose some live pigs to feed.
 *  For each pig, choose which buckets to feed it. The pig will consume all the chosen buckets
 *      simultaneously and will take no time.
 *  Wait for minutesToDie minutes. You may not feed any other pigs during this time.
 *  After minutesToDie minutes have passed, any pigs that have been fed the poisonous bucket will die,
 *      and all others will survive.
 *  Repeat this process until you run out of time.
 * Given buckets, minutesToDie, and minutesToTest, return the minimum number of pigs needed to figure
 * out which bucket is poisonous within the allotted time.
 */
inline constexpr int
PoorPigs(const int buckets, const int minutesToDie, const int minutesToTest) {
    return std::ceil(std::log(buckets) / std::log(minutesToTest / minutesToDie + 1));
}

} //namespace


THE_BENCHMARK(PoorPigs, 1000, 15, 60);

SIMPLE_TEST(PoorPigs, TestSAMPLE1, 5, 1000, 15, 60);
SIMPLE_TEST(PoorPigs, TestSAMPLE2, 2, 4, 15, 15);
SIMPLE_TEST(PoorPigs, TestSAMPLE3, 2, 4, 15, 30);
