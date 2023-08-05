#include "common_header.h"


namespace {

using StartFinishPair = std::pair<int, int>;
using ArrayType = std::vector<StartFinishPair>;
using OutputType = std::vector<ArrayType::size_type>;
using JobType = std::tuple<int, int, int>;
using JobArray = std::vector<JobType>;

/** Activity Selection Problem
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 16.1.
 * @reference   Activity Selection Problem | Greedy Algo-1
 *              https://www.geeksforgeeks.org/activity-selection-problem-greedy-algo-1/
 * @reference   C Program for Activity Selection Problem | Greedy Algo-1
 *              https://www.geeksforgeeks.org/c-program-for-activity-selection-problem-greedy-algo-1/
 * @reference   Greedy approach vs Dynamic programming
 *              https://www.geeksforgeeks.org/greedy-approach-vs-dynamic-programming/
 *
 * You are given n activities with their start and finish times. Select the maximum number of activities
 * that can be performed by a single person, assuming that a person can only work on a single activity
 * at a time.
 */
constexpr auto finish_comparator = [](const auto &lhs, const auto &rhs) {
    return lhs.second < rhs.second;
};

constexpr auto start_comparator = [](const auto &lhs, const auto &rhs) {
    return lhs.first < rhs.first;
};

void ActivitySelection_Recursive(const ArrayType &activities,
                                 const ArrayType::size_type i,
                                 OutputType &selected_activities) {
    auto j = i + 1;
    for (; j < activities.size() and activities[j].first < activities[i].second; ++j)
        ;

    if (j < activities.size()) {
        selected_activities.push_back(j);
        ActivitySelection_Recursive(activities, j, selected_activities);
    }
}

inline auto ActivitySelection_Recursive(const ArrayType &activities) {
    assert(std::is_sorted(activities.cbegin(), activities.cend(), finish_comparator));

    OutputType selected_activities = {0};
    ActivitySelection_Recursive(activities, selected_activities.front(), selected_activities);
    return selected_activities;
}


auto ActivitySelection_Iterative(const ArrayType &activities) {
    assert(std::is_sorted(activities.cbegin(), activities.cend(), finish_comparator));

    ArrayType::size_type i = 0;
    OutputType selected_activities = {i};

    for (auto j = i + 1; j < activities.size(); ++j) {
        if (activities[j].first >= activities[i].second) {
            selected_activities.push_back(j);
            i = j;
        }
    }

    return selected_activities;
}


/**
 * @reference   Maximum Length Chain of Pairs | DP-20
 *              https://www.geeksforgeeks.org/maximum-length-chain-of-pairs-dp-20/
 * @reference   Maximum Length Chain of Pairs | Set-2
 *              https://www.geeksforgeeks.org/maximum-length-chain-of-pairs-set-2/
 *
 * Given an array of pairs of numbers of size N. In every pair, the first number is always smaller than
 * the second number. A pair (c, d) can follow another pair (a, b) if b < c. The chain of pairs can be
 * formed in this fashion. The task is to find the length of the longest chain which can be formed from
 * a given set of pairs.
 */
inline auto MaxLengthChainPairs(ArrayType activities) {
    std::sort(activities.begin(), activities.end(), finish_comparator);

    return ActivitySelection_Iterative(activities).size();
}


/**
 * @reference   Non-overlapping Intervals
 *              https://leetcode.com/problems/non-overlapping-intervals/
 *
 * Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum number
 * of intervals you need to remove to make the rest of the intervals non-overlapping.
 */
inline auto NonOverlappingIntervals(ArrayType intervals) {
    const auto size = intervals.size();
    return size - MaxLengthChainPairs(std::move(intervals));
}


/**
 * @reference   Meeting Rooms
 *              https://www.programcreek.com/2014/07/leetcode-meeting-rooms-java/
 *
 * Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...](si<
 * ei), determine if a person could attend all meetings.
 */
auto MeetingRooms(ArrayType activities) {
    std::sort(activities.begin(), activities.end(), finish_comparator);

    const auto N = activities.size();
    for (std::size_t i = 1; i < N; ++i) {
        if (activities[i - 1].second > activities[i].first) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Meeting Rooms II
 *              https://cheonhyangzhang.gitbooks.io/leetcode-solutions/content/253-meeting-rooms-ii---medium.html
 *
 * Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...](si<
 * ei), find the minimum number of conference rooms required.
 */
auto MinMeetingRooms_Heap(ArrayType activities) {
    std::sort(activities.begin(), activities.end(), start_comparator);

    std::priority_queue<int, std::vector<int>, std::greater<int>> rooms;
    rooms.push(activities.front().second);
    const auto N = activities.size();
    for (std::size_t i = 1; i < N; ++i) {
        if (activities[i].first >= rooms.top()) {
            rooms.pop();
        }
        rooms.push(activities[i].second);
    }

    return rooms.size();
}


auto MinMeetingRooms_PrefixSum(const ArrayType &activities) {
    std::map<int, int> room_counts;
    for (const auto &[start, finish] : activities) {
        ++room_counts[start];
        --room_counts[finish];
    }

    int prefix_sum = 0, maximum = 0;
    for (const auto [_, count] : room_counts) {
        prefix_sum += count;
        maximum = std::max(maximum, prefix_sum);
    }

    return maximum;
}


/**
 * @reference   Car Pooling
 *              https://leetcode.com/problems/car-pooling/
 * There is a car with capacity empty seats. The vehicle only drives east (i.e., it cannot turn around
 * and drive west).
 * You are given the integer capacity and an array trips where trips[i] = [numPassengersi, fromi, toi]
 * indicates that the ith trip has numPassengersi passengers and the locations to pick them up and drop
 * them off are fromi and toi respectively. The locations are given as the number of kilometers due east
 * from the car's initial location.
 * Return true if it is possible to pick up and drop off all passengers for all the given trips, or
 * false otherwise.
 * 0 <= fromi < toi <= 1000
 */
auto CarPooling(const JobArray &trips, const int capacity) {
    std::vector<int> passengers(1001, 0);
    for (const auto &[p, from, to] : trips) {
        passengers[from] += p;
        passengers[to] -= p;
    }

    int sum = 0;
    for (const auto p : passengers) {
        sum += p;
        if (sum > capacity) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Number of Students Doing Homework at a Given Time
 *              https://leetcode.com/problems/number-of-students-doing-homework-at-a-given-time/
 *
 * Given two integer arrays startTime and endTime and given an integer queryTime.
 * The ith student started doing their homework at the time startTime[i] and finished it at time
 * endTime[i].
 * Return the number of students doing their homework at time queryTime.  More formally, return the
 * number of students where queryTime lays in the interval [startTime[i], endTime[i]] inclusive.
 * 1 <= startTime[i] <= endTime[i] <= 1000
 */
auto BusyStudents(const ArrayType &times, const int query_time) {
    int result = 0;
    for (const auto &[start, end] : times) {
        if (start <= query_time and query_time <= end) {
            ++result;
        }
    }

    return result;
}


/**
 * @reference   Maximum Profit in Job Scheduling
 *              https://leetcode.com/problems/maximum-profit-in-job-scheduling/
 *
 * We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a
 * profit of profit[i].
 * You're given the startTime, endTime and profit arrays, return the maximum profit you can take such
 * that there are no two jobs in the subset with overlapping time range.
 * If you choose a job that ends at time X you will be able to start another job that starts at time X.
 *
 * @reference   Maximum Profit in Job Scheduling
 *              https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-1235-maximum-profit-in-job-scheduling/
 */
constexpr auto end_comparator = [](const auto &one, const auto &another) {
    return std::get<1>(one) < std::get<1>(another);
};

auto ToSortedJobs(const std::vector<int> &start_time,
                  const std::vector<int> &end_time,
                  const std::vector<int> &profit) {
    assert(start_time.size() == end_time.size() and start_time.size() == profit.size());

    JobArray jobs;
    for (std::size_t i = 0; i < start_time.size(); ++i) {
        jobs.emplace_back(start_time[i], end_time[i], profit[i]);
    }

    std::sort(jobs.begin(), jobs.end(), end_comparator);

    return jobs;
}

auto MaxProfitJobScheduling_DP_MAP(const std::vector<int> &start_time,
                                   const std::vector<int> &end_time,
                                   const std::vector<int> &profit) {
    const auto jobs = ToSortedJobs(start_time, end_time, profit);

    std::map<int, int> end_profix_map {{0, 0}};
    for (const auto &[start, end, a_profit] : jobs) {
        const auto new_profix = a_profit + std::prev(end_profix_map.upper_bound(start))->second;
        if (new_profix > end_profix_map.crbegin()->second) {
            end_profix_map[end] = new_profix;
        }
    }

    return end_profix_map.crbegin()->second;
}


/**
 * @reference   Weighted Job Scheduling
 *              https://www.geeksforgeeks.org/weighted-job-scheduling/
 * @reference   Weighted Job Scheduling in O(n Log n) time
 *              https://www.geeksforgeeks.org/weighted-job-scheduling-log-n-time/
 */
auto binarySearch(const JobArray &jobs, const int last) {
    int left = 0, right = last - 1;
    const auto start = std::get<0>(jobs[last]);

    while (left <= right) {
        const int mid = (left + right) / 2;
        if (std::get<1>(jobs[mid]) <= start) {
            if (std::get<1>(jobs[mid + 1]) <= start) {
                left = mid + 1;
            } else {
                return mid;
            }
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

auto MaxProfitJobScheduling_DP(const std::vector<int> &start_time,
                               const std::vector<int> &end_time,
                               const std::vector<int> &profit) {
    const auto jobs = ToSortedJobs(start_time, end_time, profit);

    int max_profix[jobs.size()] = {std::get<2>(jobs.front())};
    for (std::size_t i = 1; i < jobs.size(); ++i) {
        const auto latest_non_conflicting_index = binarySearch(jobs, i);
        auto profit_including_i = std::get<2>(jobs[i]);
        if (latest_non_conflicting_index != -1) {
            profit_including_i += max_profix[latest_non_conflicting_index];
        }

        max_profix[i] = std::max(profit_including_i, max_profix[i - 1]);
    }

    return max_profix[jobs.size() - 1];
}


/**
 * @reference   Minimum Number of Arrows to Burst Balloons
 *              https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
 *
 * There are some spherical balloons taped onto a flat wall that represents the XY-plane.  The balloons
 * are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a balloon whose
 * horizontal diameter stretches between xstart and xend. You do not know the exact y-coordinates of the
 * balloons.
 * Arrows can be shot up directly vertically (in the positive y-direction) from different points along
 * the x-axis. A balloon with xstart and xend is burst by an arrow shot at x if xstart <= x <= xend.
 * There is no limit to the number of arrows that can be shot. A shot arrow keeps traveling up
 * infinitely, bursting any balloons in its path.
 * Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
 * -2^31 <= xstart < xend <= 2^31 - 1
 */
auto MinArrows(ArrayType points) {
    std::sort(points.begin(), points.end(), finish_comparator);

    int result = 1;
    int arrow = points.front().second;
    for (const auto &[l, r] : points) {
        if (arrow >= l) {
            continue;
        }

        ++result;
        arrow = r;
    }

    return result;
}


/**
 * @reference   Maximum Number of Events That Can Be Attended
 *              https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/
 *
 * You are given an array of events where events[i] = [startDayi, endDayi]. Every event i starts at
 * startDayi and ends at endDayi.
 * You can attend an event i at any day d where startTimei <= d <= endTimei. You can only attend one
 * event at any time d.
 * Return the maximum number of events you can attend.
 */
auto MaxEvents(ArrayType events) {
    std::sort(events.begin(), events.end(), start_comparator);

    int result = 0;
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    int day = 0;
    for (std::size_t i = 0; true;) {
        while (i < events.size() and day >= events[i].first) {
            min_heap.push(events[i++].second);
        }

        while (not min_heap.empty() and day > min_heap.top()) {
            min_heap.pop();
        }

        if (not min_heap.empty()) {
            ++result;
            ++day;
            min_heap.pop();
        } else if (i < events.size()) {
            day = events[i].first;
        } else {
            break;
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {{10, 20}, {12, 25}, {20, 30}};
const OutputType EXPECTED1 = {0, 2};

const ArrayType SAMPLE2 = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};
const OutputType EXPECTED2 = {0, 1, 3, 4};

const ArrayType SAMPLE3 = {
    {1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}};
const OutputType EXPECTED3 = {0, 3, 7, 10};


THE_BENCHMARK(ActivitySelection_Recursive, SAMPLE1);

SIMPLE_TEST(ActivitySelection_Recursive, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ActivitySelection_Recursive, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(ActivitySelection_Recursive, TestSAMPLE3, EXPECTED3, SAMPLE3);


THE_BENCHMARK(ActivitySelection_Iterative, SAMPLE1);

SIMPLE_TEST(ActivitySelection_Iterative, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ActivitySelection_Iterative, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(ActivitySelection_Iterative, TestSAMPLE3, EXPECTED3, SAMPLE3);


const ArrayType SAMPLE4 = {{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90}};
const ArrayType SAMPLE5 = {{5, 10}, {1, 11}};


THE_BENCHMARK(MaxLengthChainPairs, SAMPLE1);

SIMPLE_TEST(MaxLengthChainPairs, TestSAMPLE1, EXPECTED1.size(), SAMPLE1);
SIMPLE_TEST(MaxLengthChainPairs, TestSAMPLE2, EXPECTED2.size(), SAMPLE2);
SIMPLE_TEST(MaxLengthChainPairs, TestSAMPLE3, EXPECTED3.size(), SAMPLE3);
SIMPLE_TEST(MaxLengthChainPairs, TestSAMPLE4, 3, SAMPLE4);
SIMPLE_TEST(MaxLengthChainPairs, TestSAMPLE5, 1, SAMPLE5);


const ArrayType SAMPLE6 = {{1, 2}, {3, 4}, {5, 7}, {8, 9}};


THE_BENCHMARK(MeetingRooms, SAMPLE1);

SIMPLE_TEST(MeetingRooms, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(MeetingRooms, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(MeetingRooms, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(MeetingRooms, TestSAMPLE4, false, SAMPLE4);
SIMPLE_TEST(MeetingRooms, TestSAMPLE5, false, SAMPLE5);
SIMPLE_TEST(MeetingRooms, TestSAMPLE6, true, SAMPLE6);


const ArrayType SAMPLE7 = {{2, 15}, {36, 45}, {9, 29}, {16, 23}, {4, 9}};


THE_BENCHMARK(MinMeetingRooms_Heap, SAMPLE1);

SIMPLE_TEST(MinMeetingRooms_Heap, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(MinMeetingRooms_Heap, TestSAMPLE5, 2, SAMPLE5);
SIMPLE_TEST(MinMeetingRooms_Heap, TestSAMPLE6, 1, SAMPLE6);
SIMPLE_TEST(MinMeetingRooms_Heap, TestSAMPLE7, 2, SAMPLE7);


THE_BENCHMARK(MinMeetingRooms_PrefixSum, SAMPLE1);

SIMPLE_TEST(MinMeetingRooms_PrefixSum, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(MinMeetingRooms_PrefixSum, TestSAMPLE5, 2, SAMPLE5);
SIMPLE_TEST(MinMeetingRooms_PrefixSum, TestSAMPLE6, 1, SAMPLE6);
SIMPLE_TEST(MinMeetingRooms_PrefixSum, TestSAMPLE7, 2, SAMPLE7);


const std::vector SAMPLE1S = {1, 2, 3, 3};
const std::vector SAMPLE1E = {3, 4, 5, 6};
const std::vector SAMPLE1P = {50, 10, 40, 70};

const std::vector SAMPLE2S = {1, 2, 3, 4, 6};
const std::vector SAMPLE2E = {3, 5, 10, 6, 9};
const std::vector SAMPLE2P = {20, 20, 100, 70, 60};

const std::vector SAMPLE3S = {1, 1, 1};
const std::vector SAMPLE3E = {2, 3, 4};
const std::vector SAMPLE3P = {5, 6, 4};


THE_BENCHMARK(MaxProfitJobScheduling_DP_MAP, SAMPLE1S, SAMPLE1E, SAMPLE1P);

SIMPLE_TEST(MaxProfitJobScheduling_DP_MAP, TestSAMPLE1, 120, SAMPLE1S, SAMPLE1E, SAMPLE1P);
SIMPLE_TEST(MaxProfitJobScheduling_DP_MAP, TestSAMPLE2, 150, SAMPLE2S, SAMPLE2E, SAMPLE2P);
SIMPLE_TEST(MaxProfitJobScheduling_DP_MAP, TestSAMPLE3, 6, SAMPLE3S, SAMPLE3E, SAMPLE3P);


THE_BENCHMARK(MaxProfitJobScheduling_DP, SAMPLE1S, SAMPLE1E, SAMPLE1P);

SIMPLE_TEST(MaxProfitJobScheduling_DP, TestSAMPLE1, 120, SAMPLE1S, SAMPLE1E, SAMPLE1P);
SIMPLE_TEST(MaxProfitJobScheduling_DP, TestSAMPLE2, 150, SAMPLE2S, SAMPLE2E, SAMPLE2P);
SIMPLE_TEST(MaxProfitJobScheduling_DP, TestSAMPLE3, 6, SAMPLE3S, SAMPLE3E, SAMPLE3P);


const JobArray SAMPLE1T = {{2, 1, 5}, {3, 3, 7}};


THE_BENCHMARK(CarPooling, SAMPLE1T, 5);

SIMPLE_TEST(CarPooling, TestSAMPLE1, false, SAMPLE1T, 4);
SIMPLE_TEST(CarPooling, TestSAMPLE2, true, SAMPLE1T, 5);


const ArrayType SAMPLE1H = {{1, 3}, {2, 2}, {3, 7}};
const ArrayType SAMPLE2H = {{4, 4}};


THE_BENCHMARK(BusyStudents, SAMPLE1H, 4);

SIMPLE_TEST(BusyStudents, TestSAMPLE1, 1, SAMPLE1H, 4);
SIMPLE_TEST(BusyStudents, TestSAMPLE2, 1, SAMPLE2H, 4);


const ArrayType SAMPLE1B = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
const ArrayType SAMPLE2B = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
const ArrayType SAMPLE3B = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};


THE_BENCHMARK(MinArrows, SAMPLE1B);

SIMPLE_TEST(MinArrows, TestSAMPLE1, 2, SAMPLE1B);
SIMPLE_TEST(MinArrows, TestSAMPLE2, 4, SAMPLE2B);
SIMPLE_TEST(MinArrows, TestSAMPLE3, 2, SAMPLE3B);


const ArrayType SAMPLE1ME = {{1, 2}, {2, 3}, {3, 4}};
const ArrayType SAMPLE2ME = {{1, 2}, {2, 3}, {3, 4}, {1, 2}};


THE_BENCHMARK(MaxEvents, SAMPLE1ME);

SIMPLE_TEST(MaxEvents, TestSAMPLE1, 3, SAMPLE1ME);
SIMPLE_TEST(MaxEvents, TestSAMPLE2, 4, SAMPLE2ME);


const ArrayType SAMPLE1I = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
const ArrayType SAMPLE2I = {{1, 2}, {1, 2}, {1, 2}};
const ArrayType SAMPLE3I = {{1, 2}, {2, 3}};
const ArrayType SAMPLE4I = {{0, 2}, {1, 3}, {1, 3}, {2, 4}, {3, 5}, {3, 5}, {4, 6}};
const ArrayType SAMPLE5I = {
    {-25322, -4602}, {-35630, -28832}, {-33802, 29009}, {13393, 24550},   {-10655, 16361},
    {-2835, 10053},  {-2290, 17156},   {1236, 14847},   {-45022, -1296},  {-34574, -1993},
    {-14129, 15626}, {3010, 14502},    {42403, 45946},  {-22117, 13380},  {7337, 33635},
    {-38153, 27794}, {47640, 49108},   {40578, 46264},  {-38497, -13790}, {-7530, 4977},
    {-29009, 43543}, {-49069, 32526},  {21409, 43622},  {-28569, 16493},  {-28301, 34058}};


THE_BENCHMARK(NonOverlappingIntervals, SAMPLE1I);

SIMPLE_TEST(NonOverlappingIntervals, TestSAMPLE1, 1, SAMPLE1I);
SIMPLE_TEST(NonOverlappingIntervals, TestSAMPLE2, 2, SAMPLE2I);
SIMPLE_TEST(NonOverlappingIntervals, TestSAMPLE3, 0, SAMPLE3I);
SIMPLE_TEST(NonOverlappingIntervals, TestSAMPLE4, 4, SAMPLE4I);
SIMPLE_TEST(NonOverlappingIntervals, TestSAMPLE5, 19, SAMPLE5I);
