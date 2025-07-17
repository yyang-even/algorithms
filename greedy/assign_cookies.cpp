#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Assign Cookies
 *
 * @reference   https://leetcode.com/problems/assign-cookies/
 *
 * Assume you are an awesome parent and want to give your children some cookies. But, you should give
 * each child at most one cookie.
 * Each child i has a greed factor g[i], which is the minimum size of a cookie that the child will be
 * content with; and each cookie j has a size s[j]. If s[j] >= g[i], we can assign the cookie j to the
 * child i, and the child i will be content. Your goal is to maximize the number of your content
 * children and output the maximum number.
 *
 * @reference   Maximum Matching of Players With Trainers
 *              https://leetcode.com/problems/maximum-matching-of-players-with-trainers/
 *
 * You are given a 0-indexed integer array players, where players[i] represents the ability of the ith
 * player. You are also given a 0-indexed integer array trainers, where trainers[j] represents the
 * training capacity of the jth trainer.
 * The ith player can match with the jth trainer if the player's ability is less than or equal to the
 * trainer's training capacity. Additionally, the ith player can be matched with at most one trainer,
 * and the jth trainer can be matched with at most one player.
 * Return the maximum number of matchings between players and trainers that satisfy these conditions.
 */
auto AssignCookies(ArrayType greed, ArrayType cookies) {
    std::sort(greed.begin(), greed.end());
    std::sort(cookies.begin(), cookies.end());

    std::size_t count = 0, i = 0;
    while (count < greed.size() and i < cookies.size()) {
        if (greed[count] <= cookies[i++]) {
            count++;
        }
    }

    return count;
}

} //namespace


const ArrayType SAMPLE1G = {1, 2, 3};
const ArrayType SAMPLE1C = {1, 1};

const ArrayType SAMPLE2G = {1, 2};
const ArrayType SAMPLE2C = {1, 2, 3};


THE_BENCHMARK(AssignCookies, SAMPLE1G, SAMPLE1C);

SIMPLE_TEST(AssignCookies, TestSAMPLE1, 1, SAMPLE1G, SAMPLE1C);
SIMPLE_TEST(AssignCookies, TestSAMPLE2, 2, SAMPLE2G, SAMPLE2C);
