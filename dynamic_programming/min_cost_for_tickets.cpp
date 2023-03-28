#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Minimum Cost For Tickets
 *
 * @reference   https://leetcode.com/problems/minimum-cost-for-tickets/
 *
 * You have planned some train traveling one year in advance. The days of the year in which you will
 * travel are given as an integer array days. Each day is an integer from 1 to 365.
 * Train tickets are sold in three different ways:
 *  a 1-day pass is sold for costs[0] dollars,
 *  a 7-day pass is sold for costs[1] dollars, and
 *  a 30-day pass is sold for costs[2] dollars.
 * The passes allow that many days of consecutive travel.
 *  For example, if we get a 7-day pass on day 2, then we can travel for 7 days: 2, 3, 4, 5, 6, 7, and
 *  8.
 * Return the minimum number of dollars you need to travel every day in the given list of days.
 * days is in strictly increasing order.
 */
auto MinCostForTickets(const ArrayType &days, const ArrayType &costs) {
    std::queue<std::pair<int, int>> last7;
    std::queue<std::pair<int, int>> last30;

    int result = 0;
    for (const auto d : days) {
        while (not last7.empty() and last7.front().first <= d) {
            last7.pop();
        }

        while (not last30.empty() and last30.front().first <= d) {
            last30.pop();
        }

        last7.emplace(d + 7, result + costs[1]);
        last30.emplace(d + 30, result + costs[2]);

        result = std::min({result + costs[0], last7.front().second, last30.front().second});
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1D = {1, 4, 6, 7, 8, 20};
const ArrayType SAMPLE1C = {2, 7, 15};

const ArrayType SAMPLE2D = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31};


THE_BENCHMARK(MinCostForTickets, SAMPLE1D, SAMPLE1C);

SIMPLE_TEST(MinCostForTickets, TestSAMPLE1, 11, SAMPLE1D, SAMPLE1C);
SIMPLE_TEST(MinCostForTickets, TestSAMPLE2, 17, SAMPLE2D, SAMPLE1C);
