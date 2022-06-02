#include "common_header.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

/** Merge Intervals
 *
 * @reference   https://leetcode.com/problems/merge-intervals/
 *
 * Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping
 * intervals, and return an array of the non-overlapping intervals that cover all the
 * intervals in the input.
 */
auto MergeIntervals(ArrayType intervals) {
    std::sort(intervals.begin(), intervals.end());

    ArrayType result = {intervals.front()};
    const auto N = intervals.size();
    for (std::size_t i = 1; i < N; ++i) {
        if (intervals[i].first <= result.back().second) {
            if (intervals[i].second > result.back().second) {
                result.back().second = intervals[i].second;
            }
        } else {
            result.push_back(intervals[i]);
        }
    }

    return result;
}


/**
 * @reference   Insert Interval
 *              https://leetcode.com/problems/insert-interval/
 *
 * Given a set of non-overlapping intervals, insert a new interval into the intervals
 * (merge if necessary). You may assume that the intervals were initially sorted
 * according to their start times.
 */
auto InsertInterval(const ArrayType &intervals, std::pair<int, int> new_interval) {
    ArrayType result;
    std::size_t i = 0;
    while (i < intervals.size() and intervals[i].second < new_interval.first) {
        result.push_back(intervals[i++]);
    }

    while (i < intervals.size()) {
        const int left = std::max(intervals[i].first, new_interval.first);
        const int right = std::min(intervals[i].second, new_interval.second);
        if (left <= right) {
            new_interval.first = std::min(intervals[i].first, new_interval.first);
            new_interval.second = std::max(intervals[i].second, new_interval.second);
            i++;
        } else {
            break;
        }
    }
    result.push_back(new_interval);

    while (i < intervals.size()) {
        result.push_back(intervals[i++]);
    }

    return result;
}


/** Teemo Attacking
 *
 * @reference   https://leetcode.com/problems/teemo-attacking/
 *
 * Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo attacks
 * Ashe, Ashe gets poisoned for a exactly duration seconds. More formally, an attack at
 * second t will mean Ashe is poisoned during the inclusive time interval
 * [t, t + duration - 1]. If Teemo attacks again before the poison effect ends, the
 * timer for it is reset, and the poison effect will end duration seconds after the new
 * attack. You are given a non-decreasing integer array timeSeries, where timeSeries[i]
 * denotes that Teemo attacks Ashe at second timeSeries[i], and an integer duration.
 * Return the total number of seconds that Ashe is poisoned.
 */
auto TotalPoisonedDuration(const std::vector<int> &time_series, const int duration) {
    assert(time_series.size() > 0);

    int result = duration;
    for (std::size_t i = 1; i < time_series.size(); ++i) {
        result += std::min(time_series[i] - time_series[i - 1], duration);
    }

    return result;
}


/**
 * @reference   Remove Covered Intervals
 *              https://leetcode.com/problems/remove-covered-intervals/
 *
 * Given an array intervals where intervals[i] = [li, ri] represent the interval [li, ri),
 * remove all intervals that are covered by another interval in the list.
 * The interval [a, b) is covered by the interval [c, d) if and only if c <= a and b <= d.
 * Return the number of remaining intervals.
 */
auto RemoveCoveredIntervals(ArrayType intervals) {
    std::sort(intervals.begin(), intervals.end(), [](const auto one, const auto another) {
        if (one.first == another.first) {
            return one.second > another.second;
        }
        return one.first < another.first;
    });

    int result = 0;
    int right = 0;
    for (const auto [li, ri] : intervals) {
        if (ri > right) {
            ++result;
            right = ri;
        }
    }

    return result;
}


/**
 * @reference   Partition Labels
 *              https://leetcode.com/problems/partition-labels/
 *
 * You are given a string s. We want to partition the string into as many parts as possible
 * so that each letter appears in at most one part.
 * Note that the partition is done so that after concatenating all the parts in order, the
 * resultant string should be s.
 * Return a list of integers representing the size of these parts.
 * s consists of lowercase English letters.
 */
