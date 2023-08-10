#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Movement of Robots
 *
 * @reference   https://leetcode.com/problems/movement-of-robots/
 *
 * Some robots are standing on an infinite number line with their initial coordinates given by a
 * 0-indexed integer array nums and will start moving once given the command to move. The robots will
 * move a unit distance each second.
 * You are given a string s denoting the direction in which robots will move on command. 'L' means the
 * robot will move towards the left side or negative side of the number line, whereas 'R' means the
 * robot will move towards the right side or positive side of the number line.
 * If two robots collide, they will start moving in opposite directions.
 * Return the sum of distances between all the pairs of robots d seconds after the command. Since the
 * sum can be very large, return it modulo 10^9 + 7.
 * Note:
 *  For two robots at the index i and j, pair (i,j) and pair (j,i) are considered the same pair.
 *  When robots collide, they instantly change their directions without wasting any time.
 *  Collision happens when two robots share the same place in a moment.
 *      For example, if a robot is positioned in 0 going to the right and another is positioned in 2
 *      going to the left, the next second they'll be both in 1 and they will change direction and the
 *      next second the first one will be in 0, heading left, and another will be in 2, heading right.
 *      For example, if a robot is positioned in 0 going to the right and another is positioned in 1
 *      going to the left, the next second the first one will be in 0, heading left, and another will be
 *      in 1, heading right.
 */
auto SumOfDistancesBetweenAllPairs(ArrayType nums) {
    std::sort(nums.begin(), nums.end());

    std::size_t prefix_sum = 0;
    std::size_t result = 0;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        result = (result + (i * nums[i] - prefix_sum)) % LARGE_PRIME;
        prefix_sum += nums[i];
    }

    return result;
}

auto MovementOfRobots(ArrayType nums, const std::string_view s, const int d) {
    for (std::size_t i = 0; i < nums.size(); ++i) {
        if (s[i] == 'R') {
            nums[i] += d;
        } else {
            nums[i] -= d;
        }
    }

    return SumOfDistancesBetweenAllPairs(std::move(nums));
}


/**
 * @reference   Last Moment Before All Ants Fall Out of a Plank
 *              https://leetcode.com/problems/last-moment-before-all-ants-fall-out-of-a-plank/
 *
 * We have a wooden plank of the length n units. Some ants are walking on the plank, each ant moves with
 * a speed of 1 unit per second. Some of the ants move to the left, the other move to the right.
 * When two ants moving in two different directions meet at some point, they change their directions and
 * continue moving again. Assume changing directions does not take any additional time.
 * When an ant reaches one end of the plank at a time t, it falls out of the plank immediately.
 * Given an integer n and two integer arrays left and right, the positions of the ants moving to the
 * left and the right, return the moment when the last ant(s) fall out of the plank.
 */

} //namespace


const ArrayType SAMPLE1 = {-2, 0, 2};
const ArrayType SAMPLE2 = {1, 0};


THE_BENCHMARK(MovementOfRobots, SAMPLE1, "RLL", 3);

SIMPLE_TEST(MovementOfRobots, TestSAMPLE1, 8, SAMPLE1, "RLL", 3);
SIMPLE_TEST(MovementOfRobots, TestSAMPLE2, 5, SAMPLE2, "RL", 2);
