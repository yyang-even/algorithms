#include "common_header.h"


namespace {

using ArrayType = std::vector<std::vector<int>>;

/**
 * @reference   Set Intersection Size At Least Two
 *              https://leetcode.com/problems/set-intersection-size-at-least-two/
 *
 * You are given a 2D integer array intervals where intervals[i] = [starti, endi] represents all the
 * integers from starti to endi inclusively.
 * A containing set is an array nums where each interval from intervals has at least two integers in
 * nums.
 *  For example, if intervals = [[1,3], [3,7], [8,9]], then [1,2,4,7,8,9] and [2,3,4,8,9] are containing
 *  sets.
 * Return the minimum possible size of a containing set.
 *
 * @tags    #greedy #sorting #sort-by-end
 */
auto IntersectionSizeAtLeastTwo(ArrayType intervals) {
    std::sort(intervals.begin(), intervals.end(), [](const auto &left, const auto &right) {
        if (left[1] == right[1]) {
            return left[0] > right[0];
        }
        return left[1] < right[1];
    });

    int result = 2;
    auto current = intervals.front()[1]; // end
    auto prev = current - 1;             // end - 1
    for (std::size_t i = 1; i < intervals.size(); ++i) {
        const auto start = intervals[i][0];
        const auto end = intervals[i][1];

        if (prev >= start) {
            continue;
        }

        ++result;
        if (start > current) { //no overlapping
            ++result;
            prev = end - 1;
        } else {
            prev = current;
        }
        current = end;
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {{1, 3}, {3, 7}, {8, 9}};
const ArrayType SAMPLE2 = {{1, 3}, {1, 4}, {2, 5}, {3, 5}};
const ArrayType SAMPLE3 = {{1, 2}, {2, 3}, {2, 4}, {4, 5}};


THE_BENCHMARK(IntersectionSizeAtLeastTwo, SAMPLE1);

SIMPLE_TEST(IntersectionSizeAtLeastTwo, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(IntersectionSizeAtLeastTwo, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(IntersectionSizeAtLeastTwo, TestSAMPLE3, 5, SAMPLE3);
