#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Minimum Time to Make Rope Colorful
 *
 * @reference   https://leetcode.com/problems/minimum-time-to-make-rope-colorful/
 *
 * Alice has n balloons arranged on a rope. You are given a 0-indexed string colors where colors[i] is
 * the color of the ith balloon.
 * Alice wants the rope to be colorful. She does not want two consecutive balloons to be of the same
 * color, so she asks Bob for help. Bob can remove some balloons from the rope to make it colorful. You
 * are given a 0-indexed integer array neededTime where neededTime[i] is the time (in seconds) that Bob
 * needs to remove the ith balloon from the rope.
 * Return the minimum time Bob needs to make the rope colorful.
 */
auto MinTimeToMakeRopeColorful(const std::string_view colors, const ArrayType &neededTime) {
    char prev = 0;
    int result = 0;
    int sum = 0;
    int maxi = 0;
    for (std::size_t i = 0; i < colors.size(); ++i) {
        const auto c = colors[i];
        const auto t = neededTime[i];

        if (prev == c) {
            sum += t;
            maxi = std::max(maxi, t);
        } else {
            result += sum - maxi;
            maxi = t;
            sum = t;
            prev = c;
        }
    }

    return result + sum - maxi;
}

} //namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4, 5};
const ArrayType SAMPLE2 = {1, 2, 3};
const ArrayType SAMPLE3 = {1, 2, 3, 4, 1};


THE_BENCHMARK(MinTimeToMakeRopeColorful, "abaac", SAMPLE1);

SIMPLE_TEST(MinTimeToMakeRopeColorful, TestSAMPLE1, 3, "abaac", SAMPLE1);
SIMPLE_TEST(MinTimeToMakeRopeColorful, TestSAMPLE2, 0, "abc", SAMPLE2);
SIMPLE_TEST(MinTimeToMakeRopeColorful, TestSAMPLE3, 2, "aabaa", SAMPLE3);
