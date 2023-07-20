#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Asteroid Collision
 *
 * @reference   https://leetcode.com/problems/asteroid-collision/
 *
 * We are given an array asteroids of integers representing asteroids in a row.
 * For each asteroid, the absolute value represents its size, and the sign represents its direction
 * (positive meaning right, negative meaning left). Each asteroid moves at the same speed.
 * Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will
 * explode. If both are the same size, both will explode. Two asteroids moving in the same direction
 * will never meet.
 * asteroids[i] != 0
 */
auto AsteroidCollision(const ArrayType &asteroids) {
    ArrayType result;
    for (const auto a : asteroids) {
        while (not result.empty() and result.back() > 0 and result.back() < -a) {
            result.pop_back();
        }

        if (result.empty() or a > 0 or result.back() < 0) {
            result.push_back(a);
        } else if (a < 0 and result.back() == -a) {
            result.pop_back();
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {5, 10, -5};
const ArrayType EXPECTED1 = {5, 10};

const ArrayType SAMPLE2 = {8, -8};
const ArrayType EXPECTED2 = {};

const ArrayType SAMPLE3 = {10, 2, -5};
const ArrayType EXPECTED3 = {10};

const ArrayType SAMPLE4 = {-1, -2, 1, 2};


THE_BENCHMARK(AsteroidCollision, SAMPLE1);

SIMPLE_TEST(AsteroidCollision, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(AsteroidCollision, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(AsteroidCollision, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(AsteroidCollision, TestSAMPLE4, SAMPLE4, SAMPLE4);
