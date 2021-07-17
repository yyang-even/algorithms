#include "common_header.h"


namespace {

using StartFinishPair = std::pair<unsigned, unsigned>;
using ArrayType = std::vector<StartFinishPair>;
using OutputType = std::vector<ArrayType::size_type>;

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
 * You are given n activities with their start and finish times. Select the maximum number
 * of activities that can be performed by a single person, assuming that a person can only
 * work on a single activity at a time.
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
    for (; j < activities.size() and activities[j].first < activities[i].second; ++j);

    if (j < activities.size()) {
        selected_activities.push_back(j);
        ActivitySelection_Recursive(activities, j, selected_activities);
    }
}

inline auto ActivitySelection_Recursive(const ArrayType &activities) {
    assert(std::is_sorted(activities.cbegin(), activities.cend(), finish_comparator));

    OutputType selected_activities = {0};
    ActivitySelection_Recursive(
        activities, selected_activities.front(), selected_activities);
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
 * Given an array of pairs of numbers of size N. In every pair, the first number is
 * always smaller than the second number. A pair (c, d) can follow another pair (a, b)
 * if b < c. The chain of pairs can be formed in this fashion. The task is to find the
 * length of the longest chain which can be formed from a given set of pairs.
 */
inline auto MaxLengthChainPairs(ArrayType activities) {
    std::sort(activities.begin(), activities.end(), finish_comparator);

    return ActivitySelection_Iterative(activities).size();
}


/**
 * @reference   Meeting Rooms
 *              https://www.programcreek.com/2014/07/leetcode-meeting-rooms-java/
 *
 * Given an array of meeting time intervals consisting of start and end times
 * [[s1,e1],[s2,e2],...](si< ei), determine if a person could attend all meetings.
 */
auto MeetingRooms(ArrayType activities) {
    std::sort(activities.begin(), activities.end(), finish_comparator);

    for (std::size_t i = 1; i < activities.size(); ++i) {
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
 * Given an array of meeting time intervals consisting of start and end times
 * [[s1,e1],[s2,e2],...](si< ei), find the minimum number of conference rooms required.
 */
auto MinMeetingRooms_Heap(ArrayType activities) {
    std::sort(activities.begin(), activities.end(), start_comparator);

    std::priority_queue<unsigned, std::vector<unsigned>, std::greater<unsigned>> rooms;
    rooms.push(activities.front().second);
    for (std::size_t i = 1; i < activities.size(); ++i) {
        if (activities[i].first >= rooms.top()) {
            rooms.pop();
        }
        rooms.push(activities[i].second);
    }

    return rooms.size();
}


auto MinMeetingRooms_PrefixSum(const ArrayType &activities) {
    std::map<int, int> room_counts;
    for (const auto [start, finish] : activities) {
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

}//namespace


const ArrayType SAMPLE1 = {{10, 20}, {12, 25}, {20, 30}};
const OutputType EXPECTED1 = {0, 2};

const ArrayType SAMPLE2 = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};
const OutputType EXPECTED2 = {0, 1, 3, 4};

const ArrayType SAMPLE3 =
{{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}};
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
