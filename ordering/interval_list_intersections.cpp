#include "common_header.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

/** Interval List Intersections
 *
 * @reference   https://leetcode.com/problems/interval-list-intersections/
 *
 * You are given two lists of closed intervals, firstList and secondList, where
 * firstList[i] = [starti, endi] and secondList[j] = [startj, endj]. Each list of
 * intervals is pairwise disjoint and in sorted order. Return the intersection of these
 * two interval lists.
 * A closed interval [a, b] (with a <= b) denotes the set of real numbers x with
 * a <= x <= b.
 * The intersection of two closed intervals is a set of real numbers that are either
 * empty or represented as a closed interval. For example, the intersection of [1, 3]
 * and [2, 4] is [2, 3].
 */
auto IntervalListIntersections(const ArrayType &first_list,
                               const ArrayType &second_list) {
    ArrayType result;

    std::size_t i = 0;
    std::size_t j = 0;
    while (i < first_list.size() and j < second_list.size()) {
        const auto low = std::max(first_list[i].first, second_list[j].first);
        const auto high = std::min(first_list[i].second, second_list[j].second);

        if (low <= high) {
            result.emplace_back(low, high);
        }

        if (first_list[i].second < second_list[j].second) {
            ++i;
        } else {
            ++j;
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1F = {{0, 2}, {5, 10}, {13, 23}, {24, 25}};
const ArrayType SAMPLE1S = {{1, 5}, {8, 12}, {15, 24}, {25, 26}};
const ArrayType EXPECTED1 = {{1, 2}, {5, 5}, {8, 10}, {15, 23}, {24, 24}, {25, 25}};

const ArrayType SAMPLE2F = {{1, 3}, {5, 9}};
const ArrayType EMPTY = {};

const ArrayType SAMPLE3S = {{4, 8}, {10, 12}};

const ArrayType SAMPLE4F = {{1, 7}};
const ArrayType SAMPLE4S = {{3, 10}};
const ArrayType EXPECTED4 = {{3, 7}};


THE_BENCHMARK(IntervalListIntersections, SAMPLE1F, SAMPLE1S);

SIMPLE_TEST(IntervalListIntersections, TestSAMPLE1, EXPECTED1, SAMPLE1F, SAMPLE1S);
SIMPLE_TEST(IntervalListIntersections, TestSAMPLE2, EMPTY, SAMPLE1F, EMPTY);
SIMPLE_TEST(IntervalListIntersections, TestSAMPLE3, EMPTY, EMPTY, SAMPLE3S);
SIMPLE_TEST(IntervalListIntersections, TestSAMPLE4, EXPECTED4, SAMPLE4F, SAMPLE4S);
