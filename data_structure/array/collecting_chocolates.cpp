#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Collecting Chocolates
 *
 * @reference   https://leetcode.com/problems/collecting-chocolates/
 *
 * You are given a 0-indexed integer array nums of size n representing the cost of collecting different
 * chocolates. The cost of collecting the chocolate at the index i is nums[i]. Each chocolate is of a
 * different type, and initially, the chocolate at the index i is of ith type.
 * In one operation, you can do the following with an incurred cost of x:
 *  Simultaneously change the chocolate of ith type to ((i + 1) mod n)th type for all chocolates.
 * Return the minimum cost to collect chocolates of all types, given that you can perform as many
 * operations as you would like.
 */
auto MinCost(const ArrayType &nums, const std::size_t x) {
    auto sum = std::accumulate(nums.cbegin(), nums.cend(), 0ull);
    auto result = sum;
    auto minimums = nums;

    for (std::size_t k = 1; k < nums.size(); ++k) {
        for (std::size_t i = 0; i < nums.size(); ++i) {
            const auto n = nums[(i + k) % nums.size()];
            if (minimums[i] > n) {
                sum = sum - minimums[i] + n;
                minimums[i] = n;
            }
        }

        result = std::min(result, sum + k * x);
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {20, 1, 15};
const ArrayType SAMPLE2 = {1, 2, 3};


THE_BENCHMARK(MinCost, SAMPLE1, 5);

SIMPLE_TEST(MinCost, TestSAMPLE1, 13, SAMPLE1, 5);
SIMPLE_TEST(MinCost, TestSAMPLE2, 6, SAMPLE2, 4);
