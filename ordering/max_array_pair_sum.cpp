#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Array Partition
 *
 * @reference   https://leetcode.com/problems/array-partition/
 *
 * Given an integer array nums of 2n integers, group these integers into n pairs (a1, b1), (a2, b2),
 * ..., (an, bn) such that the sum of min(ai, bi) for all i is maximized. Return the maximized sum.
 * -10^4 <= nums[i] <= 10^4
 */
auto MaxArrayPairSum(ArrayType nums) {
    std::sort(nums.begin(), nums.end());

    const auto N = nums.size();
    int sum = 0;
    for (std::size_t i = 0; i < N; i += 2) {
        sum += nums[i];
    }

    return sum;
}


auto MaxArrayPairSum_CountingSort(const ArrayType &nums) {
    int buckets[20001] = {};

    for (const auto x : nums) {
        ++buckets[x + 10000];
    }

    int sum = 0;
    std::size_t i = 0;
    for (int x = 0; i < nums.size();) {
        if (buckets[x] == 0) {
            ++x;
        } else {
            if (i++ % 2 == 0) {
                sum += x - 10000;
            }

            --buckets[x];
        }
    }

    return sum;
}


/**
 * @reference   Minimum Difference Between Highest and Lowest of K Scores
 *              https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/
 *
 * You are given a 0-indexed integer array nums, where nums[i] represents the score of the ith student.
 * You are also given an integer k.
 * Pick the scores of any k students from the array so that the difference between the highest and the
 * lowest of the k scores is minimized.
 * Return the minimum possible difference.
 */


/**
 * @reference   Widest Vertical Area Between Two Points Containing No Points
 *              https://leetcode.com/problems/widest-vertical-area-between-two-points-containing-no-points/
 *
 * Given n points on a 2D plane where points[i] = [xi, yi], Return the widest vertical area between two
 * points such that no points are inside the area.
 * A vertical area is an area of fixed-width extending infinitely along the y-axis (i.e., infinite
 * height). The widest vertical area is the one with the maximum width.
 * Note that points on the edge of a vertical area are not considered included in the area.
 */


/**
 * @reference   Minimum Cost of Buying Candies With Discount
 *              https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/
 *
 * A shop is selling candies at a discount. For every two candies sold, the shop gives a third candy for
 * free.
 * The customer can choose any candy to take away for free as long as the cost of the chosen candy is
 * less than or equal to the minimum cost of the two candies bought.
 *  For example, if there are 4 candies with costs 1, 2, 3, and 4, and the customer buys candies with
 *  costs 2 and 3, they can take the candy with cost 1 for free, but not the candy with cost 4.
 * Given a 0-indexed integer array cost, where cost[i] denotes the cost of the ith candy, return the
 * minimum cost of buying all the candies.
 */
auto MinimumCost(ArrayType cost) {
    std::sort(cost.begin(), cost.end(), std::greater<int> {});

    int result = 0;
    for (std::size_t i = 0; i < cost.size(); ++i) {
        if (i % 3 != 2) {
            result += cost[i];
        }
    }

    return result;
}


/**
 * @reference   Minimum Sum of Four Digit Number After Splitting Digits
 *              https://leetcode.com/problems/minimum-sum-of-four-digit-number-after-splitting-digits/
 *
 * You are given a positive integer num consisting of exactly four digits. Split num into two new
 * integers new1 and new2 by using the digits found in num. Leading zeros are allowed in new1 and new2,
 * and all the digits found in num must be used.
 *  For example, given num = 2932, you have the following digits: two 2's, one 9 and one 3. Some of the
 *  possible pairs [new1, new2] are [22, 93], [23, 92], [223, 9] and [2, 329].
 * Return the minimum possible sum of new1 and new2.
 * 1000 <= num <= 9999
 */
auto MinSum(int num) {
    ArrayType digits;
    while (num) {
        digits.push_back(num % 10);
        num /= 10;
    }

    std::nth_element(begin(digits), begin(digits) + 1, end(digits));

    return (digits[0] + digits[1]) * 10 + digits[2] + digits[3];
}

} //namespace


const ArrayType SAMPLE1 = {1, 4, 3, 2};
const ArrayType SAMPLE2 = {6, 2, 6, 5, 1, 2};


THE_BENCHMARK(MaxArrayPairSum, SAMPLE1);

SIMPLE_TEST(MaxArrayPairSum, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MaxArrayPairSum, TestSAMPLE2, 9, SAMPLE2);


THE_BENCHMARK(MaxArrayPairSum_CountingSort, SAMPLE1);

SIMPLE_TEST(MaxArrayPairSum_CountingSort, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MaxArrayPairSum_CountingSort, TestSAMPLE2, 9, SAMPLE2);


const ArrayType SAMPLE1C = {1, 2, 3};
const ArrayType SAMPLE2C = {6, 5, 7, 9, 2, 2};
const ArrayType SAMPLE3C = {5, 5};
const ArrayType SAMPLE4C = {5};


THE_BENCHMARK(MinimumCost, SAMPLE1C);

SIMPLE_TEST(MinimumCost, TestSAMPLE1, 5, SAMPLE1C);
SIMPLE_TEST(MinimumCost, TestSAMPLE2, 23, SAMPLE2C);
SIMPLE_TEST(MinimumCost, TestSAMPLE3, 10, SAMPLE3C);
SIMPLE_TEST(MinimumCost, TestSAMPLE4, 5, SAMPLE4C);


THE_BENCHMARK(MinSum, 2932);

SIMPLE_TEST(MinSum, TestSAMPLE1, 52, 2932);
SIMPLE_TEST(MinSum, TestSAMPLE2, 13, 4009);
