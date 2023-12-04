#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Boats to Save People
 *
 * @reference   https://leetcode.com/problems/boats-to-save-people/
 *
 * You are given an array people where people[i] is the weight of the ith person, and an infinite number
 * of boats where each boat can carry a maximum weight of limit. Each boat carries at most two people at
 * the same time, provided the sum of the weight of those people is at most limit.
 * Return the minimum number of boats to carry every given person.
 */
auto BoatsToSavePeople(ArrayType people, const int limit) {
    std::sort(people.begin(), people.end());

    int left = 0;
    int right = people.size() - 1;

    int result = 0;
    while (left <= right) {
        ++result;
        if (people[left] + people[right--] <= limit) {
            ++left;
        }
    }

    return result;
}


/**
 * @reference   Minimize Maximum Pair Sum in Array
 *              https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/
 *
 * The pair sum of a pair (a,b) is equal to a + b. The maximum pair sum is the largest pair sum in a
 * list of pairs.
 *  For example, if we have pairs (1,5), (2,3), and (4,4), the maximum pair sum would be max(1+5, 2+3,
 *  4+4) = max(6, 5, 8) = 8.
 * Given an array nums of even length n, pair up the elements of nums into n / 2 pairs such that:
 *  Each element of nums is in exactly one pair, and
 *  The maximum pair sum is minimized.
 * Return the minimized maximum pair sum after optimally pairing up the elements.
 */


/**
 * @reference   Maximum Number of Coins You Can Get
 *              https://leetcode.com/problems/maximum-number-of-coins-you-can-get/
 *
 * There are 3n piles of coins of varying size, you and your friends will take piles of coins as
 * follows:
 *  In each step, you will choose any 3 piles of coins (not necessarily consecutive).
 *  Of your choice, Alice will pick the pile with the maximum number of coins.
 *  You will pick the next pile with the maximum number of coins.
 *  Your friend Bob will pick the last pile.
 *  Repeat until there are no more piles of coins.
 * Given an array of integers piles where piles[i] is the number of coins in the ith pile.
 * Return the maximum number of coins that you can have.
 */

} //namespace


const ArrayType SAMPLE1 = {1, 2};
const ArrayType SAMPLE2 = {3, 2, 2, 1};
const ArrayType SAMPLE3 = {3, 5, 3, 4};


THE_BENCHMARK(BoatsToSavePeople, SAMPLE1, 3);

SIMPLE_TEST(BoatsToSavePeople, TestSAMPLE1, 1, SAMPLE1, 3);
SIMPLE_TEST(BoatsToSavePeople, TestSAMPLE2, 3, SAMPLE2, 3);
SIMPLE_TEST(BoatsToSavePeople, TestSAMPLE3, 4, SAMPLE3, 5);
