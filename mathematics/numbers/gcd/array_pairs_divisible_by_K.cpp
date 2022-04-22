#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Count Array Pairs Divisible by K
 *
 * @reference   https://leetcode.com/problems/count-array-pairs-divisible-by-k/
 *
 * Given a 0-indexed integer array nums of length n and an integer k, return the number
 * of pairs (i, j) such that:
 *  0 <= i < j <= n - 1 and
 *  nums[i] * nums[j] is divisible by k.
 */
auto CountPairsDivisibleByK(const ArrayType &nums, const int k) {
    std::unordered_map<int, int> gcds;

    long long result = 0;
    for (const auto n : nums) {
        const auto one_gcd = std::gcd(n, k);
        for (const auto [other_gcd, count] : gcds)
            if (one_gcd * other_gcd % k == 0) {
                result += count;
            }
        ++gcds[one_gcd];
    }

    return result;
}


/**
 * @reference   Count Equal and Divisible Pairs in an Array
 *              https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array/
 *
 * Given a 0-indexed integer array nums of length n and an integer k, return the number
 * of pairs (i, j) where 0 <= i < j < n, such that nums[i] == nums[j] and (i * j) is
 * divisible by k.
 * 1 <= nums.length <= 100
 */

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4, 5};
const ArrayType SAMPLE2 = {1, 2, 3, 4};


THE_BENCHMARK(CountPairsDivisibleByK, SAMPLE1, 2);

SIMPLE_TEST(CountPairsDivisibleByK, TestSAMPLE1, 7, SAMPLE1, 2);
SIMPLE_TEST(CountPairsDivisibleByK, TestSAMPLE2, 0, SAMPLE2, 5);
