#include "common_header.h"

#include "mathematics/arithmetics/progression/arithmetic_progression.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Candy
 *              https://leetcode.com/problems/candy/
 *
 * There are n children standing in a line. Each child is assigned a rating value given in the integer
 * array ratings.
 * You are giving candies to these children subjected to the following requirements:
 *  Each child must have at least one candy.
 *  Children with a higher rating get more candies than their neighbors.
 * Return the minimum number of candies you need to have to distribute the candies to the children.
 *
 * @tags    #forward-and-backward
 */
auto Candy_TwoArray(const ArrayType &ratings) {
    ArrayType left_to_right(ratings.size(), 1);
    ArrayType right_to_left(ratings.size(), 1);

    for (std::size_t i = 1; i < ratings.size(); ++i) {
        if (ratings[i] > ratings[i - 1]) {
            left_to_right[i] = left_to_right[i - 1] + 1;
        }
    }

    for (int i = ratings.size() - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1]) {
            right_to_left[i] = right_to_left[i + 1] + 1;
        }
    }

    int sum = 0;
    for (std::size_t i = 0; i < ratings.size(); ++i) {
        sum += std::max(left_to_right[i], right_to_left[i]);
    }

    return sum;
}


auto Candy_OneArray(const ArrayType &ratings) {
    ArrayType candies(ratings.size(), 1);

    for (std::size_t i = 1; i < ratings.size(); ++i) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    int sum = candies.back();
    for (int i = ratings.size() - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = std::max(candies[i], candies[i + 1] + 1);
        }
        sum += candies[i];
    }

    return sum;
}


int Candy_Slope(const ArrayType &ratings) {
    if (ratings.size() <= 1) {
        return ratings.size();
    }

    int candies = 0;
    int up = 0;
    int down = 0;
    int old_slope = 0;
    for (std::size_t i = 1; i < ratings.size(); ++i) {
        const int new_slope =
            (ratings[i] > ratings[i - 1]) ? 1 : (ratings[i] < ratings[i - 1] ? -1 : 0);

        if ((old_slope > 0 and new_slope <= 0) or (old_slope < 0 and new_slope >= 0)) {
            candies += SumOfNaturals(up) + SumOfNaturals(down) + std::max(up, down);
            up = 0;
            down = 0;
        }

        if (new_slope > 0) {
            up++;
        } else if (new_slope < 0) {
            down++;
        } else {
            candies++;
        }

        old_slope = new_slope;
    }

    candies += SumOfNaturals(up) + SumOfNaturals(down) + std::max(up, down) + 1;

    return candies;
}


/**
 * @reference   Maximum Valid Pair Sum
 *              https://leetcode.com/problems/maximum-valid-pair-sum/
 *
 * You are given an integer array nums of length n and an integer k.
 * A pair of indices (i, j) is called valid if:
 *  0 <= i < j < n
 *  j - i >= k
 * Return the maximum value of nums[i] + nums[j] among all valid pairs.
 *
 * @tags    #forward-and-backward #min-max-element #sliding-window
 */


/**
 * @reference   Smallest Stable Index I
 *              https://leetcode.com/problems/smallest-stable-index-i/
 * @reference   Smallest Stable Index II
 *              https://leetcode.com/problems/smallest-stable-index-ii/
 *
 * You are given an integer array nums of length n and an integer k.
 * For each index i, define its instability score as max(nums[0..i]) - min(nums[i..n - 1]).
 * In other words:
 *  max(nums[0..i]) is the largest value among the elements from index 0 to index i.
 *  min(nums[i..n - 1]) is the smallest value among the elements from index i to index n - 1.
 * An index i is called stable if its instability score is less than or equal to k.
 * Return the smallest stable index. If no such index exists, return -1.
 *
 * @tags    #forward-and-backward #min-max-element #sliding-window
 */

} //namespace


const ArrayType SAMPLE1 = {1, 0, 2};
const ArrayType SAMPLE2 = {1, 2, 2};


THE_BENCHMARK(Candy_TwoArray, SAMPLE1);

SIMPLE_TEST(Candy_TwoArray, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(Candy_TwoArray, TestSAMPLE2, 4, SAMPLE2);


THE_BENCHMARK(Candy_OneArray, SAMPLE1);

SIMPLE_TEST(Candy_OneArray, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(Candy_OneArray, TestSAMPLE2, 4, SAMPLE2);


THE_BENCHMARK(Candy_Slope, SAMPLE1);

SIMPLE_TEST(Candy_Slope, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(Candy_Slope, TestSAMPLE2, 4, SAMPLE2);
