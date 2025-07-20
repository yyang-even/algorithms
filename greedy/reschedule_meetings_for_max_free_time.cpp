#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;


/**
 * @reference   Reschedule Meetings for Maximum Free Time I
 *              https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i/
 *
 * You are given an integer eventTime denoting the duration of an event, where the event occurs from
 * time t = 0 to time t = eventTime.
 * You are also given two integer arrays startTime and endTime, each of length n. These represent the
 * start and end time of n non-overlapping meetings, where the ith meeting occurs during the time
 * [startTime[i], endTime[i]].
 * You can reschedule at most k meetings by moving their start time while maintaining the same duration,
 * to maximize the longest continuous period of free time during the event.
 * The relative order of all the meetings should stay the same and they should remain non-overlapping.
 * Return the maximum amount of free time possible after rearranging the meetings.
 * Note that the meetings can not be rescheduled to a time outside the event.
 */
auto RescheduleMeetingsForMaxFreeTimeStable(const int eventTime,
                                            const std::size_t k,
                                            const ArrayType &startTime,
                                            const ArrayType &endTime) {
    ArrayType gaps;
    int prev = 0;
    for (std::size_t i = 0; i < startTime.size(); ++i) {
        const auto a_gap = startTime[i] - prev;
        gaps.push_back(a_gap);
        prev = endTime[i];
    }
    const auto a_gap = eventTime - prev;
    gaps.push_back(a_gap);

    int result = 0;
    for (std::size_t i = 0; i < std::min(k + 1, gaps.size()); ++i) {
        result += gaps[i];
    }

    int sum = result;
    for (auto i = k + 1; i < gaps.size(); ++i) {
        sum = sum - gaps[i - k - 1] + gaps[i];
        result = std::max(sum, result);
    }

    return result;
}


/**
 * @reference   Reschedule Meetings for Maximum Free Time II
 *              https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-ii/
 *
 * You are given an integer eventTime denoting the duration of an event. You are also given two integer
 * arrays startTime and endTime, each of length n.
 * These represent the start and end times of n non-overlapping meetings that occur during the event
 * between time t = 0 and time t = eventTime, where the ith meeting occurs during the time
 * [startTime[i], endTime[i]].
 * You can reschedule at most one meeting by moving its start time while maintaining the same duration,
 * such that the meetings remain non-overlapping, to maximize the longest continuous period of free time
 * during the event.
 * Return the maximum amount of free time possible after rearranging the meetings.
 * Note that the meetings can not be rescheduled to a time outside the event and they should remain
 * non-overlapping.
 * Note: In this version, it is valid for the relative ordering of the meetings to change after
 * rescheduling one meeting.
 *
 * @tags    #forward-and-backward
 */
auto RescheduleMeetingsForMaxFreeTimeUnstable(const int eventTime,
                                              const ArrayType &startTime,
                                              const ArrayType &endTime) {
    const int N = startTime.size();

    ArrayType gaps;
    int prev = 0;
    for (int i = 0; i < N; ++i) {
        const auto a_gap = startTime[i] - prev;
        gaps.push_back(a_gap);
        prev = endTime[i];
    }
    const auto a_gap = eventTime - prev;
    gaps.push_back(a_gap);

    ArrayType largest_of_right(gaps.size(), 0);
    for (int i = N - 1; i >= 0; --i) {
        largest_of_right[i] = std::max(largest_of_right[i + 1], gaps[i + 1]);
    }

    int largest_of_left = 0;
    int result = 0;
    for (int i = 1; i <= N; ++i) {
        const auto duration = endTime[i - 1] - startTime[i - 1];
        const auto can_fit = (largest_of_left >= duration) or (largest_of_right[i] >= duration);

        auto free_time = gaps[i - 1] + gaps[i];
        if (can_fit) {
            free_time += duration;
        }

        result = std::max(result, free_time);
        largest_of_left = std::max(largest_of_left, gaps[i - 1]);
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1S = {1, 3};
const ArrayType SAMPLE1E = {2, 5};

const ArrayType SAMPLE2S = {0, 2, 9};
const ArrayType SAMPLE2E = {1, 4, 10};

const ArrayType SAMPLE3S = {0, 1, 2, 3, 4};
const ArrayType SAMPLE3E = {1, 2, 3, 4, 5};

const ArrayType SAMPLE4S = {7, 10, 16};
const ArrayType SAMPLE4E = {10, 14, 18};


THE_BENCHMARK(RescheduleMeetingsForMaxFreeTimeStable, 5, 1, SAMPLE1S, SAMPLE1E);

SIMPLE_TEST(RescheduleMeetingsForMaxFreeTimeStable, TestSAMPLE1, 2, 5, 1, SAMPLE1S, SAMPLE1E);
SIMPLE_TEST(RescheduleMeetingsForMaxFreeTimeStable, TestSAMPLE2, 6, 10, 1, SAMPLE2S, SAMPLE2E);
SIMPLE_TEST(RescheduleMeetingsForMaxFreeTimeStable, TestSAMPLE3, 0, 5, 2, SAMPLE3S, SAMPLE3E);
SIMPLE_TEST(RescheduleMeetingsForMaxFreeTimeStable, TestSAMPLE4, 7, 21, 1, SAMPLE4S, SAMPLE4E);


const ArrayType SAMPLE5S = {0, 7, 9};
const ArrayType SAMPLE5E = {1, 8, 10};

const ArrayType SAMPLE6S = {0, 3, 7, 9};
const ArrayType SAMPLE6E = {1, 4, 8, 10};

const ArrayType SAMPLE7S = {17, 24};
const ArrayType SAMPLE7E = {19, 25};


THE_BENCHMARK(RescheduleMeetingsForMaxFreeTimeUnstable, 5, SAMPLE1S, SAMPLE1E);

SIMPLE_TEST(RescheduleMeetingsForMaxFreeTimeUnstable, TestSAMPLE1, 2, 5, SAMPLE1S, SAMPLE1E);
SIMPLE_TEST(RescheduleMeetingsForMaxFreeTimeUnstable, TestSAMPLE3, 0, 5, SAMPLE3S, SAMPLE3E);
SIMPLE_TEST(RescheduleMeetingsForMaxFreeTimeUnstable, TestSAMPLE5, 7, 10, SAMPLE5S, SAMPLE5E);
SIMPLE_TEST(RescheduleMeetingsForMaxFreeTimeUnstable, TestSAMPLE6, 6, 10, SAMPLE6S, SAMPLE6E);
SIMPLE_TEST(RescheduleMeetingsForMaxFreeTimeUnstable, TestSAMPLE7, 24, 41, SAMPLE7S, SAMPLE7E);
