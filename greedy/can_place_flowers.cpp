#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Can Place Flowers
 *
 * @reference   https://leetcode.com/problems/can-place-flowers/
 *
 * You have a long flowerbed in which some of the plots are planted, and some are not.
 * However, flowers cannot be planted in adjacent plots. Given an integer array flowerbed
 * containing 0's and 1's, where 0 means empty and 1 means not empty, and an integer n,
 * return if n new flowers can be planted in the flowerbed without violating the
 * no-adjacent-flowers rule.
 */
auto CanPlaceFlowers(const ArrayType &flowerbed, int m) {
    for (std::size_t i = 0; i < flowerbed.size(); ++i) {
        if (m == 0) {
            break;
        }

        if (flowerbed[i] == 1) {
            ++i;
        } else if (i + 1 == flowerbed.size() or flowerbed[i + 1] == 0) {
            ++i;
            --m;
        }
    }

    return m == 0;
}


/**
 * @reference   Split a String in Balanced Strings
 *              https://leetcode.com/problems/split-a-string-in-balanced-strings/
 *
 * Balanced strings are those that have an equal quantity of 'L' and 'R' characters.
 * Given a balanced string s, split it in the maximum amount of balanced strings.
 * Return the maximum amount of split balanced strings.
 */
constexpr auto SplitBalancedStrs(const std::string_view s) {
    int result = 0;
    int count = 0;
    for (const auto c : s) {
        if (c == 'L') {
            ++count;
        } else {
            --count;
        }

        if (count == 0) {
            ++result;
        }
    }

    return result;
}


/**
 * @reference   Maximize Distance to Closest Person
 *              https://leetcode.com/problems/maximize-distance-to-closest-person/
 *
 * You are given an array representing a row of seats where seats[i] = 1 represents a
 * person sitting in the ith seat, and seats[i] = 0 represents that the ith seat is empty
 * (0-indexed).
 * There is at least one empty seat, and at least one person sitting.
 * Alex wants to sit in the seat such that the distance between him and the closest
 * person to him is maximized.
 * Return that maximum distance to the closest person.
 */
auto MaxDistanceToClosestPerson(const ArrayType &seats) {
    std::size_t i = 0;
    int count = 0;
    while (seats[i++] == 0) {
        ++count;
    }

    auto result = count;
    count = 0;
    for (; i < seats.size(); ++i) {
        if (seats[i]) {
            result = std::max(result, (count + 1) / 2);
            count = 0;
        } else {
            ++count;
        }
    }

    return std::max(result, count);
}

}//namespace


const ArrayType SAMPLE1 = {1, 0, 0, 0, 1};
const ArrayType SAMPLE2 = {0, 0, 0};


THE_BENCHMARK(CanPlaceFlowers, SAMPLE1, 2);

SIMPLE_TEST(CanPlaceFlowers, TestSAMPLE1, true, SAMPLE1, 1);
SIMPLE_TEST(CanPlaceFlowers, TestSAMPLE2, false, SAMPLE1, 2);
SIMPLE_TEST(CanPlaceFlowers, TestSAMPLE3, true, SAMPLE2, 2);
SIMPLE_TEST(CanPlaceFlowers, TestSAMPLE4, false, SAMPLE2, 3);


THE_BENCHMARK(SplitBalancedStrs, "RLRRLLRLRL");

SIMPLE_TEST(SplitBalancedStrs, TestSAMPLE1, 4, "RLRRLLRLRL");
SIMPLE_TEST(SplitBalancedStrs, TestSAMPLE2, 3, "RLLLLRRRLR");
SIMPLE_TEST(SplitBalancedStrs, TestSAMPLE3, 1, "LLLLRRRR");
SIMPLE_TEST(SplitBalancedStrs, TestSAMPLE4, 2, "RLRRRLLRLL");


const ArrayType SAMPLE1S = {1, 0, 0, 0, 1, 0, 1};
const ArrayType SAMPLE2S = {1, 0, 0, 0};
const ArrayType SAMPLE3S = {0, 1};


THE_BENCHMARK(MaxDistanceToClosestPerson, SAMPLE1S);

SIMPLE_TEST(MaxDistanceToClosestPerson, TestSAMPLE1, 2, SAMPLE1S);
SIMPLE_TEST(MaxDistanceToClosestPerson, TestSAMPLE2, 3, SAMPLE2S);
SIMPLE_TEST(MaxDistanceToClosestPerson, TestSAMPLE3, 1, SAMPLE3S);
