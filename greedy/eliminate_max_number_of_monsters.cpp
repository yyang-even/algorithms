#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Eliminate Maximum Number of Monsters
 *
 * @reference   https://leetcode.com/problems/eliminate-maximum-number-of-monsters/
 *
 * You are playing a video game where you are defending your city from a group of n monsters. You are
 * given a 0-indexed integer array dist of size n, where dist[i] is the initial distance in kilometers
 * of the ith monster from the city.
 * The monsters walk toward the city at a constant speed. The speed of each monster is given to you in
 * an integer array speed of size n, where speed[i] is the speed of the ith monster in kilometers per
 * minute.
 * You have a weapon that, once fully charged, can eliminate a single monster. However, the weapon takes
 * one minute to charge. The weapon is fully charged at the very start.
 * You lose when any monster reaches your city. If a monster reaches the city at the exact moment the
 * weapon is fully charged, it counts as a loss, and the game ends before you can use your weapon.
 * Return the maximum number of monsters that you can eliminate before you lose, or n if you can
 * eliminate all the monsters before they reach the city.
 */
auto EliminateMaxNumberOfMonsters(const ArrayType &dist, const ArrayType &speed) {
    std::vector<unsigned> arrival_time;
    for (std::size_t i = 0; i < dist.size(); ++i) {
        arrival_time.push_back(std::ceil(static_cast<double>(dist[i]) / speed[i]));
    }

    std::sort(arrival_time.begin(), arrival_time.end());

    int result = 0;
    for (std::size_t i = 0; i < arrival_time.size(); ++i) {
        if (arrival_time[i] > i)
            ++result;
        else
            break;
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1D = {1, 3, 4};
const ArrayType SAMPLE1S = {1, 1, 1};

const ArrayType SAMPLE2D = {1, 1, 2, 3};
const ArrayType SAMPLE2S = {1, 1, 1, 1};

const ArrayType SAMPLE3D = {3, 2, 4};
const ArrayType SAMPLE3S = {5, 3, 2};

const ArrayType SAMPLE4D = {3, 5, 7, 4, 5};
const ArrayType SAMPLE4S = {2, 3, 6, 3, 2};


THE_BENCHMARK(EliminateMaxNumberOfMonsters, SAMPLE1D, SAMPLE1S);

SIMPLE_TEST(EliminateMaxNumberOfMonsters, TestSAMPLE1, 3, SAMPLE1D, SAMPLE1S);
SIMPLE_TEST(EliminateMaxNumberOfMonsters, TestSAMPLE2, 1, SAMPLE2D, SAMPLE2S);
SIMPLE_TEST(EliminateMaxNumberOfMonsters, TestSAMPLE3, 1, SAMPLE3D, SAMPLE3S);
SIMPLE_TEST(EliminateMaxNumberOfMonsters, TestSAMPLE4, 2, SAMPLE4D, SAMPLE4S);
