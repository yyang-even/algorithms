#include "common_header.h"


namespace {

/** Minimum Penalty for a Shop
 *
 * @reference   https://leetcode.com/problems/minimum-penalty-for-a-shop/
 *
 * You are given the customer visit log of a shop represented by a 0-indexed string customers consisting
 * only of characters 'N' and 'Y':
 *  if the ith character is 'Y', it means that customers come at the ith hour
 *  whereas 'N' indicates that no customers come at the ith hour.
 * If the shop closes at the jth hour (0 <= j <= n), the penalty is calculated as follows:
 *  For every hour when the shop is open and no customers come, the penalty increases by 1.
 *  For every hour when the shop is closed and customers come, the penalty increases by 1.
 * Return the earliest hour at which the shop must be closed to incur a minimum penalty.
 * Note that if a shop closes at the jth hour, it means the shop is closed at the hour j.
 */
auto MinPenaltyForAShop(const std::string_view customers) {
    int penalty = 0;
    for (const auto c : customers) {
        penalty += (c == 'Y');
    }

    int result = 0;
    int min_p = penalty;

    for (std::size_t i = 1; i <= customers.size(); ++i) {
        if (customers[i - 1] == 'Y') {
            --penalty;
        } else {
            ++penalty;
        }

        if (penalty < min_p) {
            result = i;
            min_p = penalty;
        }
    }

    return result;
}


auto MinPenaltyForAShop_OnePass(const std::string_view customers) {
    int result = 0;
    int penalty = 0;
    int min_p = 0;

    for (std::size_t i = 1; i <= customers.size(); ++i) {
        if (customers[i - 1] == 'Y') {
            --penalty;
        } else {
            ++penalty;
        }

        if (penalty < min_p) {
            result = i;
            min_p = penalty;
        }
    }

    return result;
}

} //namespace


THE_BENCHMARK(MinPenaltyForAShop, "YYNY");

SIMPLE_TEST(MinPenaltyForAShop, TestSAMPLE1, 2, "YYNY");
SIMPLE_TEST(MinPenaltyForAShop, TestSAMPLE2, 0, "NNNNN");
SIMPLE_TEST(MinPenaltyForAShop, TestSAMPLE3, 4, "YYYY");


THE_BENCHMARK(MinPenaltyForAShop_OnePass, "YYNY");

SIMPLE_TEST(MinPenaltyForAShop_OnePass, TestSAMPLE1, 2, "YYNY");
SIMPLE_TEST(MinPenaltyForAShop_OnePass, TestSAMPLE2, 0, "NNNNN");
SIMPLE_TEST(MinPenaltyForAShop_OnePass, TestSAMPLE3, 4, "YYYY");
