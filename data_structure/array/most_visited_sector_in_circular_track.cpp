#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Most Visited Sector in a Circular Track
 *
 * @reference   https://leetcode.com/problems/most-visited-sector-in-a-circular-track/
 *
 * Given an integer n and an integer array rounds. We have a circular track which consists of n sectors
 * labeled from 1 to n. A marathon will be held on this track, the marathon consists of m rounds. The
 * ith round starts at sector rounds[i - 1] and ends at sector rounds[i]. For example, round 1 starts at
 * sector rounds[0] and ends at sector rounds[1]
 * Return an array of the most visited sectors sorted in ascending order.
 * Notice that you circulate the track in ascending order of sector numbers in the counter-clockwise
 * direction (See the first example).
 * 2 <= n <= 100
 */
auto MostVisited(const int n, const ArrayType &rounds) {
    ArrayType result;

    if (rounds.front() <= rounds.back()) {
        for (auto i = rounds.front(); i <= rounds.back(); ++i) {
            result.push_back(i);
        }

    } else {
        for (int i = 1; i <= rounds.back(); ++i) {
            result.push_back(i);
        }
        for (auto i = rounds.front(); i <= n; ++i) {
            result.push_back(i);
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {1, 3, 1, 2};
const ArrayType EXPECTED1 = {1, 2};

const ArrayType SAMPLE2 = {2, 1, 2, 1, 2, 1, 2, 1, 2};
const ArrayType EXPECTED2 = {2};

const ArrayType SAMPLE3 = {1, 3, 5, 7};
const ArrayType EXPECTED3 = {1, 2, 3, 4, 5, 6, 7};


THE_BENCHMARK(MostVisited, 4, SAMPLE1);

SIMPLE_TEST(MostVisited, TestSAMPLE1, EXPECTED1, 4, SAMPLE1);
SIMPLE_TEST(MostVisited, TestSAMPLE2, EXPECTED2, 2, SAMPLE2);
SIMPLE_TEST(MostVisited, TestSAMPLE3, EXPECTED3, 7, SAMPLE3);