auto PartitionLabels(const std::string_view s) {
    std::size_t last[256] = {};
    for (std::size_t i = 0; i < s.size(); ++i) {
        const int c = s[i];
        last[c] = i;
    }

    std::size_t start = 0;
    std::size_t end = 0;
    std::vector<int> result;
    for (std::size_t i = 0; i < s.size(); ++i) {
        const int c = s[i];
        end = std::max(end, last[c]);
        if (i == end) {
            result.push_back(i + 1 - start);
            start = i + 1;
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
const ArrayType EXPECTED1 = {{1, 6}, {8, 10}, {15, 18}};

const ArrayType SAMPLE2 = {{1, 4}, {4, 5}};
const ArrayType EXPECTED2 = {{1, 5}};

const ArrayType SAMPLE3 = {{1, 4}, {2, 3}};
const ArrayType EXPECTED3 = {{1, 4}};


THE_BENCHMARK(MergeIntervals, SAMPLE1);

SIMPLE_TEST(MergeIntervals, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(MergeIntervals, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(MergeIntervals, TestSAMPLE3, EXPECTED3, SAMPLE3);


const std::vector SAMPLE1T = {1, 4};
const std::vector SAMPLE2T = {1, 2};


THE_BENCHMARK(TotalPoisonedDuration, SAMPLE1T, 2);

SIMPLE_TEST(TotalPoisonedDuration, TestSAMPLE1, 4, SAMPLE1T, 2);
SIMPLE_TEST(TotalPoisonedDuration, TestSAMPLE2, 3, SAMPLE2T, 2);


const ArrayType SAMPLE1I = {{1, 3}, {6, 9}};
const std::pair SAMPLE1P = {2, 5};
const ArrayType EXPECTED1I = {{1, 5}, {6, 9}};

const ArrayType SAMPLE2I = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
const std::pair SAMPLE2P = {4, 8};
const ArrayType EXPECTED2I = {{1, 2}, {3, 10}, {12, 16}};

const ArrayType SAMPLE3I = {};
const std::pair SAMPLE3P = {5, 7};
const ArrayType EXPECTED3I = {{5, 7}};

const ArrayType SAMPLE4I = {{1, 5}};
const std::pair SAMPLE4P = {2, 3};

const ArrayType SAMPLE5I = {{1, 5}};
const std::pair SAMPLE5P = {2, 7};
const ArrayType EXPECTED5I = {{1, 7}};


THE_BENCHMARK(InsertInterval, SAMPLE1I, SAMPLE1P);

SIMPLE_TEST(InsertInterval, TestSAMPLE1, EXPECTED1I, SAMPLE1I, SAMPLE1P);
SIMPLE_TEST(InsertInterval, TestSAMPLE2, EXPECTED2I, SAMPLE2I, SAMPLE2P);
SIMPLE_TEST(InsertInterval, TestSAMPLE3, EXPECTED3I, SAMPLE3I, SAMPLE3P);
SIMPLE_TEST(InsertInterval, TestSAMPLE4, SAMPLE4I, SAMPLE4I, SAMPLE4P);
SIMPLE_TEST(InsertInterval, TestSAMPLE5, EXPECTED5I, SAMPLE5I, SAMPLE5P);


const ArrayType SAMPLE1R = {{1, 4}, {3, 6}, {2, 8}};
const ArrayType SAMPLE2R = {{1, 4}, {2, 3}};
const ArrayType SAMPLE3R = {{3, 10}, {4, 10}, {5, 11}};


THE_BENCHMARK(RemoveCoveredIntervals, SAMPLE1R);

SIMPLE_TEST(RemoveCoveredIntervals, TestSAMPLE1, 2, SAMPLE1R);
SIMPLE_TEST(RemoveCoveredIntervals, TestSAMPLE2, 1, SAMPLE2R);
SIMPLE_TEST(RemoveCoveredIntervals, TestSAMPLE3, 2, SAMPLE3R);


const std::vector EXPECTED1L = {9, 7, 8};
const std::vector EXPECTED2L = {10};


THE_BENCHMARK(PartitionLabels, "ababcbacadefegdehijhklij");

SIMPLE_TEST(PartitionLabels, TestSAMPLE1, EXPECTED1L, "ababcbacadefegdehijhklij");
SIMPLE_TEST(PartitionLabels, TestSAMPLE2, EXPECTED2L, "eccbbbbdec");